#ifndef NODELIST_H
#define NODELIST_H
#define CLEAN 0

#include <cstdio>
#include <cstdlib>

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
		// printf("A node list was created!");
		head = nullptr;
		tail = nullptr;
		opt = nullptr;
	}
	bool push(int data);
	bool print();
	bool sort();
	bool pop();	 //单链表的话，就当队列用吧，当堆的话pop的实现就太傻了
};

inline bool NodeList::push(int data) {
	opt = (Node *)malloc(sizeof(Node));
	opt->data = data;
	opt->next = nullptr;
	if (tail == nullptr) {	//创建首个节点的情况
		// printf("创建了第一个节点");
		head = opt;
		tail = opt;
		opt = nullptr;
	} else {  //创建后续节点的情况
		// printf("创建了一个节点");
		tail->next = opt;
		tail = opt;
		opt = nullptr;
	}
	return true;
}

inline bool NodeList::pop() {
	if (head == tail) {
		free(head);
		head = nullptr;
		tail = nullptr;
		printf("clean");
		return CLEAN;
	} else {
		opt = head;
		head = opt->next;
		free(opt);
		opt = nullptr;
		return true;
	}
}

inline bool NodeList::sort() {
	Node *opt2 = nullptr;
	for (opt = head; opt != nullptr; opt = opt->next) {
		for (opt2 = opt; opt2 != nullptr; opt2 = opt2->next) {	//冒泡排序
			if (opt2->data < opt->data) {
				opt->data += opt2->data;
				opt2->data = opt->data - opt2->data;
				opt->data = opt->data - opt2->data;
			}
		}
	}
	return true;
}

inline bool NodeList::print() {
	for (opt = head; opt != nullptr; opt = opt->next) {
		printf("%d ", opt->data);
	}
	printf("\n");
	return true;
}

#endif