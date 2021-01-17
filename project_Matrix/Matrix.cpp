
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h> 
#include <filesystem>
#include "CError.h"

using namespace std;

template<typename T>
const int Matrix<T>::BOUND_ITERATION = 3677;
template<typename T>
const T Matrix<T>::DEFAULT_MATRIX_VAL = 0;
template<typename T>
const int Matrix<T>::DEFAULT_SIZE_X = 1;
template<typename T>
const int Matrix<T>::DEFAULT_SIZE_Y = 1;
template<typename T>
const int Matrix<T>::DEFAULT_EMPTY_MATRIX = 0;


template<typename T>
T add_el(T elem1, T elem2) { return elem1 + elem2; }
template<typename T>
T sub_el(T elem1, T elem2) { return elem1 - elem2; }
template<typename T>
T mul_el(T elem, T val) { return elem * val; }
template<typename T>
T pow_el(T elem, T val) { return pow(elem, val); }
template<typename T>
T min(T elem1, T elem2) { return (elem1 < elem2) ? elem1 : elem2; }


template<typename T>
Matrix<T>::Matrix() : matrix(NULL) {
	
	rows = DEFAULT_SIZE_Y;
	cols = DEFAULT_SIZE_X;
	alloc_matrix(rows, cols);
}


template<typename T>
Matrix<T>::Matrix(int row, int col):matrix(NULL) {
	
	rows = row;
	cols = col;
	alloc_matrix(rows, cols);
	set_all_matrix_val(DEFAULT_MATRIX_VAL);
}


template<typename T>
Matrix<T>::Matrix(int row, int col, T val) : matrix(NULL) {
	
	rows = row;
	cols = col;
	alloc_matrix(rows, cols);
	set_all_matrix_val(val);
}

template<typename T>
Matrix<T>::Matrix(const Matrix& other):matrix(NULL) {
	
	rows = other.rows;
	cols = other.cols;
	alloc_matrix(rows, cols);
	set_all_matrix_val(other);
}

template<typename T>
Matrix<T>::Matrix<T>(Matrix&& other) noexcept {

	rewrite_fields(other);
	clear_fields(other);
	//cout << "MOVE " << endl;
}


template<typename T>
Matrix<T>::~Matrix() {

	dealloc_matrix();
}

template<typename T> 
void Matrix<T>::set_all_matrix_val(T val) {

	for (int i = 0; i < get_num_of_rows(); i++)
	{
		for (int j = 0; j < get_num_of_columns(); j++)
			matrix[i][j] = val;
	}
}

template<typename T>
void Matrix<T>::set_all_matrix_val(const Matrix& other) {

	CError error;
	if (other.matrix != NULL) {
		set_size(other.rows, other.cols, false);

		for (int i = 0; i < other.rows; i++)
		{
			for (int j = 0; j < other.cols; j++)
				matrix[i][j] = other.matrix[i][j];
		}
	}
	else {
		error.set_error_code(EMPTY_MATRIX);
		error.set_message(CError::EMPTY_MATRIX_MSG);
	}
		
}


template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept {

	if (this != &other) 
	{
		if (matrix != NULL)
			dealloc_matrix();

		rewrite_fields(other);
		clear_fields(other);
	}
	//cout << "  moving op= " << endl;
	return *this;
}



template<typename T>
void Matrix<T>::rewrite_fields(Matrix<T>& other) {
	matrix = other.matrix;
	rows = other.rows;
	cols = other.cols;
}

template<typename T>
void Matrix<T>::clear_fields(Matrix<T>& other) {
	other.matrix = NULL;
	other.rows = 0;
	other.cols = 0;
}



template<typename T>
void Matrix<T>:: alloc_matrix(int num_row, int num_col)
{
	CError error;
	if (num_row < 1 || num_col < 1) {
	
		error.set_error_code(ERROR_INDEX_MATRIX);
		error.set_message(CError::ERROR_INDEX_MSG);
	}

	matrix = new T* [num_row];
	for (int i = 0; i < num_row; i++)
		matrix[i] = new T[num_col];
	
}

