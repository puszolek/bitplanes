#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

unsigned char** create2DArray(unsigned int rows, unsigned int cols, int values);
unsigned char** extract_bitplanes(unsigned char** bitmap, unsigned int rows, unsigned int cols);
unsigned char* join_bitplanes(unsigned char** bitplanes, unsigned int rows, unsigned int cols);
void print2Darray(unsigned char** array, unsigned int rows, unsigned int cols);

int main() {

	cout << "Extracting bitplanes" << endl;

	//default size value for bitplane to have something to work on
	unsigned int rows = 128;
	unsigned int cols = 128;

	//entry bitmap
	unsigned char** bitmap = create2DArray(rows, cols, 1);

	//print entry bitmap into console
	cout << "Entry bitmap:" << endl;
	print2Darray(bitmap, rows, cols);

	//extracting bitplanes
	unsigned char** bitplanes = extract_bitplanes(bitmap, rows, cols);
	//print2Darray(bitplanes, 8, ((unsigned int)ceil(1.0 * rows * cols / 8)));
	
	//output bitmap
	unsigned char* output_bitmap = join_bitplanes(bitplanes, rows, cols);

	//print output bitmap to console
	cout << "Output bitmap:" << endl;
	for (unsigned int i = 0; i < rows*cols; i++) {
		cout << int(output_bitmap[i]) << " ";
		if (i % cols == 0) {
			cout << endl;
		}
	}

	system("pause");

	return 0;
}

void print2Darray(unsigned char** array, unsigned int rows, unsigned int cols) {

	cout << "rows: " << rows << ", columns: " << cols << endl;

	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			cout << int(array[i][j]) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

unsigned char** create2DArray(unsigned int rows, unsigned int cols, int values)
{
	unsigned char** array2D = 0;
	array2D = new unsigned char*[rows];
	int counter = 0;

	for (unsigned int r = 0; r < rows; r++)
	{
		array2D[r] = new unsigned char[cols];

		for (unsigned int c = 0; c < cols; c++)
		{
			if (values == 0)
				array2D[r][c] = 0;
			else if (values == 1)
				array2D[r][c] = 1;
			else {
				array2D[r][c] = counter;
				counter++;
			}
		}
	}

	return array2D;
}

unsigned char** extract_bitplanes(unsigned char** bitmap, unsigned int rows, unsigned int cols) {

	unsigned char** bitplanes = create2DArray(8, (unsigned int)ceil(1.0 * rows * cols / 8), 0);

	for (unsigned int n = 0; n < 8; n++) {

		char mask = 0b00000001 << n;
		int tmp = 7;
		unsigned int px = 0;
		unsigned int index = 0;

		for (unsigned int i = 0; i < rows; i++) {
			for (unsigned int j = 0; j < cols; j++) {

				if ((int(bitmap[i][j]) & mask) != 0){
					px += (0b00000001 << tmp) & 0b11111111;
				}
				else {
					px += 0;
				}

				if (tmp == 0) {
					bitplanes[n][index] = char(px);
					tmp = 8;
					px = 0;
					index++;
				}
				tmp--;
			}
		}
	}

	return bitplanes;
}

unsigned char* join_bitplanes(unsigned char** bitplanes, unsigned int rows, unsigned int cols) {

	unsigned char* bitmap = new unsigned char[rows*cols];

	for (unsigned int i = 0; i < rows*cols; i++) {
		bitmap[i] = 0;
	}

	int pxls = 0;
	int px = 0;
	int index = 0;

	for (unsigned int n = 0; n < 8; n++) {
		index = 0;

		if (bitplanes[n] == NULL) {
			continue;
		}
		else {
			for (unsigned int j = 0; j < (unsigned int)ceil(1.0 * rows * cols / 8); j++) {
				pxls = bitplanes[n][j];

				for (unsigned i = 0; i < 8; i++) {
					px = (pxls & (0b00000001 << (7 - i)));
					if (px > 0) {
						bitmap[index] += int(pow(2,n));
					}
					else {
						bitmap[index] += 0;
					}
					index++;
				}
			}
		}
	}

	cout << index << endl;

	return bitmap;
}