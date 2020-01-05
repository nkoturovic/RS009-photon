#include <QPainter>
#include "imageview.h"

ImageView::ImageView(QWidget *parent) : QWidget(parent) {
  m_image = nullptr;
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void ImageView::setImage(QImage *image) {
  m_image = image;
  repaint();
}

void ImageView::paintEvent(QPaintEvent*) {
  if (!m_image) { return; }
  QPainter painter(this);
  painter.drawImage(rect(), *m_image, m_image->rect());
}
