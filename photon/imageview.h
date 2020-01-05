#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>

class ImageView : public QWidget {
  Q_OBJECT
public:
  ImageView(QWidget* parent = nullptr);
  void setImage(QImage* image);

private:
  QImage* m_image;

protected:
  void paintEvent(QPaintEvent* event);

};

#endif // IMAGEVIEW_H
