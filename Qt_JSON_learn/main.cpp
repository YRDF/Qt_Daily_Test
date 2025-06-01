#include "widget.h"

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

//JSON数据的构建
int createJsonFile(){
    //创建JSON对象 以键值对形式
    QJsonObject rootJson;
    rootJson["name"] = "zhangsan";
    rootJson["age"] = 23;
    rootJson["hobby"] = "game";

    //创建一个可放入JSON的数组
    QJsonArray jsarray;
    jsarray.append("wjqmachine");
    jsarray.append(6657);
    jsarray.append("upup");

    //array数组放入JSON中
    rootJson["machine"] = jsarray;

    //JSON对象要嵌套的JSON对象
    QJsonObject anotherJson;
    anotherJson["day0"] = "6-1";
    anotherJson["weather"] = "cloudy";
    anotherJson["log"] = 0;

    //anotherJson对象嵌入rootJson
    rootJson["date0"] = anotherJson;

    //将JSON对象转化为JSON文档
    QJsonDocument jsonDoc(rootJson);

    //将JSON文档转换为Qt的字符串
    QByteArray jsQbyte = jsonDoc.toJson(QJsonDocument::Indented);

    qDebug()<<jsQbyte;

    //将json数据写入文件
    QFile file("E:/cpp_test/daly_test/Qt_Test/Qt_JSON_learn/output.json");
    if(!file.open(QIODevice::WriteOnly)){
        qDebug()<<"file open faile!";
        return 0;
    }
    file.write(jsQbyte);
    file.close();
    qDebug() << "JSON data saved to output.json";
    return 0;
}


//JSON的数据解析
void parseJson(){
    //读取JSON文件到QByteArray中
    QFile file("E:/cpp_test/daly_test/Qt_Test/Qt_JSON_learn/output.json");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"file open failed!";
    }
    QByteArray jsData = file.readAll();
    file.close();
    //转换为JSON文档
    QJsonDocument jsDoc = QJsonDocument::fromJson(jsData);

    //检查JSON文档不为空并且包含JSON对象
    if(!jsDoc.isNull() && jsDoc.isObject()){
        //获取JSON对象
        QJsonObject jsobj = jsDoc.object();
        // 访问对象的键值
        QString name = jsobj["name"].toString();
        int age = jsobj["age"].toInt();
        QString hobby = jsobj["hobby"].toString();
        qDebug() << "Name:" << name;
        qDebug() << "age:" << age;
        qDebug() << "hobby:" << hobby;
        //处理JSON数组
        if(jsobj.contains("machine")&&jsobj["machine"].isArray()){
            QJsonArray myarray = jsobj["machine"].toArray();
            for(const QJsonValue&value : myarray){
                QJsonValue::Type t = value.type();
                switch(t){
                case QJsonValue::Double:
                    qDebug()<<QString::number(value.toDouble());
                    break;
                case QJsonValue::String:
                    qDebug()<< value.toString();
                    break;
                case QJsonValue::Object:
                    break;
                }
            }
        }
        //处理josnobject
        if(jsobj.contains("date0")&&jsobj["date0"].isObject()){
            QJsonObject daysobj = jsobj["date0"].toObject();
            qDebug() <<daysobj["day0"].toString();
            qDebug() <<daysobj["log"].toDouble();
            qDebug() <<daysobj["weather"].toString();
        }
    }
}

int main(int argc, char *argv[])
{
    //createJsonFile();
    parseJson();
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
