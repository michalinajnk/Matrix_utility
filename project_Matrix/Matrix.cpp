
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "CError.h"


using namespace std;


template<typename T>
const T Matrix<T>::DEFAULT_MATRIX_VAL = 0;
template<typename T>
const int Matrix<T>::DEFAULT_SIZE_X = 1;
template<typename T>
const int Matrix<T>::DEFAULT_SIZE_Y = 1;
template<typename T>
const int Matrix<T>::DEFAULT_EMPTY_MATRIX = 0;

template<typename T>
const string Matrix<T>::PROHIBITED_STRING = "3^14";

template<typename T>
const int Matrix<T>::SIGN_OF_ALGEBRAIC_COMPLEMENT = -1;
template<typename T>
const T Matrix<T>::OUT_OF_BOUND_VAL = 0;
template<>
const float Matrix<float>::OUT_OF_BOUND_VAL = FLT_MAX;
template<>
const double Matrix<double>::OUT_OF_BOUND_VAL = DBL_MAX;
template<>
const int Matrix<int>::OUT_OF_BOUND_VAL = INT_MAX;





template<typename T>
T add_el(T elem1, T elem2) { return elem1 + elem2; }
template<typename T>
T sub_el(T elem1, T elem2) { return elem1 - elem2; }
template<typename T>
T mul_el(T elem, T val) { return elem * val; }

template<typename T>
T min(T elem1, T elem2) { return (elem1 < elem2) ? elem1 : elem2; }




template<typename T>
T pow_el_aux(T base, T power, T& accum) {

	if (power == 1)
		return accum;
	else {
		accum = accum * base;
		return pow_el_aux(base, --power, accum);
	}

}

template<typename T>
T pow_el(T base, T power) {
	T accum = base;
	return pow_el_aux(base, power, accum);
}



template<typename T>
Matrix<T>::Matrix() : matrix(NULL) {
	
	height = DEFAULT_SIZE_Y;
	width = DEFAULT_SIZE_X;
	alloc_matrix(width, height);
}


template<typename T>
Matrix<T>::Matrix(int width_mtrx, int height_mtrx):matrix(NULL) {
	
	height = height_mtrx;
	width = width_mtrx;
	alloc_matrix(width, height);
	set_all_matrix_val(DEFAULT_MATRIX_VAL);
}


template<typename T>
Matrix<T>::Matrix(int width_mtrx, int height_mtrx, T val) : matrix(NULL) {
	
	height = height_mtrx;
	width = width_mtrx;
	alloc_matrix(width, height);
	set_all_matrix_val(val);
}

template<typename T>
Matrix<T>::Matrix(const Matrix& other):matrix(NULL) {
	
	height = other.height;
	width = other.width;
	alloc_matrix(other.width, other.height);
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

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			matrix[i][j] = val;
	}
}

template<typename T>
void Matrix<T>::set_all_matrix_val(const Matrix& other) {

	CError error;
	if (other.matrix != NULL) {
		set_size(other.width, other.height, true);

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
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
	return *this;
}




template<typename T>
void Matrix<T>::rewrite_fields(Matrix<T>& other) {
	matrix = other.matrix;
	height = other.height;
	width = other.width;
}

template<typename T>
void Matrix<T>::clear_fields(Matrix<T>& other) {
	
	other.matrix = NULL;
	other.width = 0;
	other.height = 0;
}



template<typename T>
void Matrix<T>:: alloc_matrix(int width_mtrx, int height_mtrx)
{
	CError error;
	if (width_mtrx < 1 || height_mtrx < 1) {
	
		error.set_error_code(ERROR_INDEX_MATRIX);
		error.set_message(CError::ERROR_INDEX_MSG);
	}

	matrix = new T* [height_mtrx];  
	for (int i = 0; i < height_mtrx; i++)
		matrix[i] = new T[width_mtrx];
	
}

template<typename T>
void Matrix<T>::write_matrix(){

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	
		
}

template<typename T>
void Matrix<T>::dealloc_matrix()
{
	if (width >= 1 && matrix != NULL) {

		for (int i = 0; i < height; i++)
		{
			if (matrix[i] != NULL)
			{
				delete[] matrix[i];
				matrix[i] = NULL;
			}
		}
		delete[] matrix;

		matrix = NULL;
		width = DEFAULT_EMPTY_MATRIX;
		height = DEFAULT_EMPTY_MATRIX;
	}
}

template<typename T>
Matrix<T>& Matrix<T>:: operator=(const Matrix& other) {  

	dealloc_matrix();

	height = other.height;
	width = other.width;

	T** newMatrix = new T * [height];
	for (int i = 0; i < height; i++) {
		newMatrix[i] = new T[width];

		for (int j = 0; j < width; j++) 
			newMatrix[i][j] = other.matrix[i][j];
	}

	matrix = newMatrix;
	return *this;
}

template<typename T>
void Matrix<T>::transposition(){

	int new_width = get_height();
	int new_height = get_width();


	T** newMatrix = new T * [new_height];

	for (int i = 0; i < new_height; i++)
		newMatrix[i] = new T[new_width];
	
	
	for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++)
			newMatrix[i][j] = matrix[j][i];
	}

	dealloc_matrix();

	width = new_width;
	height = new_height;
	matrix = newMatrix;
	
}

