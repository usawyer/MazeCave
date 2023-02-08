#include "pathfinding.h"

std::vector<std::pair<int, int>> Pathfinding::GetFinalPath(
    int begin_row, int begin_col, int end_row, int end_col, Maze* maze) {
  FindPath(begin_row, begin_col, end_row, end_col);
  return final_path_;
}

void Pathfinding::FindPath(int begin_row, int begin_col, int end_row,
                                int end_col) {
  path_matrix_.Inicialization();  // для очищения
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      path_matrix_(i, j) = -1;
    }
  }
  int count = 0, res = 1;
  path_matrix_(begin_row, begin_col) = 0;
  while (path_matrix_(end_row, end_col) == -1 && res != 0) {
    res = PossibleStep(count++);
  }
  final_path_.push_back(std::make_pair(end_row, end_col));
  RewerseStep(count, end_row, end_col);
}

int SetValue(int value, int cell) {
  if (cell == -1) cell = value;
  return cell;
}

void Pathfinding::RewerseStep(int step, int end_row, int end_col) {
  int i = end_row, j = end_col;
  while (step--) {
    if (i < rows_ - 1 && !(horizontall_wall_(i, j)) &&
        path_matrix_(i + 1, j) == step) {
      final_path_.push_back(std::make_pair(i + 1, j));
      i += 1;
    }
    if (i > 0 && !(horizontall_wall_(i - 1, j)) &&
        path_matrix_(i - 1, j) == step) {
      final_path_.push_back(std::make_pair(i - 1, j));
      i -= 1;
    }
    if (j < cols_ - 1 && !(vertical_wall_(i, j)) &&
        path_matrix_(i, j + 1) == step) {
      final_path_.push_back(std::make_pair(i, j + 1));
      j += 1;
    }
    if (j > 0 && !(vertical_wall_(i, j - 1)) &&
        path_matrix_(i, j - 1) == step) {
      final_path_.push_back(std::make_pair(i, j - 1));
      j -= 1;
    }
  }
}

int Pathfinding::PossibleStep(int step) {
  int result = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (path_matrix_(i, j) == step) {
        result = 1;
        if (i < rows_ - 1 && !(horizontall_wall_(i, j))) {
          path_matrix_(i + 1, j) = SetValue(step + 1, path_matrix_(i + 1, j));
        }
        if (i > 0 && !(horizontall_wall_(i - 1, j))) {
          path_matrix_(i - 1, j) = SetValue(step + 1, path_matrix_(i - 1, j));
        }
        if (j < cols_ - 1 && !(vertical_wall_(i, j))) {
          path_matrix_(i, j + 1) = SetValue(step + 1, path_matrix_(i, j + 1));
        }
        if (j > 0 && !(vertical_wall_(i, j - 1))) {
          path_matrix_(i, j - 1) = SetValue(step + 1, path_matrix_(i, j - 1));
        }
      }
    }
  }
  return result;
}
