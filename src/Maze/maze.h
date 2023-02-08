#ifndef MAZE_H_
#define MAZE_H_

#include <fstream>
#include <random>
#include <string>

#include "matrix.h"


class Maze {
 public:
  Maze() {}
  ~Maze() {}

  int GetRows() const { return rows_; }
  int GetCols() const { return cols_; }
  void SetNumberRows(int rows) { rows_ = rows; }
  void SetNumberCols(int cols) { cols_ = cols; }
  Matrix GetVerticalWall() const { return vertical_matrix_; }
  Matrix GetHorizontallWall() const { return horizontal_matrix_; }
  Maze GetMaze() const { return *this; }

  void Generate(int rows, int cols);
  void ReadFromFile(std::string &file_name);
  void Clear();

 private:
  int rows_ = 0, cols_ = 0;
  int count_value_ = 1;
  int flag_ = 0;
  Matrix horizontal_matrix_, vertical_matrix_;
  std::string horizontal_wall_, vertical_wall_;
  std::vector<int> vector_of_sets_;

  void InitSet();
  void AddNewLine(int row);
  void AddVerticalWall(int row);
  void SetIntegration(int elem, int index);
  void AddHorizontalWall(int row);
  void CheckHorizontalWall(int row);
  int NumberOfHorizontalWall(int elem, int row);
  int NumberOfUniqueSet(int elem);
  void LastLine();

  void Size(std::ifstream &file);
  void CreateMatrix();
  void ReadMatrix(std::ifstream &file, Matrix &matrix);
  void Filing(Matrix &vertical_matrix);
};


#endif  // MAZE_H_