template<typename T>
Matrix<T> Matrix<T>::transposition_copy() {

	Matrix transponed_matrix_copy(height, width);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			transponed_matrix_copy.matrix[j][i] = matrix[i][j];
	}

	return transponed_matrix_copy;

}


template<typename T>
T Matrix<T>::string_parse_to_T(string input) {
	T result = 0;
	return result;
}

template<>
int Matrix<int>::string_parse_to_T(string input) {return stoi(input);}

template<>
float Matrix<float>::string_parse_to_T(string input) {return stof(input);}

template<>
double Matrix<double>::string_parse_to_T(string input) {return stod(input);}


template<typename T>
void Matrix <T>::read_number_from_bufferString(string row_line, vector<T>* row, CError* error) {

	string number = "";
	char previous_char = ' ';

	for (char character : row_line) {

		if (character !=' ') {

			is_valid_char(character, error); 
			if (character != '.' || previous_char != '.')
				number += character;			
		}
		   
		else {

			if (number != "" && error->get_error_code() == 0 ) {
				row->push_back(string_parse_to_T(number));
				number = "";
			}
		}

		previous_char = character;
	}
	if (number != "" && error->get_error_code() == 0)
		row->push_back(string_parse_to_T(number));	
}

template<typename T>
void Matrix<T>::is_valid_char(char& character, CError* error) {

	if (character == ',' || character == '.') {
		character = '.';
	}
	
	else if(!( '0' <= character  &&  character <= '9')){
		error->set_error_code(INVALID_CHAR);
		error->set_message(CError::INVALID_CHAR_MSG);
	}
	
}

template<typename T> 
void Matrix<T>::import_matrix_from_buffer(string filename_X, T value_to_fill, vector<vector<T>>& matrix_buffer) {

	ifstream file_X;
	string line;
	CError error;

	file_X.open(filename_X);

	if (file_X.is_open()) {
		int new_width = 0;
		int new_height = 0;

		while (getline(file_X, line))
		{
			vector<T> row_temp;
			read_number_from_bufferString(line, &row_temp, &error);
			new_height++;
			matrix_buffer.push_back(row_temp);
			new_width = row_temp.size();
		}

		check_input_size(matrix_buffer, &error, new_width, value_to_fill);

		if (error.get_error_code() == 0) {

			set_size(new_width, new_height, false);

			for (int i = 0; i < new_height; i++) {
				for (int j = 0; j < new_width; j++) {
					matrix[i][j] = matrix_buffer[i].at(j);
				}
			}
		}

		file_X.close();
	}
	else if (error.get_error_code() == 0)
		error.set_error_code(OPEN_FILE_ERROR);

}

