#include "paintwidget.h"

#include "ui_paintwidget.h"

PaintWidget::PaintWidget(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::PaintWidget), controller_(controller) {
  ui_->setupUi(this);
  ui_->maze_page->setChecked(true);
  timer_ = new QTimer(this);
  connect(timer_, SIGNAL(timeout()), this, SLOT(timer_update()));
}

PaintWidget::~PaintWidget() {
  delete ui_;
  delete timer_;
}

void PaintWidget::on_open_file_clicked() {
  ui_->widget->ClearWidget();
  QString str = QFileDialog::getOpenFileName(this, "Load from file..",
                                             QDir::homePath(), "(*.txt)");
  try {
    if (!str.isEmpty()) {
      controller_->CaveParser(str.toStdString());
      ui_->width->setValue(controller_->CaveGetCols());
      ui_->height->setValue(controller_->CaveGetRows());
      ui_->widget->DrawCave(controller_->GetCave());
    }
  } catch (std::out_of_range &exept) {
    ShowExeption(exept.what());
  }
}

void PaintWidget::on_generate_button_clicked() {
  controller_->CaveSetter(ui_->height->value(), ui_->width->value(),
                          ui_->birth_limit->value(), ui_->death_limit->value(),
                          ui_->init_chance->value());
  ui_->widget->DrawCave(controller_->GetCave());
}

void PaintWidget::on_step_button_clicked() {
  controller_->CaveNextStep(ui_->birth_limit->value(),
                            ui_->death_limit->value());
  ui_->widget->DrawCave(controller_->GetCave());
}

void PaintWidget::on_start_button_clicked() {
  if (ui_->start_button->text() == "Start") {
    ui_->start_button->setText("Stop");
    timer_->start(ui_->speed->value());
  } else {
    timer_stop();
  }
}

void PaintWidget::timer_update() {
  on_step_button_clicked();
  timer_->start(ui_->speed->value());
}

void PaintWidget::timer_stop() {
  timer_->stop();
  ui_->start_button->setText("Start");
}

void PaintWidget::on_clear_button_clicked() {
  ui_->widget->ClearWidget();
  ClearPath();
  controller_->Clear();
  controller_->MazeClear();
  update();
}

void PaintWidget::on_generate_clicked() {
  ClearPath();
  on_clear_button_clicked();
  controller_->MazeGenerate(ui_->Rows->value(), ui_->Cols->value());
  ui_->widget->DrawMaze(controller_->GetMaze());
}

void PaintWidget::on_load_clicked() {
  on_clear_button_clicked();
  QString str = QFileDialog::getOpenFileName(
      this, "Open a file...", QDir::homePath(), "TXT-file (*.txt)");
  try {
    if (!str.isEmpty()) {
      QFileInfo path(str);
      controller_->MazeFromFile(str.toStdString());
      ui_->Cols->setValue(controller_->MazeGetCols());
      ui_->Rows->setValue(controller_->MazeGetRows());
      ui_->widget->DrawMaze(controller_->GetMaze());
    }
  } catch (std::out_of_range &exept) {
    ShowExeption(exept.what());
  }
}

void PaintWidget::on_cave_page_clicked() {
  on_clear_button_clicked();
  ClearPath();
  ui_->stackedWidget->setCurrentIndex(1);
  ui_->maze_page->setChecked(false);
}

void PaintWidget::on_maze_page_clicked() {
  timer_stop();
  on_clear_button_clicked();
  ui_->stackedWidget->setCurrentIndex(0);
  ui_->cave_page->setChecked(false);
}

void PaintWidget::mousePressEvent(QMouseEvent *event) {
  if (ui_->maze_page->isChecked() == true) {
    if (event->button() == Qt::LeftButton && controller_->MazeGetRows() != 0) {
      Path(event);
    } else if (event->button() == Qt::RightButton) {
      path_check_ = 0;
      ClearPath();
    }
  }
}

void PaintWidget::Path(QMouseEvent *event) {
  if (path_check_ == 0) {
    if (CheckArea(event->x(), event->y())) {
      ClearPath();
      begin_row_ = (event->y() - 10) / (499.0 / ui_->Rows->value());
      begin_col_ = (event->x() - 10) / (499.0 / ui_->Cols->value());
      ui_->widget->DrawFirstPoint(begin_row_, begin_col_);
      path_check_ = 1;
    }
  } else {
    if (CheckArea(event->x(), event->y())) {
      end_row_ = (event->y() - 10) / (499.0 / ui_->Rows->value());
      end_col_ = (event->x() - 10) / (499.0 / ui_->Cols->value());
      path_check_ = 0;
    }
  }
  if (path_check_ == 0) {
    ui_->widget->SetController(controller_);
    ui_->widget->DrawPath(controller_->GetFinalPath(
        begin_row_, begin_col_, end_row_, end_col_, controller_->GetMaze()));
    begin_row_ = begin_col_ = end_row_ = end_col_ = 0;
  }
}

bool PaintWidget::CheckArea(int x, int y) {
  return (x >= 10 && x <= 510 && y >= 10 && y <= 510);
}

void PaintWidget::ClearPath() {
  path_check_ = 0;
  begin_row_ = begin_col_ = end_row_ = end_col_ = 0;
  ui_->widget->ClearPath();
  update();
}

void PaintWidget::ShowExeption(QString exept) {
  QMessageBox msg_box;
  msg_box.setText(exept);
  msg_box.exec();
}
