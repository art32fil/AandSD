#include "scaledpixmap.h"
#include "mainwindow.h"


ScaledPixmap::ScaledPixmap(QWidget *parent): QWidget(parent) {
}

void ScaledPixmap::setScaledPixmap(const QPixmap &pixmap) {
  m_pixmap = pixmap;
  update();
}

void ScaledPixmap::removeScaledPixmap(){
    pixmap_width = 0;
    pixmap_height = 0;
    pixmap_x_start = 0;
    pixmap_y_start = 0;
}

void ScaledPixmap::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  if (false == m_pixmap.isNull()) {
    QSize widgetSize = size();
    QPixmap scaledPixmap = m_pixmap.scaled(widgetSize, Qt::KeepAspectRatio);
    pixmap_width = scaledPixmap.width();
    pixmap_height = scaledPixmap.height();
    QPoint center((widgetSize.width() - scaledPixmap.width())/2,
                  (widgetSize.height() - scaledPixmap.height())/2);
    pixmap_x_start = center.x();
    pixmap_y_start = center.y();
    painter.drawPixmap(center, scaledPixmap);
  }

  QWidget::paintEvent(event);
}

void ScaledPixmap::mousePressEvent(QMouseEvent *event) {
    press_point.setX(event->x());
    press_point.setY(event->y());
}

void ScaledPixmap::mouseReleaseEvent(QMouseEvent *event) {
    release_point.setX(event->x());
    release_point.setY(event->y());
}

QPoint ScaledPixmap::resizeWidget(){
    QPoint start_pixmap;
    start_pixmap.setX(pixmap_x_start);
    start_pixmap.setY(pixmap_y_start);
    return start_pixmap;
}

void ScaledPixmap::resetMouse(){
    press_point.setX(0);
    press_point.setY(0);
    release_point.setX(0);
    release_point.setY(0);
}

QPoint ScaledPixmap::backMouse(int count){
    if(count == 1)
        return press_point;
    else
        return release_point;
}
