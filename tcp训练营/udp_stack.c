#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <arpa/inet.h>

#define NETMAP_WITH_LIBS
#include <net/netmap_user.h>

#pragama pack(1)
#define ETH_LENGTH	6
#define PROTO_IP 0x0800
#define PROTO_UDP 17
struct ethhdr{
    unsigned char h_dest[ETH_LENGTH];//6字节
    unsigned char h_src[ETH_LENGTH];//6字节
    unsigned short h_proto; //2字节
};
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
struct udphdr{
    unsigned short sport;
    unsigned short dport;
    unsigned short length;
    unsigned short crc;
};
struct udppkt{
    struct ethhdr eh;//sizeof(eh)=14
    struct iphdr ip;//sizeof(ip)=20
    struct udphdr udp;//sizeof(udp)=8
    
    unsigned char body[0];//柔性数组sizeof(body)=0;
};//sizeof(udppkt)=44,因为需要对齐
//加了#pragama pack(1)就变成42
int main(){
	struct pollfd pfd = {0};
    //nm_desc是netmap的接口
	struct nm_desc *nmr = nm_open("netmap:eth0", NULL, 0, NULL);
	if(nmr == NULL) return -1;
	
	pfd.fd = nmr->fd;
	pfd.events = POLLIN;
	while(1){
		int ret = poll(&pfd, 1, -1);
		if(ret < 0) continue;
		if(pfd.revents & POLLIN){
			struct nm_pkthdr h;
			unsigned char * stream = nm_nextpkt(nmr, &h);
			struct ethhdr * eh = (struct ethhdr*)stream;
			if(ntohs(eh->h_proto) == PROTO_IP){
				//ip转udp
				struct udppkt * udp = (struct udppkt *)stream;
				if(udp->ip.proto == PROTO_UDP){
					unsigned short udplen = ntohs(udp->udp.length);
					udp->body[udplen-8] = '\0';
					printf("udp --> %s\n", udp->body);
				}
			}
		}
	}
	
	
	
}