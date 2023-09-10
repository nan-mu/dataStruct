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
	Node *opt;	 //用于类函数操作节点
	Node *tail;	 //指向链表结尾
	Node *now;	 //用于表示迭代器操作对象

  public:
	NodeList() {
		// printf("A node list was created!");
		head = nullptr;
		tail = nullptr;
		opt = nullptr;
	}
	~NodeList() {
		now = nullptr;
		while (pop())
			;
	}
	bool push(int data);
	bool push_f(int data);
	bool diff(NodeList diff_set);
	bool de_same();
	int length();
	bool print();
	bool sort();
	bool iter(int index);  //相当于向后移动now指针
	int get(int index);	   //获取now，index用于向后移动
	bool pop();	 //单链表的话，就当队列用吧，当堆的话pop的实现就太傻了
};

inline bool NodeList::de_same() {
	Node *opt2 = opt;
	int orgin_length = length();
	opt = head;
	for (int i = 0; i < orgin_length - 1; i++, opt = opt->next) {
		if (opt->data != opt->next->data) push(opt->data);
	}

	for (; orgin_length > 1; orgin_length--) {
		pop();
	}
	opt = opt2;
	opt2 = nullptr;
	return true;
};

inline int NodeList::length() {
	Node *opt2 = opt;
	int len = 0;
	for (opt = head; opt != nullptr; opt = opt->next) len++;
	opt = opt2;
	opt2 = nullptr;
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
	Node *opt2 = opt;
	opt = (Node *)malloc(sizeof(Node));
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
	opt = opt2;
	opt2 = nullptr;
	return true;
}

inline bool NodeList::push_f(int data) {
	Node *opt2 = opt;
	assert(head != nullptr);  //不要用来创建第一个节点！
	opt = (Node *)malloc(sizeof(Node));
	opt->data = data;
	opt->next = head;
	head = opt;
	opt = opt2;
	opt2 = nullptr;
	return true;
}

inline bool NodeList::pop() {
	Node *opt2 = opt;
	if (head == tail) {
		tail = nullptr;
		free(head);
		head = nullptr;
		printf("clean");
		opt2 = nullptr;
		return CLEAN;
	} else {
		if (head == now) now = head->next;
		opt = head;	 //从头开始删除
		head = opt->next;
		free(opt);
		opt = opt2;
		opt2 = nullptr;
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
	de_same();
	return true;
}

inline bool NodeList::print() {
	Node *opt2 = opt;
	for (opt = head; opt != nullptr; opt = opt->next) {
		printf("%d ", opt->data);
	}
	printf("\n");
	opt = opt2;
	opt2 = nullptr;
	return true;
}

inline bool NodeList::diff(NodeList diff_set) {
	Node *opt2 = opt;
	int orgin_length = length();
	for (opt = head; opt != nullptr; opt = opt->next) {
		if (opt->data == diff_set.get(0)) {
			diff_set.iter(1);
		} else {
			diff_set.iter(1);
			push(opt->data);
		};
	}
	opt = nullptr;
	for (; orgin_length > 0; orgin_length--) {
		pop();
	}
	opt = opt2;
	opt2 = nullptr;
	return true;
}

#endif