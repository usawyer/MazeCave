#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "cave.h"
#include "pathfinding.h"

class Controller {
 public:
  Controller(Maze *maze, Cave *cave) : maze_(maze), cave_(cave) {}

  void CaveSetter(int rows, int cols, int birth_limit, int death_limit,
                  double chance);
  void CaveNextStep(int birth_limit, int death_limit);
  void CaveParser(const std::string &file_name);
  int CaveGetRows() const;
  int CaveGetCols() const;
  Matrix CaveGetMatrix() const;
  Cave GetCave() const;
  void Clear();

  Matrix GetVerticalWall() const;
  Matrix GetHorizontallWall() const;
  void MazeGenerate(int rows, int cols);
  int MazeGetRows() const;
  int MazeGetCols() const;
  Maze GetMaze() const;
  void MazeFromFile(std::string file_name);
  void MazeClear();
  const std::vector<std::pair<int, int>> GetFinalPath(int begin_x, int begin_y,
                                                      int end_x, int end_y,
                                                      Maze maze);

 private:
  Maze *maze_ = nullptr;
  Cave *cave_ = nullptr;
};

#endif  // CONTROLLER_H_
