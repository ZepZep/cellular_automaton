#include "caevoview.h"
#include "ui_caevoview.h"

#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>

#include <QDebug>

CAEvoView::CAEvoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CAEvoView)
{
    ui->setupUi(this);

    updateTimer = new QTimer(this);
    sim = new CASimulator;

    connect(updateTimer, SIGNAL(timeout()), this, SLOT(nextLine()));

    curImg = new QImage();
    futImg = new QImage();
    initLine = new bool[1];

    rule = 0;
    sim->setRule(rule);
    updateTimer->stop();
    on_sbRowLen_editingFinished();
}

CAEvoView::~CAEvoView()
{
    delete ui;
}

void CAEvoView::setRule(int rule)
{
    this->rule = rule;
    sim->setRule(rule);

    clearImage();
    updateTimer->start(1000 / ui->sbFPS->value());
}

void CAEvoView::clearImage()
{
    delete curImg;
    delete futImg;

    int w = rowLen;
    int h = (ui->imgWidget->height()*rowLen) / ui->imgWidget->width();
    numRows = h;
    filledRows = 0;

    curImg = new QImage(w, h, QImage::Format_Mono);
    curImg->fill(0);
    futImg = new QImage(w, h, QImage::Format_Mono);
    futImg->fill(0);

    sim->setLine(initLine, rowLen);
    addRowToImage(initLine);
}

void CAEvoView::addRowToImage(bool *row)
{
    int fillLine = 0;
    if(filledRows >= numRows)
    {
        fillLine = numRows - 1;
        //shift
        uchar *data = curImg->bits();
        uchar *dest = futImg->bits();
        memcpy(dest, data+curImg->bytesPerLine(), curImg->byteCount()-curImg->bytesPerLine());

        //flip
        QImage * tmp = curImg;
        curImg = futImg;
        futImg = tmp;
    }
    else
    {
        fillLine = filledRows++;
    }

    for(int x=0; x<rowLen; x++)
    {
        curImg->setPixel(x, fillLine, row[x]);
    }
}

void CAEvoView::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    clearImage();
    ui->imgWidget->setImage(*curImg);
}

void CAEvoView::nextLine()
{
    bool *nl = sim->nextLine();
    addRowToImage(nl);
    ui->imgWidget->setImage(*curImg);
}

void CAEvoView::on_sbRowLen_editingFinished()
{
    rowLen = ui->sbRowLen->value();
    initLine = new bool[rowLen];
    for(int i=0; i<rowLen; i++)
        initLine[i] = 0;
    initLine[(rowLen+1)/2 - 1] = 1;
    clearImage();
}

void CAEvoView::on_sbFPS_editingFinished()
{
    updateTimer->start(1000 / ui->sbFPS->value());
}
