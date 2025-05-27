#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->OpenBtn->SetState("normal","hover","press");
    ui->SaveBtn->SetState("normal","hover","press");
    ui->CloseBtn->SetState("normal","hover","press");

    // QDateTime current_time = QDateTime::currentDateTime();
    // QDate now_date = current_time.date();
    // QTime now_time = current_time.time();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateTime);
    timer->start(1000);
    updateTime();

    QObject::connect(ui->OpenBtn,&QPushButton::clicked,this,[&](){
        QString  fileName = QFileDialog::getOpenFileName(this,
            tr("Open Image"), "E:/cpp_test/daly_test/Qt_Test/Q_Mytxt", tr("Text Files (*.txt)"));
        //qDebug()<<"file path is :" <<fileName;

        ui->textEdit->clear();

        file.setFileName(fileName);
        if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
            qDebug()<<"file open error!";
        }
        QTextStream in(&file);

        QString str = ui->comboBox->currentText();
        if (str == "UTF-8") {
            in.setEncoding(QStringConverter::Utf8);
        } else if (str == "UTF-16") {
            in.setEncoding(QStringConverter::Utf16); // 修正为 Utf16
        } else if (str == "GBK") {

        } else {
            in.setEncoding(QStringConverter::Utf8); // 默认回退到 UTF-8
        }

        while(!in.atEnd()){
            QString context = in.readLine();
            qDebug()<<context;
            //ui->textEdit->setText(context);
            ui->textEdit->append(context);
        }
        file.close();
    });

    QObject::connect(ui->SaveBtn,&QPushButton::clicked,this,[&](){
        QString  fileName = QFileDialog::getSaveFileName(this,
            tr("Open Image"), "E:/cpp_test/daly_test/Qt_Test/Q_Mytxt", tr("Text Files (*.txt)"));
        //qDebug()<<"file path is :" <<fileName;

        file.setFileName(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            qDebug()<<"file open error!";
        }
        QTextStream out(&file);
        out.setEncoding(QStringConverter::Utf8);

        QString context = ui->textEdit->toPlainText();
        out<< context;

        file.close();
    });

    QObject::connect(ui->CloseBtn,&QPushButton::clicked,this,[&](){
        ui->textEdit->clear();
        if(file.isOpen()){
            file.close();
        }
    });

    QObject::connect(ui->comboBox,&QComboBox::currentIndexChanged,this,[&](){
        ui->textEdit->clear();

        if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
            qDebug()<<"file open error!";
        }
        QTextStream in(&file);

        QString str = ui->comboBox->currentText();
        if (str == "UTF-8") {
            in.setEncoding(QStringConverter::Utf8);
        } else if (str == "UTF-16") {
            in.setEncoding(QStringConverter::Utf16); // 修正为 Utf16
        } else if (str == "system") {
            //in.setEncoding(QStringConverter::System);
            QStringConverter::encodingForName("GBK");
        } else {
            in.setEncoding(QStringConverter::Utf8); // 默认回退到 UTF-8
        }

        while(!in.atEnd()){
            QString context = in.readLine();
            qDebug()<<context;
            //ui->textEdit->setText(context);
            ui->textEdit->append(context);
        }
        file.close();
    });


    ui->textEdit->installEventFilter(this); // 给textEdit安装了事件过滤器,为滚轮字体做准备

}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Wheel){
        QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent *>(event);
        //检查键盘的CTRL是否被按下
        if (QGuiApplication::keyboardModifiers() & Qt::ControlModifier){
            if (wheelEvent->angleDelta().y() > 0) {
                qDebug()<<"up"; // 滚轮向上滚动
            } else {
                qDebug()<<"down"; // 滚轮向下滚动
            }
        }
        return true;//表示事件已被处理
    }
    return QWidget::eventFilter(watched, event);
}

void Widget::updateTime()
{
    ui->time_lab->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}
