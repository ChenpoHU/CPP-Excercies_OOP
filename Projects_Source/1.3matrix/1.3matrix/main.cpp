//Your code goes here
#include "matrix.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
	/*Matrix<int> m(2, 2);
	m.values[0] = 1;
	m.values[1] = 2;
	m.values[2] = 3;
	m.values[3] = 4;*/
	std::cout << "Initialize m1 as {{3,4,5},{1,2,3},{1,4,5}}"<< std::endl;
	Matrix<int> m1 = { {3,4,5},{1,2,3},{1,4,5} };
	std::cout << m1;
	std::cout << "Get rows" << std::endl;
	std::cout << "rows: " << m1.get_rows_nb() << std::endl;
	std::cout << "Get columns" << std::endl;
	std::cout << "columns: " << m1.get_cols_nb() << std::endl;
	std::cout << "Accept another matrix as a parameter for initialization: Initialize m2 as m1" << std::endl;
	Matrix<int> m2(m1);
	std::cout << m2;
	std::cout << "Get the elements of m2 at position (0, 0)" << std::endl;
	std::cout << m2.get_at(0, 0) << std::endl;
	std::cout << "Add a matrix to the current matrix" << std::endl;
	Matrix<int> d = { {1,2,3},{0,1,2},{0,4,1} };
	m2.add(d);
	std::cout << m2;
	std::cout << "Multiply a matrix to the current matrix" << std::endl;
	m2.multiply(d);
	std::cout << m2;
	std::cout << "Multiply the matrix with a scalar " << std::endl;
	m2.multiply_s(2);
	std::cout << m2;
	std::cout << "Return a row of a matrix as std::vector " << std::endl;
	std::cout << m2.get_row(0) << std::endl;
	std::cout << "Return a column of a matrix as std::vector " << std::endl;
	std::cout << m2.get_col(0) << std::endl;

	/*Matrix<int> m3 = { {3,2,1},{1,0,2}};
	Matrix<int> d4 = { {1,2},{0,1},{4,0} };
	m3.multiply(d4);
	std::cout << m3;*/

	return 0;
}