template<typename T>
void Matrix<T>::write_matrix()
{
	for (int i = 0; i < get_num_of_rows(); i++)
	{
		for (int j = 0; j < get_num_of_columns(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

template<typename T>
void Matrix<T>::dealloc_matrix()
{
	if (get_num_of_rows() >= 1 && matrix != NULL) {

		for (int i = 0; i < get_num_of_rows(); i++)
		{
			if (matrix[i] != NULL)
			{
				delete[] matrix[i];
				matrix[i] = NULL;
			}
		}

		delete[] matrix;
		matrix = NULL;
		cols = DEFAULT_EMPTY_MATRIX;
		rows = DEFAULT_EMPTY_MATRIX;
	}
}

template<typename T>
Matrix<T>& Matrix<T>:: operator=(const Matrix& other) {

	rows = other.rows;
	cols = other.cols;
	alloc_matrix(rows, cols);

	for (int i = 0; i < get_num_of_rows(); i++) {
		for (int j = 0; j < get_num_of_columns(); j++) 
			matrix[i][j] = other.matrix[i][j];
	}
	return *this;
}

template<typename T>
void Matrix<T>::transposition(){

	T** newMatrix = new T * [cols];

	for (int i = 0; i < cols; i++) {
		newMatrix[i] = new T[rows];
		
		for (int j = 0; j < rows; j++)
			newMatrix[i][j] = matrix[j][i];
	}

	for (int i = 0; i < rows; i++)
		delete matrix[i];
	delete matrix;

	matrix = newMatrix;
	int temp = cols;
	cols = rows;
	rows = temp;
	
}

template<typename T>
Matrix<T> Matrix<T>::transposition_copy() {

	Matrix transponed_matrix_copy(cols, rows);

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++)
			transponed_matrix_copy.matrix[i][j] = matrix[j][i];
	}

	return move(transponed_matrix_copy);

}


template<typename T>
T Matrix<T>::string_parse_to_T(string input) {
	T result = 0;
	return result;
}

template<>
int Matrix<int>::string_parse_to_T(string input) {
	return stoi(input);}

template<>
float Matrix<float>::string_parse_to_T(string input) {return stof(input);}

template<>
double Matrix<double>::string_parse_to_T(string input) {return stod(input);}


template<typename T>
void Matrix <T>::read_number_from_bufferString(string row_line, vector<T>* row, CError* error) {

	string number = "";
	char previous_char = ' ';

	for (char character : row_line) {

		if (character != ' ' ) {

			is_valid_char(character, error);

			if (character != '.' || previous_char != '.')
				number += character;
						
		}
		   
		else {

			if (number != "") {
				row->push_back(string_parse_to_T(number));
				number = "";
			}
		}

		previous_char = character;
	}
	if (number != "") 
		row->push_back(string_parse_to_T(number));	
}

template<typename T>
void Matrix<T>::is_valid_char(char& character, CError* error) {

	if (character == ',' || character == '.')
		character = '.';
	
	else if(!( '0' <= character  &&  character <= '9')){
		error->set_error_code(INVALID_CHAR);
		error->set_message(CError::INVALID_CHAR_MSG);

		throw Matrix_Exception(error->get_message(), error->get_error_code());
	}
	
}


template<typename T>
void Matrix<T>::import_matrix_from_txt_file(string filename_X) { //void

	vector<vector<T>> matrix_buffer;
	ifstream file_X;
	string line;
	CError error;

	file_X.open(filename_X);

	if (file_X.is_open()) {
		int row_num = 0; int col_num = 0;

		while (getline(file_X, line))
		{
			vector<T> row_temp;
			read_number_from_bufferString(line, &row_temp, &error);
			row_num++;
			matrix_buffer.push_back(row_temp);
			col_num = row_temp.size();
		}

		check_input_size(matrix_buffer, &error, col_num);

		if (error.get_error_code() != 0)
			throw Matrix_Exception(error.get_message(), error.get_error_code());

		set_size(row_num, col_num, false);
	
		for (int i = 0; i < row_num; i++) {
			for (int j = 0; j < col_num; j++) {
				matrix[i][j] = matrix_buffer[i].at(j);
			}
		}

		file_X.close();
	}
	else
		error.set_error_code(OPEN_FILE_ERROR);

	if (error.get_error_code() != 0)
		throw Matrix_Exception(error.get_message(), error.get_error_code());
}

template<typename T>
void Matrix<T>::check_input_size(vector<vector<T>>& matrix_buffer, CError* error, int& col_num) {

	int max_elem_number = 0;

	if (matrix_buffer.size() == 0)
		error->set_error_code(EMPTY_MATRIX);

	for (int i = 0; i < matrix_buffer.size(); i++) {

		if (max_elem_number < matrix_buffer.at(i).size())
			max_elem_number = matrix_buffer.at(i).size();
	}
	col_num = max_elem_number;

	fill_by_default_val(matrix_buffer, max_elem_number, error);
}



template<typename T>
void Matrix<T>::fill_by_default_val(vector<vector<T>>& matrix_buffer, int max_elem_number, CError* error) {

	for (int i = 0; i < matrix_buffer.size(); i++) {

		if (matrix_buffer.at(i).size() < max_elem_number) {
			error->set_info_code(FILLED_BY_DEFAULT_VAL);

			for (int j = 0; j <= max_elem_number - matrix_buffer.at(i).size(); j++)
				matrix_buffer[i].push_back(DEFAULT_MATRIX_VAL);
		}
	}
}

template<typename T>
Matrix<T> Matrix<T>::get_row(int chosen_row) {
	
	if (0 < chosen_row && chosen_row <= get_num_of_rows()) {

		Matrix picked_row(1, get_num_of_columns());

		for (int i = 0; i < get_num_of_columns(); i++)
			picked_row.set_elem_at(matrix[chosen_row][i], 0, i);

		return move(picked_row);
	}

	else {
		CError error;
		error.set_error_code(ERROR_INDEX_MATRIX);
		error.set_message(CError::ERROR_INDEX_MSG);
		return move(Matrix());
	}

}

template<typename T>
Matrix<T> Matrix<T>::get_col(int chosen_col) {

	if (0 < chosen_col && chosen_col <= get_num_of_columns()) {

		Matrix picked_col(get_num_of_rows(), 1);

		for (int i = 0; i < get_num_of_rows(); i++)
			picked_col.set_elem_at(matrix[i][chosen_col], i, 0);

		return move(picked_col);
	}
	else {
		CError error;
		error.set_error_code(ERROR_INDEX_MATRIX);
		error.set_message(CError::ERROR_INDEX_MSG);
		return move(Matrix());
	}
}

template<typename T>
Matrix<T> Matrix<T>::unit_matrix(T val) {

	if (rows == cols)
		return move(Matrix(rows, cols, val));

	else {

		CError error;
		error.set_error_code(ERROR_SIZE_MATRIX);
		error.set_message(CError::ERROR_SIZE_MSG);

		throw Matrix_Exception(error.get_message(), error.get_error_code());
	}
}

template<typename T>
T Matrix<T>::scalar_product(const Matrix<T>& other) 
{
	Matrix helperMtrx_this(*this);
	Matrix helperMtrx_other(other);

	if (helperMtrx_this.rows > 1)
		helperMtrx_this.transposition();

	if (helperMtrx_other.rows > 1)
		helperMtrx_other.transposition();
	

	if (helperMtrx_this.cols == helperMtrx_other.cols  && helperMtrx_this.rows == 1 && helperMtrx_other.rows == 1) {
		
		T res = 0;
		for (int i = 0; i < get_num_of_columns(); i++) 
			res += helperMtrx_this.matrix[0][i] * helperMtrx_other.matrix[0][i];
		
		return res;
	}
	else {
		CError error;
		error.set_error_code(ERROR_SIZE_MATRIX);
		error.set_message(CError::ERR0R_SIZE_MSG);

		throw Matrix_Exception(error.get_message(), error.get_error_code());
	}
}


template<typename T>
void Matrix<T>::set_elem_at(T val, int num_row, int num_col) {

	CError error;

	if (num_row >= get_num_of_rows() || num_col >= get_num_of_columns()) {

		error.set_error_code(ERROR_INDEX_MATRIX);
		error.set_message(CError::ERROR_INDEX_MSG);

	}
	else 
		matrix[num_row][num_col] = val;
}

template<typename T>
T  Matrix<T>::get_elem_at(int num_row, int num_col) {

	
	if (num_row >= get_num_of_rows() || num_col >= get_num_of_columns() ||
		num_row < 0 || num_col < 0) {

		CError error;
		error.set_error_code(ERROR_INDEX_MATRIX);
		error.set_message(CError::ERROR_INDEX_MSG);
		throw Matrix_Exception(error.get_message(), error.get_error_code());

	}
	else 
		return matrix[num_row][num_col];
	
}

template<typename T>
void Matrix<T>::set_size(int num_row, int num_col, bool rewrite_old_val) {

	CError error;

	if (num_row < 1 || num_col < 1) {

		error.set_error_code(ERROR_INDEX_MATRIX);
		error.set_message(CError::ERROR_INDEX_MSG);

	}
		
	else{

		T** newMatrix = new T * [num_row];

		for (int i = 0; i < num_row; i++) {
			newMatrix[i] = new T[num_col];

			if (rewrite_old_val ) {
				for (int k = 0; k < num_col; k++) {

					if (k >= rows || i >=cols)
						newMatrix[i][k] = DEFAULT_MATRIX_VAL;
					else
						newMatrix[i][k] = matrix[i][k];
				}

			}
			
		}
			dealloc_matrix();

			cols = num_col;
			rows = num_row;
			matrix = newMatrix;
		
	}
}

template<typename T>
Matrix<T> Matrix<T>::multiply_matrix(const Matrix& other, CError* error)
{
	if (cols == other.rows)
	{
		Matrix matrix3(cols, other.rows);

		for (int i = 0; i < matrix3.get_num_of_rows(); i++)
		{
			for (int j = 0; j < matrix3.get_num_of_columns(); j++)
			{
				for (int k = 0; k < get_num_of_columns(); k++)
					matrix3.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
			}
		}
		return move(matrix3);
	}
	else
		error->set_error_code(ERROR_SIZE_MATRIX);
		error->set_message(CError::ERR0R_SIZE_MSG);
		return move(Matrix());
}

template<typename T>
T  Matrix<T>::count(T elem1, T elem2, p_operation oper) {
	return oper(elem1, elem2);
}


template<typename T>
Matrix<T> Matrix<T>::traverse_matrix(p_operation oper, const Matrix<T>& other, int num_row, int num_col) {

	Matrix<T> matrix_res(num_row, num_col);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix_res.matrix[i][j] = count(matrix[i][j], other.matrix[i][j], oper);
		}
	}

	return matrix_res;
}


