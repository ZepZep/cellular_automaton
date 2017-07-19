#ifndef CARULEMODEL_H
#define CARULEMODEL_H

#include <QAbstractListModel>

class CARuleModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit CARuleModel(int rowLen = 21, int neighbourhood = 1, QObject *parent = nullptr);

    void makeData();
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:

    QImage makeImage(int ruleNum) const;


    int rowLen;
    int neighbours;

    QVector<int> rules;

    int maxSize;
    int size;

};

#endif // CARULEMODEL_H
