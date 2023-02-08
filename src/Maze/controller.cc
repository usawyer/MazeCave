#include "controller.h"

void Controller::CaveSetter(int rows, int cols, int birth_limit,
                                 int death_limit, double chance) {
  return cave_->Setter(rows, cols, birth_limit, death_limit, chance);
}

void Controller::CaveNextStep(int birth_limit, int death_limit) {
  return cave_->NextStep(birth_limit, death_limit);
}

void Controller::CaveParser(const std::string &file_name) {
  return cave_->Parser(file_name);
}

int Controller::CaveGetCols() const { return cave_->GetRows(); }

int Controller::CaveGetRows() const { return cave_->GetCols(); }

Matrix Controller::CaveGetMatrix() const {
  return cave_->GetMatrix();
}

Cave Controller::GetCave() const { return cave_->GetCave(); }

void Controller::Clear() { return cave_->Clear(); }

Matrix Controller::GetVerticalWall() const {
  return maze_->GetVerticalWall();
}

Matrix Controller::GetHorizontallWall() const {
  return maze_->GetHorizontallWall();
}

void Controller::MazeGenerate(int rows, int cols) {
  maze_->Generate(rows, cols);
}

int Controller::MazeGetRows() const { return maze_->GetRows(); }

int Controller::MazeGetCols() const { return maze_->GetCols(); }

Maze Controller::GetMaze() const { return maze_->GetMaze(); }

void Controller::MazeFromFile(std::string file_name) {
  maze_->ReadFromFile(file_name);
}

void Controller::MazeClear() { maze_->Clear(); }

const std::vector<std::pair<int, int>> Controller::GetFinalPath(
    int begin_x, int begin_y, int end_x, int end_y, Maze maze) {
  Pathfinding pathfinding_ = Pathfinding(&maze);
  return pathfinding_.GetFinalPath(begin_x, begin_y, end_x, end_y, &maze);
}
