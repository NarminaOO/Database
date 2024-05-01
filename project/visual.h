#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QSqlQueryModel>
#include "dbmanager.h"

class visual : public QWidget {
    Q_OBJECT
public:
    visual(QWidget *parent = nullptr);
    ~visual();



private:
    void setupUI();
    void setupConnections();

    QLineEdit *nameLineEdit;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *showDatabaseButton;
    QPushButton *findButton;
    QLineEdit *findLineEdit;
    QTableView *tableView;
    dbmanager *dbmanager;
    QSqlQueryModel *model;
    QWidget *databaseWindow;
};

#endif // INTERFACE_H

