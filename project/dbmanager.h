#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

class dbmanager
{
public:
    dbmanager(const QString &path);
    bool addPerson(const QString& name);
    bool personExists(const QString& name);
    bool removePerson(const QString& name);
    void printAll() const;
    bool removeAll();
    ~dbmanager();
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
