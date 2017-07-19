#include "carulemodel.h"

#include <ctime>
#include <QtMath>
#include <QTime>
#include <QSet>
#include <QVector>
#include <QSize>
#include <QImage>


#include <QDebug>

typedef long long int lli;

CARuleModel::CARuleModel(int rowLen, int neighbourhood, QObject *parent)
    : QAbstractListModel(parent)
{
    this->rowLen = rowLen;
    this->neighbours = neighbourhood;

    qsrand(std::time(NULL));

    maxSize = 1000;

    float s = pow(2, 1 << (2*neighbourhood+1));
    if(s > maxSize) size = maxSize;
    else size = s;

    qDebug() << "Created model with size " <<size;

}

void CARuleModel::makeData()
{
    //QSet<lli> usedRules;
    rules.fill(0, size);

    if (neighbours == 1)
    {

        for(int i=0; i<size; i++)
            rules[i] = i;
    }

//    for(int i=0; i<maxSize;)
//    {
//        lli c = 0;
//        c += qrand();
//        c << 31;
//        c += qrand();
//        c << 31;
//        c += qrand();

//        if( !usedRules.contains(c) )
//        {
//            usedRules.insert(c);
//            i++;
//        }
//    }
}

int CARuleModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return rules.size();
}

QVariant CARuleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return makeImage(index.row());
        break;
    case Qt::ToolTipRole:
        return "Rule " + QString::number(rules[index.row()]);
        break;
    case Qt::WhatsThisRole:
        return rules[index.row()];
        break;
    case Qt::SizeHintRole:
        return QSize(260, 300);
        break;
    default:
        return QVariant();
        break;
    }
    return QVariant();
}

QImage CARuleModel::makeImage(int ruleNum) const
{
    //qDebug() << "Generating " <<ruleNum;
    qsrand( ruleNum );
    QImage img(rowLen, rowLen, QImage::Format_Mono);

    for(int y=0; y<rowLen; y++)
    {
        int rnum = qrand();
        for(int x=0; x<rowLen; x++)
        {
            img.setPixel(x, y, (rnum >> x) % 2);
        }
    }

    return img;
}
