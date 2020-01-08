#include "undoitem.h"


UndoItem::UndoItem(QWidget *parent, const QPixmap &icon, QString &&text, bool isActive) : QWidget(parent) {
    QHBoxLayout * hbox = new QHBoxLayout(this);
    hbox->setSpacing(5);
    hbox->setContentsMargins(2,0,2,0);
    hbox->setAlignment(Qt::AlignLeft);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setText("");
    m_iconLabel->setPixmap(icon.scaled(20,20));
    hbox->addWidget(m_iconLabel, 0, Qt::AlignLeft);

    m_textLabel = new QLabel(this);
    m_textLabel->setText(std::move(text));
    hbox->addWidget(m_textLabel, 0, Qt::AlignLeft);


    this->setActive(isActive);
    this->setLayout(hbox);
    this->setMaximumHeight(30);
}

void UndoItem::setActive(bool val) {
    QString styleStr = "background-color:";

    if (val == true)
        styleStr += activeColor;
    else
        styleStr += inactiveColor;

    styleStr += ";";
    this->setStyleSheet(styleStr);
}
