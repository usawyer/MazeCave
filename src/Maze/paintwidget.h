#ifndef PAINTWIDGET_H_
#define PAINTWIDGET_H_

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTimer>

#include "painter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PaintWidget;
}
QT_END_NAMESPACE


class PaintWidget : public QMainWindow {
  Q_OBJECT

 public:
  explicit PaintWidget(Controller *controller, QWidget *parent = nullptr);
  ~PaintWidget();

 private slots:
  void on_open_file_clicked();
  void on_generate_button_clicked();
  void on_step_button_clicked();
  void on_start_button_clicked();
  void on_clear_button_clicked();
  void timer_update();
  void timer_stop();
  void on_generate_clicked();
  void on_load_clicked();
  void on_cave_page_clicked();
  void on_maze_page_clicked();
  void mousePressEvent(QMouseEvent *event) override;

 private:
  Ui::PaintWidget *ui_;
  Controller *controller_ = nullptr;
  QTimer *timer_;

  int begin_row_ = 0, begin_col_ = 0, end_row_ = 0, end_col_ = 0;
  bool path_check_ = 0;

  void Path(QMouseEvent *event);
  bool CheckArea(int x, int y);
  void ClearPath();
  void ShowExeption(QString exept);
};


#endif  // PAINTWIDGET_H_
