#include "maze.h"

void Maze::Generate(int rows, int cols) {
  vector_of_sets_.clear();
  std::ofstream out(HOMEDIR "/Desktop/Maze/wall_information.txt",
                    std::ofstream::out | std::ofstream::trunc);
  out.close();
  SetNumberRows(rows);
  SetNumberCols(cols);
  CreateMatrix();
  InitSet();
  for (auto i = 0; i < rows_; ++i) {
    AddNewLine(i);
    AddVerticalWall(i);
    AddHorizontalWall(i);
  }
  LastLine();
  Filing(vertical_matrix_);
  Filing(horizontal_matrix_);
}

void Maze::AddNewLine(int row) {
  if (row > 0) {
    std::vector<int> buffer = std::move(vector_of_sets_);
    for (auto j = 0; j < cols_; ++j) {
      if (horizontal_matrix_(row - 1, j)) {
        vector_of_sets_.push_back(count_value_);
        count_value_++;
      } else {
        vector_of_sets_.push_back(buffer[j]);
      }
    }
  }
}

void Maze::InitSet() {
  for (auto i = 0; i < cols_; ++i, ++count_value_) {
    vector_of_sets_.push_back(count_value_);
  }
}

void Maze::SetIntegration(int elem, int index) {
  int elem_f = vector_of_sets_[index + 1];
  for (auto j = 0; j < cols_; ++j) {
    if (elem_f == vector_of_sets_[j]) {
      vector_of_sets_[j] = elem;
    }
  }
}

void Maze::AddVerticalWall(int row) {
  std::random_device random;
  std::mt19937 gen(random());
  std::uniform_int_distribution<> distrib(0, 1);
  for (auto j = 0; j < cols_ - 1; ++j) {
    int value = distrib(gen);
    int a = j;
    if (value || vector_of_sets_[a] == vector_of_sets_[++a]) {
      vertical_matrix_(row, j) = 1;
    } else {
      vertical_matrix_(row, j) = 0;
      SetIntegration(vector_of_sets_[j], j);
    }
  }
  vertical_matrix_(row, cols_ - 1) = 1;
}

void Maze::AddHorizontalWall(int row) {
  std::random_device random;
  std::mt19937 gen(random());
  std::uniform_int_distribution<> distrib(0, 1);
  for (auto j = 0; j < cols_; ++j) {
    int value = distrib(gen);
    if (value && NumberOfUniqueSet(vector_of_sets_[j]) != 1) {
      horizontal_matrix_(row, j) = 1;
    }
  }
  CheckHorizontalWall(row);
}

void Maze::CheckHorizontalWall(int row) {
  for (int j = 0; j < cols_; j++) {
    if (NumberOfHorizontalWall(vector_of_sets_[j], row) ==
        NumberOfUniqueSet(vector_of_sets_[j])) {
      horizontal_matrix_(row, j) = 0;
    }
  }
}

int Maze::NumberOfUniqueSet(int elem) {
  int count = 0;
  for (int i = 0; i < cols_; i++) {
    if (vector_of_sets_[i] == elem) {
      count++;
    }
  }
  return count;
}

int Maze::NumberOfHorizontalWall(int elem, int row) {
  int count = 0;
  for (int j = 0; j < cols_; j++) {
    if (vector_of_sets_[j] == elem && horizontal_matrix_(row, j)) {
      count++;
    }
  }
  return count;
}

void Maze::LastLine() {
  for (int j = 0; j < cols_ - 1; j++) {
    if (vector_of_sets_[j] != vector_of_sets_[j + 1]) {
      vertical_matrix_(rows_ - 1, j) = 0;
      SetIntegration(vector_of_sets_[j], j);
    }
    horizontal_matrix_(rows_ - 1, j) = 1;
  }
  horizontal_matrix_(rows_ - 1, cols_ - 1) = 1;
}

void Maze::Filing(Matrix& matrix) {
  std::ofstream out(HOMEDIR "/Desktop/Maze/wall_information.txt",
                    std::ios::app);
  if (out.is_open()) {
    if (!flag_) {
      out << matrix.GetRows() << ' ' << matrix.GetCols() << '\n';
      flag_ = 1;
    }
    for (auto i = 0; i < matrix.GetRows(); ++i) {
      for (auto j = 0; j < matrix.GetCols(); ++j) {
        out << matrix(i, j) << ' ';
      }
      out << '\n';
    }
    out << '\n';
  }
  out.close();
}

void Maze::ReadFromFile(std::string& file_name) {
  std::ifstream file(file_name);
  Size(file);
  CreateMatrix();
  ReadMatrix(file, vertical_matrix_);
  ReadMatrix(file, horizontal_matrix_);
  file.close();
}

void Maze::Size(std::ifstream& file) {
  std::string line;
  std::getline(file, line);
  std::string::size_type size = 0;

  int temp_rows = std::stoi(line, &size);
  line.erase(0, size + 1);
  int temp_cols = std::stoi(line);

  if (temp_rows < 1 || temp_cols < 1 || temp_rows > 50 || temp_cols > 50)
    throw std::out_of_range("Incorrect matrix size value");

  rows_ = temp_rows;
  cols_ = temp_cols;
}

void Maze::CreateMatrix() {
  horizontal_matrix_ = Matrix(rows_, cols_);
  vertical_matrix_ = Matrix(rows_, cols_);
}

void Maze::ReadMatrix(std::ifstream& file, Matrix& matrix) {
  std::string line;
  int row = 0;
  std::string::size_type size = 0;
  while (row != rows_) {
    std::getline(file, line);
    for (auto i = 0; i < cols_; ++i) {
      if (!line.empty()) {
        matrix(row, i) = std::stoi(line, &size);
        if (size != 1) {
          throw std::out_of_range("Incorrect matrix value");
        }
      } else {
        --row;
        break;
      }
      line.erase(0, size + 1);
    }
    ++row;
  }
}

void Maze::Clear() {
  rows_ = cols_ = 0;
  count_value_ = 1;
  flag_ = 0;
  horizontal_matrix_.Inicialization();
  vertical_matrix_.Inicialization();
}
