#ifndef PAINTER_H_
#define PAINTER_H_

#include <QPaintEvent>
#include <QPainter>
#include <QWidget>

#include "controller.h"

class Painter : public QWidget {
 public:
  explicit Painter(QWidget *parent = nullptr);
  void ClearWidget();
  void ClearPath();
  void DrawCave(const Cave &cave);
  void DrawMaze(const Maze &maze);
  void DrawPath(const std::vector<std::pair<int, int>> &FinalPath);
  void DrawFirstPoint(int x, int y);
  void SetController(Controller *controller) { controller_ = controller; }

 protected:
  void paintEvent(QPaintEvent *event) override;
  QPoint PointToCentral(int row, int col);

 private:
  QImage field_;
  QImage maze_;
  QImage path_;
  double height_ = 0.0, width_ = 0.0;
  Controller *controller_ = nullptr;
};

#endif  // PAINTER_H_
