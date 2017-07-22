#include "imagewidget.h"

#include <QPaintEvent>
#include <QPainter>

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    image = QImage();
}

void ImageWidget::setImage(QImage &img)
{
    image = img;
    repaint();
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect r(0, 0, this->width(), this->height());
    painter.drawImage(r, image);
}
