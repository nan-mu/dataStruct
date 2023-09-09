#ifndef NODELIST_H
#define NODELIST_H
#define CLEARD 0

#include <cstdio>

typedef struct Node {  // 数据节点类
	Node *next;
	int data;
} Node;

class NodeList {
  private:
	Node *head;	 //指向链表开头
	Node *opt;	 //用于类函数操作节点
	Node *tail;	 //指向链表结尾

  public:
	NodeList() {
		printf("A node list was created!");
		head = nullptr;
		tail = nullptr;
		opt = nullptr;
	}
	bool push(int data);
	bool print();
	bool sort();
	bool pop();	 //单链表的话，就当队列用吧，当堆的话pop的实现就太傻了
};

#endif