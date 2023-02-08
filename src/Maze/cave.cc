#include "cave.h"

Cave::Cave()
    : cave_matrix_(),
      rows_(0),
      cols_(0),
      birth_limit_(0),
      death_limit_(0),
      chance_(0.0) {}

void Cave::Setter(int rows, int cols, int birth_limit, int death_limit,
                  double chance) {
  rows_ = rows;
  cols_ = cols;
  birth_limit_ = birth_limit;
  death_limit_ = death_limit;
  chance_ = chance;

  CreateCave();
}

void Cave::CreateMatrix() { cave_matrix_ = Matrix(rows_, cols_); }

void Cave::CreateCave() {
  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::discrete_distribution<> distribution({1 - chance_, chance_});

  CreateMatrix();

  for (int i = 0; i < cave_matrix_.GetRows(); ++i) {
    for (int j = 0; j < cave_matrix_.GetCols(); ++j) {
      cave_matrix_(i, j) = distribution(generator);
    }
  }
}

void Cave::NextStep(int birth_limit, int death_limit) {
  birth_limit_ = birth_limit;
  death_limit_ = death_limit;
  Matrix previous_map(cave_matrix_);

  for (int i = 0; i < previous_map.GetRows(); i++) {
    for (int j = 0; j < previous_map.GetCols(); j++) {
      int neighbours = CountAliveNeighbours(previous_map, i, j);

      if (previous_map(i, j) == 0 && neighbours > birth_limit_)
        cave_matrix_(i, j) = 1;
      if (previous_map(i, j) == 1 && neighbours < death_limit_)
        cave_matrix_(i, j) = 0;
    }
  }
}

int Cave::CountAliveNeighbours(Matrix &previous_map, int x, int y) {
  int count = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      int neighbour_x = x + i;
      int neighbour_y = y + j;

      if (i == 0 && j == 0) {
        continue;
      } else if (neighbour_x < 0 || neighbour_y < 0 ||
                 neighbour_x >= previous_map.GetRows() ||
                 neighbour_y >= previous_map.GetCols()) {
        count = count + 1;
      } else if (previous_map(neighbour_x, neighbour_y)) {
        count = count + 1;
      }
    }
  }
  return count;
}

void Cave::Parser(const std::string &file_name) {
  std::ifstream file(file_name);
  if (file.is_open()) {
    Size(file);
    CreateMatrix();
    Map(file);
    file.close();
  }
}

void Cave::Size(std::ifstream &file) {
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

void Cave::Map(std::ifstream &file) {
  std::string line;
  int line_counter = 0;

  while (line_counter != rows_) {
    std::getline(file, line);
    std::string::size_type size = 0;

    for (int i = 0; i < cols_; i++) {
      int value = std::stoi(line, &size);

      if (value != 1 && value != 0)
        throw std::out_of_range("Incorrect matrix value");

      cave_matrix_(line_counter, i) = value;
      line.erase(0, size + 1);
    }
    line_counter++;
  }
}

void Cave::Clear() {
  cave_matrix_.Inicialization();
  rows_ = cols_ = 0;
}
