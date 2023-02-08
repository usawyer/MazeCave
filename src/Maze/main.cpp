#include <QApplication>

#include "controller.h"
#include "paintwidget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Maze maze;
  Cave cave;
  Controller controller(&maze, &cave);
  PaintWidget w(&controller);
  w.show();
  return a.exec();
}
