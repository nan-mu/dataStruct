#include <assert.h>

#include <cstddef>
#include <cstdio>
#include <cstdlib>

using namespace std;

/// @brief 交换两变量
template <class T>
void tSwap(T *p1, T *p2) {
	T temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

typedef struct Node {  // 数据节点类
	Node *next;
	char data;
} Node;

class NodeLink {
  private:
	Node *head;	 //指向队开头
	Node *tail;	 //操作对象（队尾）
	int length;
	bool push_head(char data) {
		Node *opt = (Node *)malloc(sizeof(Node));
		opt->data = data;
		opt->next = head;
		if (length++ == 0)
			tail = opt;
		else
			tail->next = opt;
		head = opt;

		return true;
	}

  public:
	NodeLink() {  //初始化链表
		head = nullptr;
		tail = nullptr;
		length = 0;
	}
	~NodeLink() {
		while (pop() != false)
			;
		head = nullptr;
		tail = nullptr;
	}
	int pop() {
		if (length == 0) return 0;
		if (head == tail) {	 //删除最后一项
			char data = head->data;
			free(head);
			head = nullptr;
			tail = nullptr;
			length = 0;
			return data;
		} else {
			char data = head->data;
			tail->next = head->next;
			free(head);
			head = tail->next;
			return data;
		}
	}
	bool push(char data) {
		if (head == nullptr) {
			head = (Node *)malloc(sizeof(Node));
			tail = head;
			head->data = data;
			head->next = head;
			length++;
			return true;
		} else {
			Node *opt = (Node *)malloc(sizeof(Node));
			opt->data = data;
			tail->next = opt;
			tail = opt;
			opt->next = head;
			length++;
			return true;
		}
	}
	int get_length() {						// 计算长度
		int len = head != nullptr ? 1 : 0;	//这个有点多余，但确实穷经了所有情况
		for (Node *opt = head; opt != tail; opt = opt->next) len++;
		length = len;
		return len;
	}
	void print() {	// 打印
		Node *opt = head;
		for (int i = get_length(); i > 0; i--) {
			printf("%c ", opt->data);
			opt = opt->next;
		}
		printf("\n");
	}
	void
	exchange() {  //颠倒队列，思路是先把队列数据导出，然后再从头插入，时间和空间复杂度都为O(n)
		Node *opt1 = head, *opt2 = tail;
		size_t temp_length = get_length();
		char *temp_items = (char *)malloc(sizeof(char) * temp_length);
		for (size_t i = 0; i < temp_length; i++) temp_items[i] = pop();
		for (size_t i = 0; i < temp_length; i++) push_head(temp_items[i]);
		delete temp_items;
	}
};

int main() {
	NodeLink a;
	a.push('a');
	a.push('b');
	a.push('c');
	a.push('d');
	a.push('e');
	a.print();
	a.exchange();
	a.print();
}