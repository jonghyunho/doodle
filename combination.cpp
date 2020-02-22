#include <iostream>
#include <string>

using namespace std;

void combination(int arr[], int data[], int start, int end, int index, int r) {
  if (index > r) {
    for (int j = 0; j <= r; j++) cout << data[j] << " ";
    cout << endl;
    return;
  }

  for (int i = start; i <= end; i++) {
    data[index] = arr[i];
    combination(arr, data, i + 1, end, index + 1, r);
  }
}

void combination(int arr[], int n, int r) {
  int* data = new int[r];

  combination(arr, data, 0, n - 1, 0, r - 1);

  delete[] data;
}

int main() {
  int arr[] = {1, 2, 3, 4, 5};
  int r = 3;
  combination(arr, 5, 3);
  return 0;
}
