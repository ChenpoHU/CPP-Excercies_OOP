#pragma once
#include <vector>
#include <stdlib.h>

//using std::vector;

template<typename T>
class Matrix {
	int rows, columns;
	T* values;

	Matrix(int _rows, int _columns) :rows(_rows), columns(_columns) {
		values = new T[rows*columns];
	}
	
	Matrix(const Matrix& other) :Matrix(other.rows, other.columns) {
		memcpy(values, other.values, sizeof(T)*rows*columns);
	}

	~Matrix() {
		delete[] values;
	}

	void debugPrint() {
		for (int y = 0; y < rows; ++y) {
			for (int x = 0; x < columns; ++x)
				std::cout << values[x][y] << " ";
			std::cout << std::endl;
		}
	}

	//Your code goes here
};
