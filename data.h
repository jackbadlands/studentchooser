#ifndef DATA_H
#define DATA_H

#include <QList>
#include <QString>

struct Student {
    QString name;
    Qt::CheckState present;
};

struct Class {
    QList<Student> students;
    QString name;
};


#endif // DATA_H
