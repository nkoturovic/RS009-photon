#include "label_image.h"

void LabelImage::resizeEvent(QResizeEvent *pQEvent) {
    QLabel::resizeEvent(pQEvent);
    setPixmap(m_qPixmap, pQEvent->size());
}

void LabelImage::setPixmap(const QPixmap &qPixmap, const QSize &size) {

    if (qPixmap.isNull())
        return;

    m_qPixmap = qPixmap;
    m_qPixmapScaled = m_qPixmap.scaled(size, Qt::KeepAspectRatio);
    QLabel::setPixmap(m_qPixmapScaled);
}
