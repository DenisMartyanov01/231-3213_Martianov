#include "clientinterface.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QEventLoop>
#include <QJsonArray>
#include <QVector>

ClientInterface * ClientInterface::instance = nullptr;


ClientInterface::ClientInterface(QObject *parent) : QObject{parent}
{
    m_client = new QNetworkAccessManager();
}


ClientInterface *ClientInterface::getInstance()
{
    if(!instance)
        instance = new ClientInterface();


    return instance;
}

ClientInterface::~ClientInterface()
{
    m_client->deleteLater();
}

Teacher ClientInterface::Get(int id)
{
    Teacher teacher;
    QNetworkReply * repl = m_client->get(QNetworkRequest(QUrl(url + ".get/" + QString::number(id))));

    QEventLoop evtLoop;
    QObject::connect(
        m_client, &QNetworkAccessManager::finished,
        &evtLoop, &QEventLoop::quit);
    evtLoop.exec();

    QJsonParseError jsonErr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson( repl->readAll(), &jsonErr);
    QJsonObject jsonRootObj = jsonDoc.object();

    teacher.id                   = jsonRootObj["id"].toInt();
    teacher.name                 = jsonRootObj["name"].toString();
    teacher.phone                = jsonRootObj["phone"].toString();
    teacher.lesson_name          = jsonRootObj["lesson_name"].toString();
    teacher.last_lesson          = jsonRootObj["last_lesson"].toString();
    teacher.years_of_teaching    = jsonRootObj["years_of_teaching"].toInt();
    teacher.is_working           = jsonRootObj["is_working"].toBool();

    if (teacher.id == 0)
        qDebug() << "Teacher does not exist";
    else
        teacher.print();

    return teacher;
}



QList<Teacher> ClientInterface::List()
{
    QList<Teacher> list;

    QNetworkReply *replay = m_client->get( QNetworkRequest(QUrl(url + ".get")));

    QEventLoop evtLoop;
    QObject::connect(m_client, &QNetworkAccessManager::finished, &evtLoop, &QEventLoop::quit);
    evtLoop.exec();

    QJsonParseError jsonErr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(replay->readAll(), &jsonErr);

    if (jsonDoc.isArray())
    {
        QJsonArray jsonArray = jsonDoc.array();

        for (const QJsonValue &value : jsonArray)
        {
            QJsonObject obj = value.toObject();
            Teacher teacher;

            teacher.id                  = obj["id"].toInt();
            teacher.name                = obj["name"].toString();
            teacher.phone               = obj["phone"].toString();
            teacher.lesson_name         = obj["lesson_name"].toString();
            teacher.last_lesson         = obj["last_lesson"].toString();
            teacher.years_of_teaching   = obj["years_of_teaching"].toInt();
            teacher.is_working          = obj["is_working"].toBool();

            list.append(teacher);
        }

    }

    for(const auto& teacher : list)
        teacher.print();

    return list;
}

Teacher ClientInterface::Create()
{
    Teacher teacher;
    QJsonObject teacherData;
    teacherData["name"]                 = "Иван Иванов";
    teacherData["phone"]                = "+7 (900)1234561";
    teacherData["lesson_name"]          = "Информатика";
    teacherData["last_lesson"]          = "2025-01-06";
    teacherData["years_of_teaching"]    = 12;
    teacherData["is_working"]           = true;

    QJsonDocument doc(teacherData);
    QByteArray data = doc.toJson();
    QNetworkRequest request(QUrl(QString(url + ".create/")));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *replay = m_client->post(request, data);

    QEventLoop evtLoop;
    QObject::connect(
        m_client, &QNetworkAccessManager::finished,
        &evtLoop, &QEventLoop::quit);
    evtLoop.exec();

    QJsonParseError jsonErr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(replay->readAll(), &jsonErr);
    QJsonObject jsonRootObj = jsonDoc.object();

    teacher.id                   = jsonRootObj["id"].toInt();
    teacher.name                 = jsonRootObj["name"].toString();
    teacher.phone                = jsonRootObj["phone"].toString();
    teacher.lesson_name          = jsonRootObj["lesson_name"].toString();
    teacher.last_lesson          = jsonRootObj["last_lesson"].toString();
    teacher.years_of_teaching    = jsonRootObj["years_of_teaching"].toInt();
    teacher.is_working           = jsonRootObj["is_working"].toBool();

    teacher.print();

    return teacher;
}

Teacher ClientInterface::Update(int id)
{

    QJsonObject teacherData;
    teacherData["name"]                 = "Александр Александров";
    teacherData["phone"]                = "+7(900)7654321";
    teacherData["lesson_name"]          = "Физкультура";
    teacherData["last_lesson"]          = "2025-02-06";
    teacherData["years_of_teaching"]    = 2;
    teacherData["is_working"]           = false;

    QJsonDocument doc(teacherData);
    QByteArray data = doc.toJson();
    QNetworkRequest request(QUrl(QString(url + ".update/") + QString::number(id)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply * repl = m_client->post(request, data);

    QEventLoop evtLoop;
    QObject::connect(
        m_client, &QNetworkAccessManager::finished,
        &evtLoop, &QEventLoop::quit);
    evtLoop.exec();

    QJsonParseError jsonErr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(repl->readAll(), &jsonErr);
    QJsonObject jsonRootObj = jsonDoc.object();

    Teacher teacher;
    teacher.id                   = jsonRootObj["id"].toInt();
    teacher.name                 = jsonRootObj["name"].toString();
    teacher.phone                = jsonRootObj["phone"].toString();
    teacher.lesson_name          = jsonRootObj["lesson_name"].toString();
    teacher.last_lesson          = jsonRootObj["last_lesson"].toString();
    teacher.years_of_teaching    = jsonRootObj["years_of_teaching"].toInt();
    teacher.is_working           = jsonRootObj["is_working"].toBool();


    if(teacher.id == 0)
        qDebug() << "Teacher does not exist";
    else
        teacher.print();

    return teacher;
}

bool ClientInterface::Delete(int id)
{
    QNetworkReply * repl = m_client->get(QNetworkRequest(QUrl(QString(url + ".delete/") + QString::number(id))));
    QEventLoop evtLoop;
    QObject::connect(
        m_client, &QNetworkAccessManager::finished,
        &evtLoop, &QEventLoop::quit);
    evtLoop.exec();
    QJsonParseError jsonErr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(repl->readAll(), &jsonErr);
    QJsonObject jsonRootObj = jsonDoc.object();

    Teacher teacher;

    teacher.id                   = jsonRootObj["id"].toInt();
    teacher.name                 = jsonRootObj["name"].toString();
    teacher.phone                = jsonRootObj["phone"].toString();
    teacher.lesson_name          = jsonRootObj["lesson_name"].toString();
    teacher.last_lesson          = jsonRootObj["last_lesson"].toString();
    teacher.years_of_teaching    = jsonRootObj["years_of_teaching"].toInt();
    teacher.is_working           = jsonRootObj["is_working"].toBool();

    if (teacher.id == 0) {
        qDebug() << "Obj was deleted";
        return 1;
    } else {
        qDebug() << "Does not exist";
        return 0;
    }
}