template<typename T>
void Matrix<T>::append_matrix_from_file(string filename_X, T value_to_fill) {

	vector<vector<T>> matrix_buffer;

	for (int i = 0; i < height; i++) {
		vector<T> row_temp;
		for (int j = 0; j < width; j++) {
			row_temp.push_back(matrix[i][j]);
		}
		matrix_buffer.push_back(row_temp);
	}
	
	import_matrix_from_buffer(filename_X, value_to_fill, matrix_buffer);
	
}


template<typename T>
void Matrix<T>::import_matrix_from_txt_file(string filename_X, T value_to_fill) { 

	vector<vector<T>> matrix_buffer;
	import_matrix_from_buffer(filename_X, value_to_fill, matrix_buffer);
	
}

template<typename T>
void Matrix<T>::check_input_size(vector<vector<T>>& matrix_buffer, CError* error, int& width_mtrx, T& default_val) {

	int max_elem_number = 0;

	if (matrix_buffer.size() == 0)
		error->set_error_code(EMPTY_MATRIX);

	for (int i = 0; i < matrix_buffer.size(); i++) {

		if (max_elem_number < matrix_buffer.at(i).size())
			max_elem_number = matrix_buffer.at(i).size();
	}
	width_mtrx = max_elem_number;

	fill_by_default_val(matrix_buffer, max_elem_number, error, default_val);
}



