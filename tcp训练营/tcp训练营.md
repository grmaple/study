# tcp训练营

![image-20200806201439659](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200806201439659.png)

## day1实现一个协议栈

##### 为什么要实现协议栈？

tcp协议栈从内核搬到了应用程序

减少了copy次数，提升了吞吐量



主机192.168.142.1（客户端）

虚拟机192.168.142.129（服务器）

两台机器之间为什么能够收到数据？

##### 网络协议栈

![image-20200806202135665](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200806202135665.png)

##### 网卡属于那一层？

物理层：光电信号

数据链路层：数字信号

网卡是将光电信号转换成数字信号，起到A/D转换作用

网卡在两层之间

网络适配器(网卡)工作在数据链路层和物理层

##### 以太网协议头

![image-20200806203541815](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200806203541815.png)

```c
#pragama pack(1)
#define ETH_LENGTH	6
struct ethhdr{
    unsigned char h_dest[ETH_LENGTH];//6字节
    unsigned char h_src[ETH_LENGTH];//6字节
    unsigned short h_proto; //2字节
};
```

##### ip协议头

![image-20200806204444238](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200806204444238.png)

```c
struct iphdr{
    unsigned char version:4, hdrlen:4;//位域
    unsigned char tos;
    
    unsigned short totlen;
    unsigned short id;
    
    unsigned short flag:3, offset:13;
    unsigned char ttl;//默认64，每经过一个网关-1
    
    unsigned char proto;
    unsigned short check;
    
    unsigned int sip;
    unsigned int dip;
};
```

##### udp协议头

![image-20200806205918049](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200806205918049.png)

```c
struct udphdr{
    unsigned short sport;
    unsigned short dport;
    unsigned short length;
    unsigned short crc;
};
```

端口是什么？

传输层里面有个字段叫端口

##### udp包

udp packet = ethhdr+iphdr+udphdr+body

```c
struct udppkt{
    struct ethhdr eh;//sizeof(eh)=14
    struct iphdr ip;//sizeof(ip)=20
    struct udphdr udp;//sizeof(udp)=8
    
    unsigned char body[0];//柔性数组sizeof(body)=0;
};//sizeof(udppkt)=44,因为需要对齐
//加了#pragama pack(1)就变成42
```

网卡驱动运行在内核，cpu上面

网卡把收到的数据通过mmap映射到内存

然后

netmap 开源的

dpdk 商用的

数据来了，cpu怎么知道有数据来了？

通过I/O多路复用 poll

```c
struct pollfd {
	int fd;          // 需要监视的文件描述符
	short events;    // 需要内核监视的事件
	short revents;   // 实际发生的事件
};
```



*ntohs*()是一个函数名，作用是将一个16位数由网络字节顺序转换为主机字节顺序。

网络字节序 两个字节以上就要转

## day2

昨天实现了一个udp协议栈

1.以太网协议

2.ip协议

3.udp协议

在netmap的基础上，实现了udp协议栈。

不走系统的协议栈。



三个功能

1.tcp connect

2.tcp send

3.tcp close

![img](https://pics1.baidu.com/feed/d8f9d72a6059252d20d93b0a6645fb3e59b5b9d2.jpeg?token=c86d4509157378798ebbccbe843486d1&s=9746F8123F5754CA48D574DA0300D0B2)

服务器先行。服务器先进入listen状态。

每来一个连接。服务器调用accept函数，然后返回一个新的fd，接下来的通讯通过这个新fd进行



三次握手发生在哪个函数里面?

客户端connect里面,

服务器listen之后,accept之前，被动连接。



listen(fd, backlog);

back：syn队列总长度

linux中syn队列+accept队列总长度



tcp状态迁移图

![img](https://images2015.cnblogs.com/blog/826551/201705/826551-20170519094144338-1763590644.png)

![img](https://images2015.cnblogs.com/blog/826551/201705/826551-20170519094310869-571721150.png)

tcp状态放哪里？

每一个连接都有状态



tcp控制块（tcb），伴随着整个tcp连接生命周期

如何标识tcb？

对应的五元组

(sip,dip,sport,dport,proto)

```c
struct tcb{
    int sip;
    int dip;
    short sport;
    short dport;
    char proto;
    
    int fd;
    unsigned char * rbuf;
    unsigned char * sbuf;
};
```

tcp协议头

![img](https://images2015.cnblogs.com/blog/740952/201611/740952-20161107132809311-2059896218.png)

```c
struct tcphdr{
    unsigned short sport;
    unsigned short dport;
    unsigned int seqnum;
    unsigned int acknum;
    unsigned char hdrlen:4,resv:4;
    unsigned char cwr:1,ece:1,urg:1,ack:1,psh:1,rst:1,syn:1,fin:1;
    unsigned short windows;
    unsigned short check;
    unsigned short urgpointer;
    
};//20
```



调用send

send(fd, buffer, length, 0);

把application里的tcb的数据copy到kernel里面的sbuff[]。

sk_buff

把kernel的数据放到网卡

recv()

任何一次接收数据

1.从网卡copy到内核协议栈

2.从协议栈copy到应用程序

当服务器接收大量数据包的时候， 大量时间在copy上面。

能不能直接从网卡拷贝到应用程序上面？

用户态协议栈

零拷贝技术



tcp是流式套接字，它是顺序的



延迟ack200ms



app与服务器连接

1.弱网环境延迟大

弱网会引起大量超时重传



tcp如何确定可以发送多少个包?



rtt=0.9*rtt(n-1) +0.1\*rtt(1)

消抖

