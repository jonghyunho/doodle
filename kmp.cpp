#include <iostream>

using namespace std;

int str_len(char* str) {
	int i = 1;
	while (str[i] != '\0') { i++; }
	return i-1;
}

int main() {
	char str[100] = " hello banana hello banaba1 banaba2 world3";
	char pattern[10] = " banaba";
	int F[10] = {0};

	int i = 0;
	int k = 0;
	int lenp = str_len(pattern);
	int lens = str_len(str);

	F[1] = 0;
	for (int i = 2; i <= lenp; i++) {
		while (k && pattern[k+1] != pattern[i]) {  k = F[i]; }
		if (pattern[k+1] == pattern[i]) { k++; }
		F[i] = k;
	}

	for (int i = 1; i <= lenp; i++) {
		cout << F[i] << " ";
	}
	cout << endl;

	k = 0;
	for (int i = 1; i <= lens; i++) {
		while (k && pattern[k+1] != str[i]) { k = F[k]; }
		if (pattern[k+1] == str[i]) { k++; }
		if (k == lenp) {
			for (int j = i - lenp + 1; j <= i; j++) {
				cout << str[j];
			}
			cout << endl;
			k = F[k];
		}	
	}
	
	return 0;
}
