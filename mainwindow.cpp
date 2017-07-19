#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cstdlib>
#include <QListView>


#include "carulemodel.h"
#include "caitemdelegate.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << RAND_MAX <<sizeof(long long int);
    CARuleModel *model = new CARuleModel(21, 1, this);
    model->makeData();
    ui->listView->setModel(model);
    ui->listView->setWrapping(true);
    ui->listView->setFlow(QListView::LeftToRight);
    ui->listView->setAlternatingRowColors(true);


    CAItemDelegate *delegate = new CAItemDelegate(this);

    ui->listView->setItemDelegate(delegate);
    connect(ui->listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(ruleChanged(QItemSelection,QItemSelection)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ruleChanged(QItemSelection cur, QItemSelection old)
{
    if(cur.indexes().size() > 0)
    {
        int newRule = cur.indexes().first().data(Qt::WhatsThisRole).toInt();
        qDebug() <<"Cyrrent rule is " <<newRule;
    }
}
