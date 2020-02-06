w#include <cassert>
#include <iostream>
#include "Matrix.h"
using namespace std;

int main()
{
	Matrix mat;
	ostream& os = cout;
	Matrix_init(&mat, 20, 10);
	Matrix_fill_border(&mat, 5);
	Matrix_print(&mat, os);
	int* ptr =  Matrix_at(&mat, 12, 8);
	cout << Matrix_row(&mat, ptr) << " " << Matrix_column(&mat, ptr) << endl;
	cout << Matrix_max(&mat) << endl;
	cout << Matrix_column_of_min_value_in_row(&mat, 3, 5, 19) << endl;
	return 0;
}