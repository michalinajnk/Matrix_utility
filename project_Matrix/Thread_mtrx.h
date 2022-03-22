/*
#include <thread>
using namespace std;

const int THREADS_NUMBER = 4;
thread threads[THREADS_NUMBER];

typedef T (*thread_op)(int iterator, const Matrix<T>& other);

Matrix<T> multiply_threading(const int thread_number, const Matrix<T>& other) {
    // Calculate workload  m1 - this
    const int n_elements = (MATRIX_SIZE * MATRIX_SIZE);
    const int n_operations = n_elements / THREADS_NUMBER;
    const int rest_operations = n_elements % THREADS_NUMBER;
    Matrix<T> result;

    int start_op, end_op;

    if (thread_number == 0) {
        // First thread does more job
        start_op = n_operations * thread_number;
        end_op = (n_operations * (thread_number + 1)) + rest_operations;
    }
    else {
        start_op = n_operations * thread_number + rest_operations;
        end_op = (n_operations * (thread_number + 1)) + rest_operations;
    }

    for (int op = start_op; op < end_op; ++op) {
        const int row = op % MATRIX_SIZE;
        const int col = op / MATRIX_SIZE;
       
        for(int i = 0; i < MATRIX_SIZE; ++i) {
          
           result.matrix[row][col] += matrix[row][i] *other.matrix[i][col];
        }
    }
    return move(result);
}

Matrix<T> adding_threading(const int thread_number, const Matrix<T>& other) {
    // Calculate workload  m1 - this
    const int n_elements = (MATRIX_SIZE * MATRIX_SIZE);
    const int n_operations = n_elements / THREADS_NUMBER;
    const int rest_operations = n_elements % THREADS_NUMBER;
    Matrix<T> result;

    int start_op, end_op;

    if (thread_number == 0) {
        // First thread does more job
        start_op = n_operations * thread_number;
        end_op = (n_operations * (thread_number + 1)) + rest_operations;
    }
    else {
        start_op = n_operations * thread_number + rest_operations;
        end_op = (n_operations * (thread_number + 1)) + rest_operations;
    }

    for (int op = start_op; op < end_op; ++op) {
        const int row = op % MATRIX_SIZE;
        const int col = op / MATRIX_SIZE;

        for (int i = 0; i < MATRIX_SIZE; ++i) {

            result.matrix[row][col] = matrix[row][i] + other.matrix[i][col];
        }
    }
    return move(result);
}


Matrix<T> substracting_matrix(const int thread_number, const Matrix<T>& other) {
    // Calculate workload  m1 - this
    const int n_elements = (MATRIX_SIZE * MATRIX_SIZE);
    const int n_operations = n_elements / THREADS_NUMBER;
    const int rest_operations = n_elements % THREADS_NUMBER;
    Matrix<T> result;

    int start_op, end_op;

    if (thread_number == 0) {
        // First thread does more job
        start_op = n_operations * thread_number;
        end_op = (n_operations * (thread_number + 1)) + rest_operations;
    }
    else {
        start_op = n_operations * thread_number + rest_operations;
        end_op = (n_operations * (thread_number + 1)) + rest_operations;
    }

    for (int op = start_op; op < end_op; ++op) {
        const int row = op % MATRIX_SIZE;
        const int col = op / MATRIX_SIZE;

        for (int i = 0; i < MATRIX_SIZE; ++i) {

            result.matrix[row][col] = matrix[row][i] - other.matrix[i][col];
        }
    }
    return move(result);
}


void execute_operation_with_threads(const Matrix<T>& other, thread_op *oper) {
    for (int i = 0; i < THREADS_NUMBER; ++i) {
        // Initialize each thread with the function responsible of multiplying only a part of the matrices
        threads[i] = thread(oper, i, other);
    }

    for (int i = 0; i < THREADS_NUMBER; ++i) {
        // Wait until each thead has finished
        threads[i].join();
    }
}

*/