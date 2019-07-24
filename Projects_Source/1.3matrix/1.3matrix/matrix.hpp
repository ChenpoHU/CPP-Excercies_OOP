#pragma once
#include <vector>
#include <ostream>
#include <stdlib.h>

class MatDimExcep : public std::exception {
	const char* msg;
public:
	MatDimExcep(const char* _msg) :msg(_msg) {
		// this->msg = _msg;
	}

	const char* what() const throw () {
		return msg;
	}
};

template<typename T>
struct Matrix {
	int rows, columns; // instance variables
	T* values; // instance variable

	~Matrix() { // destructor
		delete[] values;
	}

	Matrix(int _rows, int _columns) :rows(_rows), columns(_columns) { // constructor
		values = new T[rows * columns];
	}

	Matrix(std::initializer_list<std::initializer_list<T>> list) :Matrix(list.size(), list.begin()->size()) { // constructor
		auto rowIter = list.begin();
		for(int y = 0; y < rows; ++y) {
			if(rowIter->size() != columns)
				throw new MatDimExcep("initializer rows have different lengths"); // 2. Extend the constructor to use MatDimExcep and report error in case anything is wrong
			auto columnIter = (*rowIter++).begin();
			for(int x = 0; x < columns; ++x)
				values[y * columns + x] = *columnIter++;
		}
	}

	Matrix(const Matrix& other) :Matrix(other.rows, other.columns) { // constructor
		memcpy(values, other.values, sizeof(T) * rows * columns);
	}

	int get_rows_nb() {
		return rows;
	}

	int get_cols_nb() {
		return columns;
	}

	T& get_at(int x, int y) {
		if(x < 0 || y < 0 || x >= columns || y >= rows)
			throw new MatDimExcep("index out of bounds");
		return values[y*columns+x];
	}

	bool add(const Matrix& other) {
		// check if the matrix has appropriate number of elements 
		if(rows != other.rows || columns != other.columns)
			throw new MatDimExcep("matrix dimensions mismatch");
		for(int y = 0; y < rows; ++y)
			for(int x = 0; x < columns; ++x)
				values[y*columns+x] += other.values[y*columns+x];
		return true;
	}

	bool multiply(const Matrix& other) {
		// check if the matrix has appropriate number of elements 
		if(columns != other.rows)
			throw new MatDimExcep("matrix dimensions mismatch");
		Matrix result(other.columns, rows);
		for(int y = 0; y < result.rows; ++y)
			for(int x = 0; x < result.columns; ++x) {
				T& cell = result.values[y * result.columns + x];
				cell = 0;
				for(int i = 0; i < columns; ++i)
					cell += values[y * columns + i] * other.values[i * other.columns + x];
			}
		rows = result.rows;
		columns = result.columns;
		std::swap(values, result.values);
		return true;
	}

	void multiply_s(T scalar) {
		for(int y = 0; y < rows; ++y)
			for(int x = 0; x < columns; ++x)
				values[y*columns+x] *= scalar;
	}

	std::vector<T> get_row(int y) {
		if(y < 0 || y >= rows)
			throw new MatDimExcep("index out of bounds");
		std::vector<T> result(columns); // initialise a vector with size columns
		for(int x = 0; x < columns; ++x)
			result[x] = values[y*columns+x];
		return result;
	}

	std::vector<T> get_col(int x) {
		if(x < 0 || x >= columns)
			throw new MatDimExcep("index out of bounds");
		std::vector<T> result(rows);
		for(int y = 0; y < rows; ++y)
			result[y] = values[y*rows+x];
		return result;
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Matrix<T>&	matrix) {
	for(int y = 0; y < matrix.rows; ++y) {
		for(int x = 0; x < matrix.columns; ++x)
			stream << matrix.values[y*matrix.columns+x] << " ";
		stream << std::endl;
	}
	return stream;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vector) {
	for(T element : vector)
		stream << element << " ";
	return stream;
}

/*template<typename T>
void debugPrintVector(const std::vector<T>& vector) {
	for(T element : vector)
		std::cout << element << " ";
	std::cout << std::endl;
}*/