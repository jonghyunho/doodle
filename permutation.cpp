#include <iostream>
#include <string>

using namespace std;

void permutation(string str, int l, int r) {
  if (l == r) {
    cout << str << endl;
  } else {
    for (int i = l; i <= r; i++) {
      swap(str[i], str[l]);
      permutation(str, l + 1, r);
      swap(str[i], str[l]);
    }
  }
}

int main() {
  string str = "ABC";
  permutation(str,  0, str.length()-1);
  return 0;
}
