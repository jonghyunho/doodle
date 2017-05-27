#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

vector < int >heap;

void push_heap(vector < int >&heap, int newValue)
{
	heap.push_back(newValue);

	int idx = heap.size() - 1;

	while (idx > 0 && heap[(idx - 1) / 2] < heap[idx]) {
		swap(heap[idx], heap[(idx - 1) / 2]);
		idx = (idx - 1) / 2;
	}
}

int pop_heap(vector < int >&heap)
{
	int ret = heap[0];
	heap[0] = heap.back();

	heap.pop_back();

	int here = 0;

	while (true) {
		int left = here * 2 + 1, right = here * 2 + 2;

		if (left >= heap.size())
			break;

		int next = here;

		if (heap[next] < heap[left])
			next = left;

		if (right < heap.size() && heap[next] < heap[right])
			next = right;

		if (next == here)
			break;

		swap(heap[here], heap[next]);

		here = next;
	}

	return ret;
}

void print_heap(vector < int >&heap)
{
	cout << "* ";
	for (int i = 0; i < heap.size(); i++) {
		cout << heap[i] << " ";
	}
	cout << endl;
}

int main()
{
	srand(time(NULL));

	for (int i = 0; i < 5; i++) {
		int newValue = rand() % 10;
		push_heap(heap, newValue);
		cout << "push " << newValue << endl;
		print_heap(heap);
	}

	for (int i = 0; i < 5; i++) {
		cout << "pop " << pop_heap(heap) << endl;
		print_heap(heap);
	}


	return 0;
}
