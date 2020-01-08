#ifndef UNDOPREVIEW_H
#define UNDOPREVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <memory>
#include "rsimg/transform.hpp"
#include "custom_visitors.hpp"
#include "undoitem.h"

class UndoPreview : public QWidget {
    Q_OBJECT
private:
    QLayout * m_layout = new QVBoxLayout(this);

    void deleteChildren();



public:
    UndoPreview(QWidget *parent = nullptr);

    void updatePreview(std::vector<std::shared_ptr<const rs::Transform>> previous,
                       std::vector<std::shared_ptr<const rs::Transform>> next
                      );

signals:

};

#endif // UNDOPREVIEW_H
