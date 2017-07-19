#ifndef CAITEMDELEGATE_H
#define CAITEMDELEGATE_H

#include <QAbstractItemDelegate>

class CAItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    CAItemDelegate(QObject *parent = 0);

    void paint(QPainter * painter, const QStyleOptionViewItem & option,
               const QModelIndex & index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                      const QModelIndex &index ) const;
};

#endif // CAITEMDELEGATE_H
