/* Ovaj kod je preuzat sa:
 * https://stackoverflow.com/questions/42833511/qt-how-to-create-image-that-scale-with-window-and-keeps-aspect-ratio */

#ifndef LABEL_IMAGE_H
#define LABEL_IMAGE_H

// Qt header:
#include <QApplication>
#include <QObject>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QResizeEvent>
#include <QTimer>

class LabelImage : public QLabel {
    Q_OBJECT
private:
    QPixmap m_qPixmap, m_qPixmapScaled;

public:
    LabelImage(QWidget * parent) : QLabel(parent) {}
    void setPixmap(const QPixmap &qPixmap) { setPixmap(qPixmap, size()); }

protected:
    virtual void resizeEvent(QResizeEvent *pQEvent);

private:
    void setPixmap(const QPixmap &qPixmap, const QSize &size);
};

#endif // LABEL_IMAGE_H