template<typename T>
void Matrix<T>::fill_by_default_val(vector<vector<T>>& matrix_buffer, int max_elem_number, CError* error, T& default_val) {

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
	
	if (0 < chosen_row && chosen_row <= get_height()) {

		Matrix picked_row(get_width(),1);

		for (int i = 0; i < width; i++)
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

	if (0 < chosen_col && chosen_col <= get_width()) {

		Matrix picked_col(1, get_height());

		for (int i = 0; i < height; i++)
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

	if (height == width)
		return move(Matrix(width, height, val));

	else {

		CError error;
		error.set_error_code(ERROR_SIZE_MATRIX);
		error.set_message(CError::ERROR_SIZE_MSG);

		return move(Matrix());
	}
}

template<typename T>
T Matrix<T>::scalar_product(const Matrix<T>& other) {
	Matrix helperMtrx_this(*this);
	Matrix helperMtrx_other(other);

	if (helperMtrx_this.height > 1)
		helperMtrx_this.transposition();

	if (helperMtrx_other.height > 1)
		helperMtrx_other.transposition();
	

	if (helperMtrx_this.width == helperMtrx_other.width  && helperMtrx_this.height == 1 && helperMtrx_other.height == 1) {
		
		T res = 0;
		for (int i = 0; i < width; i++) 
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

	if (num_row >= get_height() || num_col >= get_width()) {

		error.set_error_code(ERROR_INDEX_MATRIX);
		error.set_message(CError::ERROR_INDEX_MSG);

	}
	else 
		matrix[num_row][num_col] = val;
}

template<typename T>
T  Matrix<T>::get_elem_at(int num_row, int num_col) {

	
	if (num_row >= get_height() || num_col >= get_width() ||
		num_row < 0 || num_col < 0) {

		CError error;
		error.set_error_code(ERROR_INDEX_MATRIX);
		error.set_message(CError::ERROR_INDEX_MSG);
		return OUT_OF_BOUND_VAL;

	}
	else 
		return matrix[num_row][num_col];	
}

template<typename T>
void Matrix<T>::set_size(int new_width, int new_height, bool rewrite_old_val) {

	CError error;

	if (new_width < 1 || new_height < 1) {

		error.set_error_code(ERROR_INDEX_MATRIX);
		error.set_message(CError::ERROR_INDEX_MSG);

	}
		
	else{	

		T** newMatrix = new T * [new_height]; 

		for (int i = 0; i < new_height; i++) {
			newMatrix[i] = new T[new_width];

			if (rewrite_old_val ){
				for (int k = 0; k < new_width; k++) {

					if (k >= width || i >= height)
						newMatrix[i][k] = DEFAULT_MATRIX_VAL;
					else
						newMatrix[i][k] = matrix[i][k];
				}

			}
			
		}

		dealloc_matrix();

		width = new_width;
		height = new_height;
		matrix = newMatrix;
		
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 template<typename T>
 T Matrix<T>::det_2x2(){
	
	return get_elem_at(0,0)* get_elem_at(1,1) - get_elem_at(0,1) * get_elem_at(1,0);
	
 }

 template<typename T>
 T Matrix<T>::det_3x3() {
	 
	 T sum1 = 1, sum2 = 1, sum3 = 1;
	 T sub1 = 1, sub2 = 1, sub3 = 1;
	
	 for (int i = 0; i < 3; i++) {

		 sum1 = sum1 * matrix[i][i];
		 sum2 = sum2 * matrix[i][(i + 1) % 3];
		 sum3 = sum3 * matrix[i][(i + 2) % 3];
	 }

	 for (int i = 0; i < 3 ; i++) {

		sub1 = sub1 * matrix[i][(2*i)%3];  // 00 12 21  
		sub2 = sub2 * matrix[i][(2*i + 2) % 3]; ///02 11 20
		sub3 = sub3 * matrix[i][(2*i + 1) % 3];  ///   01 10 22 
	 }

	 return sum1 + sum2 + sum3 - sub1 - sub2 - sub3;
 }

 template<typename T>
 T Matrix<T>::det_experiment() {



 }

 template<typename T>
 T Matrix<T>::det_bigger(vector<Matrix<T>>& all_matrix_to_count) {

	 int size_X = get_height();
	 T result = 0;
	 int counter = 1;
	while(size_X > 3) {

		if(counter == 1)
		add_all_algebraic_complement(all_matrix_to_count, size_X);

		counter++;
		size_X--;

		if (size_X > 3) {
			for (int i = 0; i < all_matrix_to_count.size(); i++) {

				Matrix<T> temp_mtrx = all_matrix_to_count.at(i);
				delete_matrix(i, all_matrix_to_count);
				temp_mtrx.add_all_algebraic_complement(all_matrix_to_count, size_X);

			}
		}
	}
	
	for(Matrix<T> matrix : all_matrix_to_count) 
		result += matrix.det_3x3();
	
	return result;
 }

 template<typename T>
 void Matrix<T>::add_all_algebraic_complement(vector<Matrix<T>>& all_matrix_to_count, int& size_X) {

	 for (int i = 0; i < size_X; i++) {
		 for (int j = 0; j < size_X; j++) {

			 Matrix<T> toAdd = algebraic_complement(i, j);
			 toAdd.set_sign_of3x3(pow_el(-1, i + j + 2));
			 all_matrix_to_count.push_back(toAdd);
		 }
	 }
 }


template<typename T>
T Matrix<T>::det_matrix()
{
	CError error;

	if (height == width) {

		if (height == 1)
			return get_elem_at(0, 0);

		else if (height == 2)
			return det_2x2();

		else if (height == 3)
			return det_3x3();

		else {

			T result = 1;

			if (is_diagonal_matrix()) {

				for (int i = 0; i < width; i++)
					result = result * matrix[i][i];
				return result;
			}
			else {
				if (is_det_zero())
					return DEFAULT_MATRIX_VAL;

				else {
					vector<Matrix<T>> container;
					return det_bigger(container);
				}

			}

		}
	else {
		error.set_error_code(ERROR_SIZE_MATRIX);
		error.set_message(CError::ERR0R_SIZE_MSG);
		return T();
	}

	}
}


template<typename T>
Matrix<T> Matrix<T>::multiply_matrix(const Matrix& other, CError* error)
{
	if (width == other.height)
	{
		Matrix result(width, other.height);

		for (int i = 0; i < result.get_height(); i++)
		{
			for (int j = 0; j < result.get_width(); j++)
			{
				for (int k = 0; k < result.get_width(); k++)
					result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
			}
		}
		return move(result);
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
Matrix<T> Matrix<T>::traverse_matrix(p_operation oper, const Matrix<T>& other, int new_width, int new_height) {

	Matrix<T> matrix_res(new_width, new_height);

	for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++) {
			matrix_res.matrix[i][j] = count(matrix[i][j], other.matrix[i][j], oper);
		}
	}

	return move(matrix_res);
}


template<typename T>
Matrix<T> Matrix<T>::add_matrix(const Matrix& other, CError* error) {

		if (height == other.height && width == other.width)
			return move(traverse_matrix(&add_el, other, width, height));

		else
			error->set_error_code(ERROR_SIZE_MATRIX);
		    error->set_message(CError::ERR0R_SIZE_MSG);
			return move(Matrix());
}

template<typename T>
Matrix<T> Matrix<T>::subtract_matrix(const Matrix& other, CError* error) {

	if (height == other.height && width == other.width) 
		return move(traverse_matrix(&sub_el, other, width, height));
	
	else
		error->set_error_code(ERROR_SIZE_MATRIX);
		error->set_message(CError::ERR0R_SIZE_MSG);
		return  move(Matrix()); 

}

template<typename T>
Matrix<T> Matrix<T>::power_of_matrix(T power, CError* error) {


	if (height == width)
		return move(traverse_matrix(&pow_el,  Matrix(width, height, power), width, height));
	
	else
		error->set_error_code(ERROR_SIZE_MATRIX);
		error->set_message(CError::ERR0R_SIZE_MSG);
		return move(Matrix());
}


template<typename T>
Matrix<T> Matrix<T>::multiply_matrix(const T& number)
{
	return traverse_matrix(&mul_el, Matrix(width, height, number), width, height);
}

template<typename T>
bool Matrix<T>::is_diagonal_matrix() {

	T to_cmpare = get_elem_at(0, 0);
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == j) {
				if (matrix[i][j] != to_cmpare)
					return false;

			}
			else if (matrix[i][j] != DEFAULT_MATRIX_VAL)
				return false;	
		}
	}

	return true;
}


template<typename T>
bool Matrix<T>::is_det_zero() {

	for (int i = 0; i < width; i++) {

		if (get_col(i).has_the_same_el())
			return true;
	}

	for (int i = 0; i < height; i++) {

		if (get_row(i).has_the_same_el())
			return true;
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height; j++) {

			if ( i != j && get_row(i).are_the_same_matrices(get_row(j)))
				return true;
		}
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < width; j++) {

			if (i != j && get_col(i).are_the_same_matrices(get_col(j)))
				return true;
		}
	}

	return false;
}



