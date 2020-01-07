#include "undopreview.h"

void UndoPreview::deleteChildren() {
    while ( QLayoutItem* item = m_layout->takeAt( 0 ) )
    {
        Q_ASSERT(sender() != item->layout() || !sender()); // otherwise the layout will leak

        if (auto widget = item->widget())
            widget->deleteLater();

        delete item;
    }
}

UndoPreview::UndoPreview(QWidget *parent) : QWidget(parent) {
    this->setLayout(m_layout);
    m_layout->setAlignment(Qt::AlignTop);
}

void UndoPreview::updatePreview(std::vector<std::shared_ptr<const rs::Transform> > previous, std::vector<std::shared_ptr<const rs::Transform> > next) {

    this->deleteChildren();

    UndoItemGenerator itemGenerator(this);


    for (auto it = previous.cbegin(); it != previous.cend(); it++) {
        auto oneBeforeLast = std::prev(previous.cend());
        if (it != oneBeforeLast) {
            m_layout->addWidget(itemGenerator(*it->get()));
        } else {
            if (next.empty()) {
                UndoItem * item = itemGenerator(*it->get());
                item->setActive(true);
                m_layout->addWidget(item);
            } else {
                m_layout->addWidget(itemGenerator(*it->get()));
            }
        }
    }

    for (auto it = next.crbegin(); it != next.crend(); it++) {
        if (it != next.crbegin()) {
            m_layout->addWidget(itemGenerator(*it->get()));
        } else {
            UndoItem * item = itemGenerator(*it->get());
            item->setActive(true);
            m_layout->addWidget(item);
        }
    }
}
