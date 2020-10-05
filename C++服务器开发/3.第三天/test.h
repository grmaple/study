/*************************************************************************
	> File Name: test.h
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 四  8/20 20:25:55 2020
 ************************************************************************/

#ifndef _TEST_H
#define _TEST_H

#define TEST(func, arr, n) { \
    int *temp = (int *)malloc(sizeof(int) * n); \
    for (int i = 0; i < n; i++) temp[i] = arr[i]; \
    long long b = clock(); \
    func(temp, 0, n - 1); \
    long long e = clock(); \
    if (check(temp, 0, n - 1)) { \
        printf("\033[1;32m[    OK    ]\033[0m %s ", #func); \
    } else { \
        printf("\033[1;31m[  FAILED  ]\033[0m %s ", #func); \
    } \
    printf("\033[1;33m(%lld ms)\033[0m\n", 1000 * (e - b) / CLOCKS_PER_SEC); \
}

int check(int *arr, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        if (arr[i] < arr[i - 1]) return 0;
    }
    return 1;
}

int *getRandData(int n) {
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) arr[i] = rand() % n;
    return arr;
}

#endif
