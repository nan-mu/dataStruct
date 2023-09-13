#ifndef NODELIST_H
#define NODELIST_H
#include <cstddef>
#define CLEAN 0

#include <assert.h>

#include <cstdio>
#include <cstdlib>

typedef struct Node {  // 数据节点类
	Node *next;
	int data;
} Node;

class NodeList {
  private:
	Node *head;	 //指向链表开头
	// 本来这里有一个opt用来当作中间变量，但第二题略有负责，所以使用中间变量可能会导致作用域污染，所以删掉了
	Node *tail;	 //指向链表结尾
	Node *now;	 //用于表示迭代器操作对象

  public:
	NodeList() {
		// printf("A node list was created!");
		head = nullptr;
		tail = nullptr;
	}
	~NodeList() {
		now = nullptr;
		while (pop())
			;
	}
	bool push(int data);
	bool push_f(int data);
	bool diff(NodeList *diff_set);
	bool de_same();
	int length();
	bool print();
	bool sort();
	bool iter(int index);  //相当于向后移动now指针
	int get(int index);	   //获取now，index用于向后移动
	bool pop();	 //单链表的话，就当队列用吧，当堆的话pop的实现就太傻了
};

inline bool NodeList::de_same() {
	Node *opt = head;
	int orgin_length = length();
	for (int i = 0; i < orgin_length - 1; i++, opt = opt->next) {
		if (opt->data != opt->next->data) push(opt->data);
	}
	push(opt->data);
	for (; orgin_length > 0; orgin_length--) {
		pop();
	}
	opt = nullptr;
	return true;
};

inline int NodeList::length() {
	Node *opt;
	int len = 0;
	for (opt = head; opt != nullptr; opt = opt->next) len++;
	opt = nullptr;
	return len;
}

inline int NodeList::get(int index) {
	iter(index);
	return now->data;
}

inline bool NodeList::iter(int index) {
	if (index >= 0)
		for (; index > 0; index--)
			if (now != tail) {
				now = now->next;
				return true;
			} else {
				return false;  //表示到头了
			}
	else {
		now = head;	 //复位
	}
	return true;
}

inline bool NodeList::push(int data) {
	Node *opt = (Node *)malloc(sizeof(Node));
	opt->data = data;
	opt->next = nullptr;
	if (tail == nullptr) {	//创建首个节点的情况
		// printf("创建了第一个节点");
		head = opt;
		tail = opt;
		opt = nullptr;
		now = head;
	} else {  //创建后续节点的情况
		// printf("创建了一个节点");
		tail->next = opt;
		tail = opt;
		opt = nullptr;
	}
	opt = nullptr;
	return true;
}

inline bool NodeList::push_f(int data) {
	Node *opt = (Node *)malloc(sizeof(Node));
	assert(head != nullptr);  //不要用来创建第一个节点！
	opt->data = data;
	opt->next = head;
	head = opt;
	opt = nullptr;
	return true;
}

inline bool NodeList::pop() {
	if (head == tail) {
		tail = nullptr;
		free(head);
		head = nullptr;
		printf("clean");
		return CLEAN;
	} else {
		if (head == now) now = head->next;
		Node *opt = head;  //从头开始删除
		head = opt->next;
		free(opt);
		opt = nullptr;
		return true;
	}
}

inline bool NodeList::sort() {
	Node *opt2 = nullptr, *opt = nullptr;
	for (opt = head; opt != nullptr; opt = opt->next) {
		for (opt2 = opt; opt2 != nullptr; opt2 = opt2->next) {	//冒泡排序
			if (opt2->data < opt->data) {
				opt->data += opt2->data;
				opt2->data = opt->data - opt2->data;
				opt->data = opt->data - opt2->data;
			}
		}
	}
	de_same();
	return true;
}

inline bool NodeList::print() {
	Node *opt;
	for (opt = head; opt != nullptr; opt = opt->next) {
		printf("%d ", opt->data);
	}
	printf("\n");
	opt = nullptr;
	return true;
}

inline bool NodeList::diff(NodeList *diff_set) {
	Node *opt = head;
	int orgin_length = length();
	for (int i = 0; i < orgin_length; i++) {
		if (opt->data > diff_set->get(0)) {
			if (!diff_set->iter(1)) {
				for (; i < orgin_length; i++) {
					push(opt->data);
					opt = opt->next;
				}
				break;
			};
			i--;
		} else if (opt->data < diff_set->get(0)) {
			push(opt->data);
			opt = opt->next;
		} else {
			diff_set->iter(1);
			opt = opt->next;
		};
	}
	opt = nullptr;
	for (; orgin_length > 0; orgin_length--) {
		pop();
	}
	return true;
}

#endif