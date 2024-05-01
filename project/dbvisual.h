#ifndef DBVISUAL_H
#define DBVISUAL_H
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QSqlTableModel>
#include "dbmanager.h"
#include <QMessageBox>
#include <QFont>
class dbVisual : public QWidget {
    Q_OBJECT

public:
    explicit dbVisual(QWidget *parent = nullptr);
    ~dbVisual();

private slots:
    void showData();
    void addPerson();
    void removePerson();
    void removeAllPeople();
    void checkPerson();

private:
    QLineEdit *nameLineEdit;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *removeAllButton;
    QPushButton *checkButton;
    QPushButton *showButton;
    QTableView *tableView;
    QSqlTableModel *model;
    dbmanager *manager;
};

#endif // DBVISUAl_H
