//
//  main.c
//  static_list
//
//  Created by met7or on 2020/1/21.
//  Copyright © 2020 met7or. All rights reserved.
//

#include <stdio.h>

#define MAXSIZE 1000
#define ERROR 0
#define OK 1

typedef int ElemType;
typedef int Status;
typedef struct Node {
    
    ElemType data;
    int cur;
    
}StaticLinkList[MAXSIZE];

void TraverseSList(StaticLinkList L) {
    printf("List Traverse : \n");
    int k = MAXSIZE - 1;
    while (L[k].cur != 0) {
        k = L[k].cur;
        printf("%d ", L[k].data);
    }
    printf("\n");
}

// 初始化静态链表
Status InitSList(StaticLinkList space) {
    
    int i;
    for(i=0; i<MAXSIZE - 2; i++) {
        space[i].cur = i+1;
    }
    space[MAXSIZE-1].cur = 0;
    space[MAXSIZE-2].cur = 0;
    return OK;
}

// 获取链表的长度
int GetSListLength(StaticLinkList L) {
    int j = 0;
    int i = L[MAXSIZE-1].cur;
    
    while (i) {
        i = L[i].cur;
        j++;
    }
    return j;
}

// 若备用链表空间非空，则返回分配的节点下标，否则返回0
int MallocSList(StaticLinkList space) {
    int i = space[0].cur;
    // 判断备用链表是否为空
    if (space[0].cur) {
        space[0].cur = space[i].cur;
    }

    return i;
}

// 回收释放
void FreeSList(StaticLinkList space, int k) {
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

// 链表中i元素之前插入元素e
// 这里执行了将最后一个元素的游标赋值为0
Status InsertSList(StaticLinkList L, int i, ElemType e) {
    int j, k, l;
    k = MAXSIZE - 1;
    
    if (i < 1 || i > GetSListLength(L) + 1) {
        return ERROR;
    }
    
    j = MallocSList(L);
    if (j) {
        L[j].data = e;
        // 设置了最后一个元素的游标为0
        for (l = 1; l < i; l++) {
            k = L[k].cur;
        }
        
        L[j].cur = L[k].cur;
        L[k].cur = j;
        return OK;
    }
    
    return ERROR;
}

Status DeleteSList(StaticLinkList L, int i) {
    int j, k;
    
    if (i < 1 || i > GetSListLength(L)) {
        return ERROR;
    }
    
    k = MAXSIZE - 1;
    for (j = 1; j <= i-1; j++ ) {
        k = L[k].cur;
    }
    j = L[k].cur;
    L[k].cur = L[j].cur;
    FreeSList(L, j);
    
    return OK;
}

int main(int argc, const char * argv[]) {
    StaticLinkList L;
    InitSList(L);
    for (int i = 1; i < 5; i++) {
        InsertSList(L, i, i);
    }
    TraverseSList(L);
    
    DeleteSList(L, 4);
    TraverseSList(L);
    
    InsertSList(L, 2, 10);
    TraverseSList(L);
    return 0;
}
