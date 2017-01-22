#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

char*** create3DArray(unsigned int rows, unsigned int cols, unsigned int n);
char** create2DArray(unsigned int rows, unsigned int cols);
char*** extract_bitplanes(char** bitmap);
char** extract_bitplane(char** bitmap, int mask);

int main() {
	string x = "";
	getline(cin, x);

	//default size value for bitplane to have something to work on
	unsigned int rows = 4;
	unsigned int cols = 3;

	char** bitmap = create2DArray(rows, cols);
	char*** bitplanes = extract_bitplanes(bitmap);

	cout << "wypisywanie bitplejna" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << int(bitplanes[1][i][j]) << " ";
		}
		cout << endl;
	}

	getline(cin, x);

	return 0;
}

char** create2DArray(unsigned int rows, unsigned int cols)
{
	char** array2D = 0;
	array2D = new char*[rows];

	for (int r = 0; r < rows; r++)
	{
		array2D[r] = new char[cols];

		for (int c = 0; c < cols; c++)
		{
			array2D[r][c] = c + cols * r;
		}
	}

	return array2D;
}

char*** create3DArray(unsigned int rows, unsigned int cols, unsigned int n)
{
	char*** array3D = 0;
	array3D = new char**[n];

	for (int i = 0; i < n; i++)
	{
		array3D[i] = create2DArray(rows, cols);
	}

	return array3D;
}

char*** extract_bitplanes(char** bitmap) {

	char** bitplane = 0;
	char*** bitplanes = 0;

	unsigned int rows = sizeof bitmap / sizeof bitmap[0];  
	unsigned int cols = sizeof bitmap[0] / sizeof(char);
	char bitplanes_count = 8;

	bitplanes = create3DArray(rows, cols, bitplanes_count);

	for (int i = 0; i < 8; i++) {
		int mask = 0b00000001 << i;
		bitplane = extract_bitplane(bitmap, mask);
		bitplanes[i] = bitplane;
	}

	return bitplanes;
}

char** extract_bitplane(char** bitmap, int mask) {

	char** bitplane = create2DArray(4, 4);
	cout << "Mask: " << mask << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			bitplane[i][j] = (char)(int(bitmap[i][j]) & mask);
			//cout << int(bitplane[i][j]) << ", " << bitmap[i][j] << ", " << int(bitmap[i][j]) << endl;
		}
	}

	return bitplane;
}