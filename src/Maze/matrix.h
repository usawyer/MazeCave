#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <cmath>
#include <iostream>

constexpr double E = 1e-7;


class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  int GetRows();
  int GetCols();

  bool EqMatrix(const Matrix& other);
  void Inicialization();
  Matrix& operator=(const Matrix& other);
  double& operator()(int rows, int cols);

 private:
  int rows_ = 0, cols_ = 0;
  double** matrix_ = nullptr;

  void CreateMatrix();
  void DeleteMatrix();
  int EqLoop(const Matrix& other);
};


#endif  // SRC_MATRIX_H_
