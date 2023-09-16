#include <assert.h>

#include <cstdio>
#include <string>

using namespace std;

bool is_currect(string tar) {
	int d = 0, z = 0, x = 0;
	for (const auto& iter : tar) {
		switch (iter) {
			case '{':
				d++;
				break;
			case '}':
				d--;
				break;
			case '[':
				z++;
				break;
			case ']':
				z--;
				break;
			case '(':
				x++;
				break;
			case ')':
				x--;
				break;
			default:
				assert(false);
		}
	}
	return (d + z + x) == 0;
}

int main() {
	string yes = "([[]{)(}])([[]{)(}])([[]{)(}])", no = "([[]{)(})";
	printf(is_currect(yes) ? "对的\n" : "错的\n");
	printf(is_currect(no) ? "对的\n" : "错的\n");
}
