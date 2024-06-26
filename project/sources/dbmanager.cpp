#include "headers\dbmanager.h"

dbmanager::dbmanager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    if(!m_db.open())
    {
        qDebug()<<"Connection to database failed";
    }
    else
    {
        qDebug()<<"Connection to database ok";
    }
}
bool dbmanager::addPerson(const QString& name)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO people (name) VALUES (:name)");
    query.bindValue(":name",name);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug()<<"addPerson error:"<<query.lastError().text();
    }
    return success;
}
bool dbmanager::personExists(const QString& name)
{
    bool found = false;
    QSqlQuery query;
    query.prepare("SELECT name FROM people WHERE name = (:name)");
    query.bindValue(":name",name);
    if(query.exec())
    {
        if(query.next())
        {
            found = true;
        }
        else
        {
            qDebug()<<"personExists error: "<<query.lastError().text();
        }
    }
    return found;

}
bool dbmanager::removePerson(const QString& name)
{
    bool success = false;
    if(personExists(name))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM people WHERE name = (:name)");
        queryDelete.bindValue(":name",name);
        success = queryDelete.exec();
        if(!success)
        {
            qDebug()<<"remove person failed";
        }
     }
    else{
            qDebug()<<"person doesn't exist";
        }

    return success;
}
void dbmanager::printAll() const
{
   qDebug()<<"People in db:";
   QSqlQuery query ("SELECT *FROM people");
   int idName = query.record().indexOf("name");
   while(query.next())
   {
       QString name = query.value(idName).toString();
       qDebug()<<"==="<<name;
   }
}

bool dbmanager::removeAll()
{
    bool success = false;
    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM PEOPLE");
    if(removeQuery.exec())
    {
        success = true;
    }else
    {
        qDebug()<<"remove failed "<<removeQuery.lastError();
    }
    return success;
}
dbmanager::~dbmanager()
{
    if(m_db.isOpen())
    {
        m_db.close();
    }
}
