#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cstdlib>
#include <QListView>
#include <QScrollBar>
#include <QBoxLayout>


#include "carulemodel.h"
#include "caitemdelegate.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Cellular Automaton 1.3");

    qDebug() << RAND_MAX <<sizeof(long long int);
    CARuleModel *model = new CARuleModel(31, 1, this);
    model->makeData();
    ui->listView->setModel(model);
    ui->listView->setWrapping(true);
    ui->listView->setFlow(QListView::LeftToRight);
    ui->listView->setAlternatingRowColors(true);
    ui->listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listView->setUniformItemSizes(true);
    ui->listView->verticalScrollBar()->setSingleStep(15);
    ui->listView->viewport()->setMinimumWidth(900);
    ui->listView->setMinimumWidth(920);

    CAItemDelegate *delegate = new CAItemDelegate(this);

    ui->listView->setItemDelegate(delegate);
    connect(ui->listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(ruleChanged(QItemSelection,QItemSelection)));

    evoView = new CAEvoView(this);
    ui->layRight->addWidget(evoView);
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

        evoView->setRule(newRule);
        qDebug() <<"Cyrrent rule is " <<newRule;
    }
}
