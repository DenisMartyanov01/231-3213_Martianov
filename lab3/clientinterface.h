#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <QObject>
#include <QNetworkAccessManager>


class Teacher {
public:
    Teacher() = default;

    int id = -1;
    QString name;
    QString phone;
    QString lesson_name;
    QString last_lesson;
    int years_of_teaching;
    bool is_working;

    void print() const {
        qDebug()
        << "Teacher " << id
        << ":\nname - " << name
        << "\nphone - = " << phone
        << "\nlesson_name - " << lesson_name
        << "\nlast_lesson - = " << last_lesson
        << "\nyears_of_teaching - " << years_of_teaching
        << "\nis_working - " << is_working << "\n";
    }
};

class ClientInterface : public QObject
{
    Q_OBJECT
public:
    static ClientInterface * getInstance();
    static ClientInterface * instance;
    ~ClientInterface();

    Teacher Create();
    Teacher Get(int id);
    QList<Teacher> List();
    Teacher Update(int id);
    bool Delete(int id);

    QString url = "http://localhost:7000/api/teacher";

signals:
private:
    explicit ClientInterface(QObject *parent = nullptr);
    QNetworkAccessManager * m_client = nullptr;
};


#endif // CLIENTINTERFACE_H
