#ifndef CAEVOVIEW_H
#define CAEVOVIEW_H

#include <QWidget>
#include <QTimer>
#include <QImage>

#include "casimulator.h"

namespace Ui {
class CAEvoView;
}

class CAEvoView : public QWidget
{
    Q_OBJECT

public:
    explicit CAEvoView(QWidget *parent = 0);
    ~CAEvoView();

    void setRule(int rule);

private:
    Ui::CAEvoView *ui;

    int rowLen;
    int numRows;
    int filledRows;

    QTimer *updateTimer;

    CASimulator *sim;
    bool *initLine;
    int rule;

    QImage *curImg;
    QImage *futImg;

    void clearImage();
    void addRowToImage(bool *row);

protected:
    void resizeEvent(QResizeEvent *event);

public slots:
    void nextLine();

private slots:
    void on_sbRowLen_editingFinished();
    void on_sbFPS_editingFinished();
};

#endif // CAEVOVIEW_H
