#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

char*** create3DArray(unsigned int rows, unsigned int cols, unsigned int n);
char** create2DArray(unsigned int rows, unsigned int cols, int values);
char*** extract_bitplanes(char** bitmap, unsigned int rows, unsigned int cols);
char** extract_bitplane(char** bitmap, unsigned int rows, unsigned int cols, int mask);
char** join_bitplanes(char*** bitplanes, unsigned int rows, unsigned int cols);
void print2Darray(char** array, unsigned int rows, unsigned int cols);

int main() {

	cout << "Extracting bitplanes" << endl;

	//default size value for bitplane to have something to work on
	unsigned int rows = 16;
	unsigned int cols = 16;

	//entry bitmap
	char** bitmap = create2DArray(rows, cols, 1);

	//print entry bitmap into console
	cout << "Entry bitmap:" << endl;
	print2Darray(bitmap, rows, cols);

	//extracting bitplanes
	char*** bitplanes = extract_bitplanes(bitmap, rows, cols);

	//code to print array into console
	//n - number of bitplane to show
	int n = 2;
	cout << "Bitplane " << n << ":" << endl;
	print2Darray(bitplanes[n], rows, cols);
	cout << "Joining bitplanes" << endl;

	//output bitmap
	char** output_bitmap = join_bitplanes(bitplanes, rows, cols);

	//print output bitmap to console
	cout << "Output bitmap:" << endl;
	print2Darray(output_bitmap, rows, cols);

	system("pause");

	return 0;
}

void print2Darray(char** array, unsigned int rows, unsigned int cols) {

	cout << "rows: " << rows << ", columns: " << cols << endl;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << int(array[i][j]) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

char** create2DArray(unsigned int rows, unsigned int cols, int values)
{
	char** array2D = 0;
	array2D = new char*[rows];
	int counter = 0;

	for (int r = 0; r < rows; r++)
	{
		array2D[r] = new char[cols];

		for (int c = 0; c < cols; c++)
		{
			if (values == 0)
				array2D[r][c] = 0;
			else
				array2D[r][c] = counter;
				counter++;
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
		array3D[i] = create2DArray(rows, cols, 1);
	}

	return array3D;
}

char*** extract_bitplanes(char** bitmap, unsigned int rows, unsigned int cols) {

	char** bitplane = 0;
	char*** bitplanes = 0;
	char bitplanes_count = 8;

	bitplanes = create3DArray(rows, cols, bitplanes_count);

	for (int i = 0; i < 8; i++) {
		int mask = 0b00000001 << i;
		bitplane = extract_bitplane(bitmap, rows, cols, mask);
		bitplanes[i] = bitplane;
	}

	return bitplanes;
}

char** extract_bitplane(char** bitmap, unsigned int rows, unsigned int cols, int mask) {

	char** bitplane = create2DArray(rows, cols, 1);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			bitplane[i][j] = (char)(int(bitmap[i][j]) & mask);
		}
	}

	return bitplane;
}

char** join_bitplanes(char*** bitplanes, unsigned int rows, unsigned int cols) {

	char** bitplane = 0;
	int n = 8;

	bitplane = create2DArray(rows, cols, 0);

	for (int i = 0; i < n; i++) {
		if (bitplanes[i] == NULL) {
			continue;
		}
		else {
			for (int r = 0; r < rows; r++) {
				for (int c = 0; c < cols; c++) {
					bitplane[r][c] += bitplanes[i][r][c];
				}
			}
		}
	}

	return bitplane;
}