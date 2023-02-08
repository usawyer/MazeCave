#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#include <vector>

#include "maze.h"


class Pathfinding {
 public:
  Pathfinding() {}
  explicit Pathfinding(Maze *maze) : maze_(maze) {}
  Pathfinding(Pathfinding &p) = delete;
  Pathfinding(Pathfinding &&p) = delete;
  Pathfinding &operator=(Pathfinding &p) = delete;
  Pathfinding &operator=(Pathfinding &&p) = delete;
  ~Pathfinding() {}

  std::vector<std::pair<int, int>> GetFinalPath(int begin_row, int begin_col,
                                                int end_row, int end_col,
                                                Maze *maze);

 private:
  std::vector<std::pair<int, int>> final_path_;
  Maze *maze_ = nullptr;
  int rows_ = maze_->GetRows();
  int cols_ = maze_->GetCols();
  Matrix horizontall_wall_ = maze_->GetHorizontallWall();
  Matrix vertical_wall_ = maze_->GetVerticalWall();
  Matrix path_matrix_ = Matrix(rows_, cols_);

  void FindPath(int begin_x, int begin_y, int end_x, int end_y);
  int PossibleStep(int step);
  void RewerseStep(int step, int end_x, int end_y);
};


#endif  // PATHFINDING_H_