template<typename T>
Matrix<T> Matrix<T>::add_matrix(const Matrix& other, CError* error) {

		if (rows == other.rows && cols == other.cols)
			return move(traverse_matrix(&add_el, other, rows, cols));

		else
			error->set_error_code(ERROR_SIZE_MATRIX);
		    error->set_message(CError::ERR0R_SIZE_MSG);
			return move(Matrix());
}

template<typename T>
Matrix<T> Matrix<T>::subtract_matrix(const Matrix& other, CError* error) {

	if (rows == other.rows && cols == other.cols) 
		return move(traverse_matrix(&pow_el, other, rows, cols));
	
	else
		error->set_error_code(ERROR_SIZE_MATRIX);
		error->set_message(CError::ERR0R_SIZE_MSG);
		return  move(Matrix()); 

}

template<typename T>
Matrix<T> Matrix<T>::power_of_matrix(T power, CError* error) {


	if (rows == cols)
		return move(traverse_matrix(&pow_el,  Matrix(rows, cols, power), rows, cols));
	
	else
		error->set_error_code(ERROR_SIZE_MATRIX);
		error->set_message(CError::ERR0R_SIZE_MSG);
		return move(Matrix());
}


template<typename T>
Matrix<T> Matrix<T>::multiply_matrix(const T& number)
{
	return traverse_matrix(&mul_el, Matrix(rows, cols, number), rows, cols);
}








 
