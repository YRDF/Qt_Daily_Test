#include "citymap.h"

CityMap::CityMap() {
}

QString CityMap::findCity(QString cityname)
{
    if(saveMap.isEmpty()){
        qDebug()<<"star find city";
        initMap();
    }
    auto it = saveMap.find(cityname);
    if(it ==saveMap.end())
        return "";
    else{
        return it.value();
    }

}

void CityMap::initMap()
{
    QFile file(":/citycode.json");
    file.open(QIODevice::ReadOnly);
    QByteArray rawData = file.readAll();
    file.close();
    QJsonDocument jsDoc = QJsonDocument::fromJson(rawData);
    if(jsDoc.isArray()){
        QJsonArray citys = jsDoc.array();
        for(QJsonValue val:citys){
            if(val.isObject()){
                QString cityName = val["city_name"].toString();
                QString cityCode = val["city_code"].toString();
                saveMap.insert(cityName,cityCode);
            }
        }
        qDebug()<<"save finish";
    }
}
