#include "caitemdelegate.h"

#include <QImage>
#include <QPainter>
#include <QFont>
#include <QStyleOptionViewItem>

#include <QDebug>

CAItemDelegate::CAItemDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{

}

void CAItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString name = index.data(Qt::ToolTipRole).toString();
    QImage img = index.data(Qt::DisplayRole).value<QImage>();

    int mar = 5;
    QPoint tl = option.rect.topLeft();
    QPoint br = option.rect.bottomRight();
    painter->save();

    QFont font = option.font;
    font.setPixelSize(30);
    painter->setFont(font);




    if(option.state & QStyle::State_Selected)
    {
        painter->setPen(option.palette.highlightedText().color());
        painter->setBrush(option.palette.highlight());
    }
    else
    {
        painter->setPen(option.palette.text().color());

        if(option.features & QStyleOptionViewItem::Alternate)
            painter->setBrush(option.palette.alternateBase());
        else
            painter->setBrush(option.palette.base());
    }

    painter->drawRect(option.rect);
    painter->drawText(tl + QPoint(5, 35), name);
    QRect imgRect = QRect(tl + QPoint(5, 45), br - QPoint(5, 5));
    painter->drawImage(imgRect, img);

    painter->restore();
}

QSize CAItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(260, 300);
}
