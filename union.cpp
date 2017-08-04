#include <iostream>

using namespace std;

int data[10];
int r[10];

void makeSet(int x) {
	data[x] = x;
	r[x] = 0;
}

int findSet(int x) {
	if (data[x] == x) {
		return x;
	}

	return findSet(data[x]);
}

void link(int x, int y) {
	x = findSet(x);
	y = findSet(y);

	if (r[x] < r[y]) {
		data[x] = y;
	}
	else {
		data[y] = x;
		if (r[x] == r[y]) {
			r[y]++;
		}
	}

	data[y] = x;
}

int main() {
	for (int i = 0; i < 10; i++) {
		makeSet(i);
	}

	for (int i = 1; i <= 4; i++) {
		link(i-1, i);
	}

	for (int i = 5; i <= 8; i++) {
		link(i, i+1);
	}

	for (int i = 0; i < 10; i++) {
		cout << data[i] << " ";
	}
	cout << endl;
	
	cout << "group of 3 : " << findSet(3) << endl;
	cout << "group of 9 : " <<  findSet(9) << endl;

	return 0;
}
