#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

char* extract_bitplanes(char bitmap[][4]);
char* extract_bitplane(char bitmap[][4], int mask);

int main() {
	string x = "";
	getline(cin, x);

	char bitmap[4][4] = { { 'a', 'b', 'c', 'd' },{ 'e', 'f', 'g', 'h' },{ 'i', 'j', 'k', 'l' },{ 'm', 'n', 'o', 'p' } };
	char* bitplanes = extract_bitplanes(bitmap);

	cout << bitplanes[0] << endl;
	cout << bitplanes[1] << endl;
	for (int i = 0; i < 4; i++) {
		//cout << bitplanes[0][i] << endl;
		cout << endl;
	}

	getline(cin, x);

	return 0;
}

char* extract_bitplanes(char bitmap[][4]) {

	char* bitplane;
	char* bitplanes[8];

	for (int i = 0; i < 8; i++) {
		int mask = 0b00000001 << i;
		bitplane = extract_bitplane(bitmap, mask);
		bitplanes[i] = bitplane;
	}
	return *bitplanes;
}

char* extract_bitplane(char bitmap[][4], int mask) {

	char b[4][4];
	cout << "Mask: " << mask << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			b[i][j] = (char)(int(bitmap[i][j]) & mask);
			cout << int(b[i][j]) << ", " << bitmap[i][j] << ", " << int(bitmap[i][j]) << endl;
		}
	}

	return *b;
}