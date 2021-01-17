
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "CError.h"
using namespace std;


template<typename T>
class Matrix {

	static const int BOUND_ITERATION;
	static const T DEFAULT_MATRIX_VAL;
	static const int DEFAULT_EMPTY_MATRIX;
	static const int DEFAULT_SIZE_X;
	static const int DEFAULT_SIZE_Y;
	
public:

	void import_matrix_from_txt_file(string filename_X);
	T string_parse_to_T(string input);
	void read_number_from_bufferString(string row_line, vector<T>* v, CError* error);
	void check_input_size(vector <vector<T>>& v, CError *error, int& col_num);
	void is_valid_char(char& character, CError *error);
	void fill_by_default_val(vector<vector<T>>& matrix_buffer, int max_elem_number, CError* error);

	Matrix();
	Matrix(int rows, int cols);
	Matrix(int row, int col, T val);
	~Matrix();
    Matrix(const Matrix& other);
    Matrix(Matrix&& other)  noexcept;

	Matrix& operator=(Matrix&& other) noexcept;
	Matrix& operator=(const Matrix& other);

	Matrix operator+(const Matrix& other)  {
		CError error;
		Matrix<T> result = move(add_matrix(other, &error));

		if (error.get_error_code() != 0)
			throw Matrix_Exception(error.get_message(),error.get_error_code());

		return result;
		
	}
	Matrix add_matrix(const Matrix& other, CError* error);

	Matrix  operator-(const Matrix& other)  {
		CError error;
		Matrix<T> result = move(subtract_matrix(other, &error));

		if (error.get_error_code() != 0)
			throw Matrix_Exception(error.get_message(),error.get_error_code());

		return result;

	}
	Matrix subtract_matrix(const Matrix& other, CError* error);

	Matrix operator*(const Matrix& other)  {
		CError error;
		Matrix<T> result = move(multiply_matrix(other, &error));

		if (error.get_error_code() != 0)
			throw Matrix_Exception(error.get_message(), error.get_error_code() );

		return result;
	}
	Matrix multiply_matrix(const Matrix& other, CError* error);
	

	Matrix operator*(T number) {
		return multiply_matrix(number);
	}

	Matrix multiply_matrix(const T& number);

	Matrix operator^(T power) {

		CError error;
		Matrix<T> result = move(power_of_matrix(power, &error));
		if (error.get_error_code() != 0)
			throw Matrix_Exception(error.get_message(), error.get_error_code());

		return result;
	}
	Matrix power_of_matrix(T power, CError* error);

	void transposition();
	Matrix transposition_copy();
	Matrix unit_matrix(T val);
	T scalar_product(const Matrix<T>& other);

	
	void alloc_matrix(int num_row, int num_col);
	void dealloc_matrix();
	void write_matrix(); 
	void rewrite_fields(Matrix<T>& other);  
	void clear_fields(Matrix<T>& other);   

	
	Matrix get_col(int num_col);
	Matrix get_row(int num_row);
	int get_num_of_columns() { return cols; };
	int get_num_of_rows() { return rows; };
	T get_elem_at(int num_row, int num_col);
	
	void set_elem_at(T val, int num_row, int num_col);  //SPRAWDZ 
	void set_all_matrix_val(T val);
	void set_all_matrix_val(const Matrix& other); 
	void set_size(int num_row, int num_col, bool rewrite_old_val); //SPRAWDZ
	
	
	typedef T(*p_operation)(T elem1, T elem2);
	T count(T elem1, T elem2, p_operation oper);
	Matrix traverse_matrix(p_operation oper, const Matrix<T>& other, int num_row, int num_col);

	
	
private:
	T** matrix;
	int rows;
	int cols;
};


#include "Matrix.cpp";