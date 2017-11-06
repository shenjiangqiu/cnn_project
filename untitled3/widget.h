#ifndef WIDGET_H
#define WIDGET_H

#define myn 11772
#define mym 9216
#include <QWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QSpacerItem>
#include<QLabel>
#include<QPushButton>
#include<QPixmap>
#include<QScrollArea>
#include<QWidget>
#include"gettop.h"
#include"figue.h"
#include<QDragEnterEvent>
#include<QDropEvent>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void on_scro_sizeChange(int w,int h);

private:
    Ui::Widget *ui;
    QVBoxLayout *mainlayout;
    QPushButton* open;

    QPushButton* exit;

    QPushButton* about;

    QHBoxLayout *toplayout;

    QHBoxLayout *buttonlayout;
    QVBoxLayout *btlflayout;
    QVBoxLayout *btrtlayout;
    QLabel* inputName;
    QLabel* outputName;
    QLabel* inputImage;
    QScrollArea* scroll;
    QWidget* scroWidget;
    QVBoxLayout* scrolayout;
    QHBoxLayout* scroItemLayout[10];
    QLabel *ll[10];
    QLabel *lr[10];


    getTop *mygetTop;

    pscons mypscons;
    void setLables(const QString& filename);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


};

#endif // WIDGET_H
