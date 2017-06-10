#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

bool compareGreater(int a, int b) {
	return a > b;
}

bool compareSmaller(int a, int b) {
	return a < b;
}

class HeapTree {
private:
	vector<int> mData;
	bool(*compare)(int a, int b);

public:
	HeapTree(bool(*c)(int a, int b))
	: compare(c) {
	}

	~HeapTree() {
	}

	void swap(int idxA, int idxB) {
		int temp = mData[idxA];
		mData[idxA] = mData[idxB];
		mData[idxB] = temp;
	}

	void push(int data) {
		mData.push_back(data);

		int idx = mData.size() - 1;

		while (idx > 0 && compare(mData[idx], mData[(idx - 1) / 2])) {
			swap((idx - 1) / 2, idx);
			idx = (idx - 1) / 2;
		}
	}

	int pop() {
		int ret = mData[0];

		swap(0, mData.size() - 1);
		mData.pop_back();

		int here = 0;
		
		while (true) {
			int left = here * 2 + 1;
			int right = here * 2 + 2;

			if (left >= (int) mData.size()) {
				break;
			}

			int next = here;
			
			if (compare(mData[left], mData[next])) {
				next = left;
			}

			if (right < (int) mData.size() && compare(mData[right], mData[next])) {
				next = right;
			}

			if (here == next) {
				break;
			}

			swap(here, next);
			here = next;
		}

		return ret;
	}
};

int main() {
	srand((unsigned int) time(NULL));

	HeapTree maxHeap(&compareGreater);
	HeapTree minHeap(&compareSmaller);

	int base = 50;
	for (int i = 0; i < 100; i++) {
		int v = rand() % 100;
		
		if (v <= 50) {
			maxHeap.push(v);
		}
		else {
			minHeap.push(v);
		}
	}

	for (int i = 0; i < 5; i++) {
		int maxv = maxHeap.pop();
		int minv = minHeap.pop();

		cout << "maxv : " << maxv << " minv : " << minv << endl;
	}

	return 0;
}