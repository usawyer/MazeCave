#include "matrix.h"

Matrix::Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = NULL;
}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1)
    throw std::out_of_range("Incorrect matrix size value");
  CreateMatrix();
}

Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::Matrix(Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.cols_ = other.rows_ = 0;
  other.matrix_ = nullptr;
}

Matrix::~Matrix() {
  if (matrix_) {
    DeleteMatrix();
  }
  rows_ = 0;
  cols_ = 0;
}

int Matrix::GetRows() { return rows_; }
int Matrix::GetCols() { return cols_; }

void Matrix::CreateMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  Inicialization();
}

void Matrix::Inicialization() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0.0;
    }
  }
}

void Matrix::DeleteMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

bool Matrix::EqMatrix(const Matrix& other) {
  bool result = true;
  if (cols_ != other.cols_ || rows_ != other.rows_) {
    result = false;
  } else {
    if (EqLoop(other) != cols_ * rows_) {
      result = false;
    }
  }
  return result;
}

int Matrix::EqLoop(const Matrix& other) {
  int match = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) < E) {
        match++;
      }
    }
  }
  return match;
}

Matrix& Matrix::operator=(const Matrix& other) {
  DeleteMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix();

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

double& Matrix::operator()(int rows, int cols) {
  if (rows_ <= rows || cols_ <= cols || rows < 0 || cols < 0) {
    throw std::out_of_range("Incorrect matrix indices!");
  }
  return matrix_[rows][cols];
}
