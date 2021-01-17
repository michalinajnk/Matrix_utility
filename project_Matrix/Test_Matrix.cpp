#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Matrix.h";
using namespace std;

int main() {

  
    Matrix<int> matrix;
    matrix.import_matrix_from_txt_file("matrix2.txt");
    matrix.write_matrix();
   
    Matrix<int> matrix3;
    matrix3.import_matrix_from_txt_file("matrix.txt"); 
    matrix3.write_matrix();
   
    Matrix<int> result;
    result = matrix3 + matrix;
    cout << "After adding Matrix: " << endl;
    result.write_matrix();

    Matrix<int> result2;
    result2 = result - matrix3;

    cout << "After substracting Matrix: " << endl;
    result2.write_matrix();
    

    Matrix<int> result_mul;
    result_mul = matrix3 * matrix;
    cout << "After multiplication Matrix: " << endl;
    result_mul.write_matrix();

    Matrix<int> result_mul_number;
    int number = 5;
    result_mul_number = matrix3 * number;

    cout << "Multiplied Matrix by a number" << endl;
    result_mul_number.write_matrix();


    
    result_mul_number.transposition();
    cout << "After transposition Matrix: " << endl;
    result_mul_number.write_matrix();

   
    Matrix<int> sec_col;
    sec_col = result_mul_number.get_col(2);

    cout << "Vector from second column" << endl;
    sec_col.write_matrix();

    Matrix<int> sec_row;
    sec_row = result_mul_number.get_row(2);

    cout << "Vector from second row" << endl;
    sec_row.write_matrix();

    cout << endl;
 
    cout << "Power of Matrix" << endl;

    Matrix<int> res_mtrx;
    res_mtrx = result_mul_number ^ 3;
    res_mtrx.write_matrix();

    cout << endl;
    res_mtrx.transposition();
    res_mtrx.write_matrix();

    cout << endl;
    res_mtrx.set_size(2, 2, true);
    res_mtrx.write_matrix();
  

    cout << endl;
    cout << "First vector: " << endl;
    Matrix<int> wektor1;
    wektor1.import_matrix_from_txt_file("wektor1.txt");
    wektor1.write_matrix();

    cout << endl;
    cout << "Second vector: " << endl;
    Matrix<int> wektor2;
    wektor2.import_matrix_from_txt_file("wektor2.txt");
    wektor2.write_matrix();
   
    cout << endl;
    cout << "Scalar product: " << endl << wektor2.scalar_product(wektor1) << endl;
    cout << endl;
   
    Matrix<int> z³a_c;
    z³a_c.import_matrix_from_txt_file("z³a_macierz.txt");
    z³a_c.write_matrix();
   
    Matrix<int> mat_wpis(2, 2, 4);
    Matrix<int> mat_wpis2(3, 3, 5);
    Matrix<int> mat_res;
    mat_wpis.set_size(3, 3, true);

    cout << endl;
    mat_wpis.write_matrix();

    cout << endl;
    mat_wpis2.write_matrix();
    mat_res = mat_wpis + mat_wpis2;

    cout << endl;
    mat_res.write_matrix();

    cout << endl;
    Matrix<double> double_mtrx;
    double_mtrx.import_matrix_from_txt_file("spacje_test.txt");
    double_mtrx.write_matrix();

    cout << endl;
    Matrix<double> double_mtrx2(3,6,2.5);
    double_mtrx2.write_matrix();

    try {
        Matrix<double> result_d = double_mtrx2 * double_mtrx;
    }
    catch (Matrix_Exception e) {

        cout << e.get_error_code() << endl;
        cout << e.get_message() << endl;
    }

    cout << endl;
    Matrix<float> float_mtrx;;
    float_mtrx.import_matrix_from_txt_file("spacje_test.txt");
    float_mtrx.write_matrix();

    cout << float_mtrx.get_num_of_rows() << " " << float_mtrx.get_num_of_columns() << endl;


}





