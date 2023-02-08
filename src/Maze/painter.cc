#include "painter.h"

Painter::Painter(QWidget* parent)
    : QWidget(parent),
      field_(QSize(500, 500), QImage::Format_ARGB32),
      maze_(QSize(500, 500), QImage::Format_ARGB32),
      path_(QSize(500, 500), QImage::Format_ARGB32) {}

void Painter::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  QRect dirtyRect = event->rect();
  painter.drawImage(dirtyRect, field_, dirtyRect);
  painter.drawImage(dirtyRect, maze_, dirtyRect);
  painter.drawImage(dirtyRect, path_, dirtyRect);
  painter.setPen(QPen(Qt::white, 2));
  painter.drawRect(0, 0, 500, 500);
}

void Painter::DrawCave(const Cave& cave) {
  ClearWidget();
  QPainter painter(&field_);
  painter.setBrush(QBrush(Qt::black));
  width_ = 500.0 / cave.GetCols();
  height_ = 500.0 / cave.GetRows();
  for (int i = 0; i < cave.GetRows(); i++) {
    for (int j = 0; j < cave.GetCols(); j++) {
      if ((cave.GetMatrix())(i, j) == 1) {
        painter.drawRect(
            QRect(QPoint(width_ * j, height_ * i), QSize(width_, height_)));
      }
    }
  }
  update();
}

void Painter::DrawMaze(const Maze& maze) {
  ClearWidget();
  QPainter painter(&maze_);
  painter.setPen(QPen(Qt::black, 2));
  height_ = 500.0 / maze.GetRows();
  width_ = 500.0 / maze.GetCols();
  double y = 1.0;
  for (int i = 0; i < maze.GetRows(); ++i) {
    y += height_;
    double x = 1.0;
    for (int j = 0; j < maze.GetCols(); ++j) {
      x += width_;
      if ((maze.GetVerticalWall())(i, j)) {
        painter.drawLine(x, y, x, y - height_);
      }
      if ((maze.GetHorizontallWall())(i, j)) {
        painter.drawLine(x, y, x - width_, y);
      }
    }
  }
  update();
}

void Painter::DrawFirstPoint(int x, int y) {
  ClearPath();
  QPainter painter(&path_);
  painter.setPen(QPen(Qt::NoPen));
  painter.setBrush(QBrush(Qt::red));
  painter.drawEllipse(PointToCentral(x, y), 3, 3);
  update();
}

void Painter::DrawPath(const std::vector<std::pair<int, int>>& FinalPath) {
  QPainter painter(&path_);
  std::vector<std::pair<int, int>> points = FinalPath;
  for (auto it = points.begin(); it != (points.end() - 1); ++it) {
    if (it == points.begin()) {
      painter.setPen(QPen(Qt::NoPen));
      painter.setBrush(QBrush(Qt::red));
      painter.drawEllipse(PointToCentral(it->first, it->second), 3, 3);
      painter.setPen(QPen(Qt::red, 2));
    }
    painter.drawLine(PointToCentral(it->first, it->second),
                     PointToCentral((it + 1)->first, (it + 1)->second));
  }
  update();
}

QPoint Painter::PointToCentral(int row, int col) {
  double row_pos = row * height_ + height_ / 2;
  double col_pos = col * width_ + width_ / 2;
  return QPoint(col_pos, row_pos);
}

void Painter::ClearWidget() {
  maze_.fill(QColor(0, 0, 0, 0));
  field_.fill(QColor(0, 0, 0, 0));
}

void Painter::ClearPath() { path_.fill(QColor(0, 0, 0, 0)); }
