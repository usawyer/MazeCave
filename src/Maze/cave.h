#ifndef CAVE_H_
#define CAVE_H_

#include <fstream>
#include <random>

#include "matrix.h"

class Cave {
 public:
  Cave();

  void Setter(int rows, int cols, int birth_limit, int death_limit,
              double chance);
  void CreateCave();
  void NextStep(int birth_limit, int death_limit);
  void Parser(const std::string &file_name);
  void Clear();

  int GetRows() const { return rows_; }
  int GetCols() const { return cols_; }
  int GetBirth() const { return birth_limit_; }
  int GetDeath() const { return death_limit_; }
  int GetChance() const { return chance_; }
  Matrix GetMatrix() const { return cave_matrix_; }
  Cave GetCave() const { return *this; }

 private:
  Matrix cave_matrix_;
  int rows_;
  int cols_;
  int birth_limit_;
  int death_limit_;
  double chance_;

  void CreateMatrix();
  int CountAliveNeighbours(Matrix &previous_map, int x, int y);
  void Size(std::ifstream &file);
  void Map(std::ifstream &file);
};

#endif  // CAVE_H_
