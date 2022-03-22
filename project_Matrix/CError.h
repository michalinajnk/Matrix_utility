#include <stdexcept>
using namespace std;

#pragma once
#define NO_ERROR 0
#define EMPTY_MATRIX 25
#define ERROR_SIZE_MATRIX 50
#define ERROR_INDEX_MATRIX 75
#define OPEN_FILE_ERROR 100
#define FILE_NOT_FOUND_ERROR 125
#define INVALID_CHAR 150 
#define INVALID_INPUT_STRING 175
#define FILLED_BY_DEFAULT_VAL 1025
#define NO_INFO 1000


class CError {	
	
public:
	static const string EMPTY_MATRIX_MSG;
	static const string INVALID_CHAR_MSG;
	static const string ERR0R_SIZE_MSG;
	static const string ERROR_INDEX_MSG;
	static const string ERROR_OPENFILE_MSG;
	static const string ERROR_FILENOTFOUND_MSG;
	static const string INVALID_INPUT_STRING_MSG;

	CError() {
		error_code = NO_ERROR;
		message = "";
		info_code = NO_INFO;
	}

	CError(const string msg, int err_code)
	{
		error_code = err_code;
		message = msg;
	}

	int get_info_code() { return info_code; }
	void set_info_code(int new_info) { info_code = new_info; }

	int get_error_code() { return error_code; }
	void set_error_code(int new_err_code) { error_code = new_err_code; }

	string get_message() { return message; }
	void set_message(string msg) { message = msg; }

private:

	int error_code;
	int info_code;
	string message;

};

const string CError::EMPTY_MATRIX_MSG = "The matrix is empty";
const string CError::INVALID_CHAR_MSG = "The char is not a number";
const string CError::ERR0R_SIZE_MSG = "Wrong size of the input matrix";
const string CError::ERROR_INDEX_MSG = "The index is out of bound";
const string CError::ERROR_OPENFILE_MSG = "File cannot be opened";
const string CError::ERROR_FILENOTFOUND_MSG = "The file is not found";
 const string  CError::INVALID_INPUT_STRING_MSG = "Prohibited string occurs";


class Matrix_Exception {

public:
	Matrix_Exception() { 
		error_code = NO_ERROR;
		message = "";
	}

	Matrix_Exception(string msg, int err_code) {
		error_code = err_code;
		message = msg;
	}

	int get_error_code() { return error_code; }
	string get_message() { return message; }

private:

	int error_code;
	string message;

};