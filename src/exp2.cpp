#include <cstdio>
using namespace std;

#include "./linklist.cpp"
int main() {
	NodeLink h;
	h.push('a');
	h.push('b');
	h.push('c');
	h.push('d');
	h.push('e');
	h.print();
	printf("h length: %d\n", h.get_length());
	printf(h.is_empty() ? "有的\n" : "空的\n");
	printf("%c\n", h.print(3));
	printf("%p\n", h.find('a'));
	h.push('/', 4);
	h.print();
	h.deleteE(3);
	h.print();
	return 0;
}