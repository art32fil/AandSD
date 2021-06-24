#ifndef SCALEDPIXMAP_H
#define SCALEDPIXMAP_H

#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QScrollArea>

class ScaledPixmap : public QWidget {

public:
  ScaledPixmap(QWidget *parent = 0);
  void setScaledPixmap(const QPixmap &pixmap);
  void deleteScaledPixmap();
  void removeScaledPixmap();
  QPoint resizeWidget();
  void resetMouse();
  QPoint backMouse(int count);

protected:
  void paintEvent(QPaintEvent *event);

private:
  int pixmap_width = 0;
  int pixmap_height = 0;
  int pixmap_x_start = 0;
  int pixmap_y_start = 0;
  QPoint press_point;
  QPoint release_point;
  QPixmap m_pixmap;
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
};

#endif // SCALEDPIXMAP_H
