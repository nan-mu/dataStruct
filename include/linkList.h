#ifndef MYCLASS_H
#define MYCLASS_H

#include <cstdio>

typedef struct Node {  // 数据节点类
    Node *next;
    int data;
}Node;

class NodeList{
    public:
        Node *head;
        Node *now;
        Node *tail;
        NodeList(){
            printf("A node list was created!");
            head = nullptr;
            tail = nullptr;
            now = nullptr;
        }
};

#endif