template<typename T>
bool Matrix<T>::has_the_same_el() {

	T to_cmpare = get_elem_at(0, 0);

	for (int i = 0; i <height; i++) {
		for (int j = 0; j < width; j++) {
			if (matrix[i][j] != to_cmpare)
				return false;
		}
	}
	return true;
}


template<typename T>
bool Matrix<T>::are_the_same_matrices(const Matrix<T>& other) {

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (matrix[i][j] !=other.matrix[i][j])
				return false;
		}
	}
	return true;
}




/////////////////////////////////////////////////////////////////////
template<typename T>
Matrix<T> Matrix<T> ::algebraic_complement(int num_row, int num_col) {


	if (num_row >= get_height() || num_col >= get_width() ||
		num_row < 0 || num_col < 0) {

		CError error;
		error.set_error_code(ERROR_INDEX_MATRIX);
		error.set_message(CError::ERROR_INDEX_MSG);
		return move(Matrix());

	}
	else
	{
		int height_mtrx = get_height() - 1;
		int width_mtrx = get_width() - 1;

		Matrix<T> alg_complement(*this);
		

		for (int i = 0; i < alg_complement.height; i++) {
			if (i >= num_row && i + 1 < alg_complement.height) {
				for (int j = 0; j < alg_complement.width; j++)
					alg_complement.matrix[i][j] = matrix[i + 1][j];
			}
		}


		 alg_complement.set_size(width, height_mtrx, true);



		 alg_complement.transposition();

		for (int j = 0; j < alg_complement.height; j++) {
			if (j >= num_col && j + 1 < alg_complement.height) {
				for (int k = 0; k < alg_complement.width; k++)
					alg_complement.matrix[j][k] = alg_complement.matrix[j + 1][k];
			}
		}

		alg_complement.set_size(height_mtrx, width_mtrx, true);
		alg_complement.transposition();

		
		return alg_complement;
	}
			
}



 
