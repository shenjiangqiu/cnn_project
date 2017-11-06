#include "widget.h"
#include "ui_widget.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QSpacerItem>
#include<QLabel>
#include<QPushButton>
#include<QPixmap>
#include<QScrollArea>
#include<QMimeData>
#include<QFileDialog>
#include<QMessageBox>
#include<QFont>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mygetTop=new getTop("/home/sjq/cppnew.bin",myn,mym);//-----------new
    mypscons=new scons[myn];

    mainlayout=new QVBoxLayout(this);
    open=new QPushButton(tr("Open"),this);
    open->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    exit=new QPushButton(tr("Exit"),this);
    exit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    about=new QPushButton(tr("About"),this);
    about->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    toplayout=new QHBoxLayout();


    toplayout->addWidget(open);
    toplayout->addWidget(exit);
    toplayout->addWidget(about);
    toplayout->addStretch(1);

    mainlayout->addLayout(toplayout);

    buttonlayout=new QHBoxLayout();
    btlflayout=new QVBoxLayout();
    btrtlayout=new QVBoxLayout();

    inputName=new QLabel(this);
    inputName->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);

    outputName=new QLabel(this);
    outputName->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    inputImage=new QLabel(this);

    inputName->setText(tr("Input:"));
    QFont imFont(inputImage->font());
    imFont.setPointSize(36);
    inputImage->setFont(imFont);
    inputImage->setText(tr("Drop Image HERE"));
    outputName->setText(tr("Output:"));


    inputImage->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    scroll=new QScrollArea(this);
    scroWidget =new QWidget(this);
    scroWidget->setGeometry(0,0,450,2500);
    scroWidget->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    scroll->setWidget(scroWidget);
    scrolayout=new QVBoxLayout();
    inputImage->setScaledContents(true);

    for(int i=0;i<10;i++)
    {
        scroItemLayout[i]=new QHBoxLayout();
        ll[i]=new QLabel(this);
        ll[i]->setText(tr(" "));
        ll[i]->setScaledContents(true);
        scroItemLayout[i]->addWidget(ll[i],3);
        lr[i]=new QLabel(this);
        lr[i]->setText(tr(" "));
        scroItemLayout[i]->addWidget(lr[i],2);
        scrolayout->addLayout(scroItemLayout[i]);
    }
    scroWidget->setLayout(scrolayout);
    btlflayout->addWidget(inputName);
    btlflayout->addWidget(inputImage);
    btrtlayout->addWidget(outputName);
    btrtlayout->addWidget(scroll);

    buttonlayout->addLayout(btlflayout,1);
    buttonlayout->addLayout(btrtlayout,1);
    mainlayout->addLayout(buttonlayout);
    this->setAcceptDrops(true);
    this->setLayout(mainlayout);
    this->setMaximumSize(1366,768);
    this->setGeometry(300,10,724,650);
    QObject::connect(open,&QPushButton::clicked,this,&Widget::on_pushButton_clicked);
    QObject::connect(exit,&QPushButton::clicked,this,&Widget::on_pushButton_2_clicked);
    QObject::connect(about,&QPushButton::clicked,this,&Widget::on_pushButton_3_clicked);



}
void Widget::setLables(const QString &filename)
{
    QPixmap map;
    QByteArray btar=filename.toLatin1();
    char* c_filename=btar.data();
    map.load(filename);
    inputImage->setPixmap(map);
    mygetTop->getValue(c_filename,mypscons);//fill mypscons with top simulate pictures
    for(int i=0;i<10;i++)
        cout<<mypscons[i].i+1<<"  / "<<mypscons[i].value<<endl;
    for(int i=0;i<10;i++)
    {
        ll[i]->setPixmap(QPixmap(QString("/home/sjq/image/")+QString::number(mypscons[i].i+1)+QString(".jpg")));

        lr[i]->setText(QString("cos: ")+QString("%1").arg(mypscons[i].value));

    }
}
void Widget::dragEnterEvent(QDragEnterEvent *event)
{
        event->acceptProposedAction();

}

void Widget::dropEvent(QDropEvent *event)
{

    QList<QUrl> urls=event->mimeData()->urls();
    if(urls.isEmpty())
        return;
    QString filename=urls[0].toLocalFile();
    setLables(filename);

}

void Widget::on_pushButton_clicked()
{

    QString filename=QFileDialog::getOpenFileUrl(this,tr("Open Image"),tr("/home"),tr("Image Files(*.jpg)")).toLocalFile();
    if(filename.length()==0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }else{
        setLables(filename);
    }
}

void Widget::on_pushButton_2_clicked()
{
    this->close();
}

void Widget::on_pushButton_3_clicked()
{
    QMessageBox::information(this,tr("imfomation about us"),tr("a cnn image recognazition software"),tr("Ok"));
}

Widget::~Widget()
{
    delete ui;
    delete mygetTop;//----------------------------------delete
    delete[] mypscons;
}
