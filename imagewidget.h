#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);

    void setImage(QImage &img);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QImage image;

signals:

public slots:
};

#endif // IMAGEWIDGET_H
