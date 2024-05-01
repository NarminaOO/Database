#include "dbvisual.h"

dbVisual::dbVisual(QWidget *parent) : QWidget(parent) {
    manager = new dbmanager("C:/Users/Narmina/Documents/SQL/SQLite/people.db");

    QFont font ("arial");
    font.setPointSize(10);
    QApplication::setFont(font);

    setWindowTitle("Manage People");
    setMinimumSize( 500, 400);

    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setGeometry(20, 20, 300, 40);

    addButton = new QPushButton("Add Person", this);
    addButton->setGeometry(20, 80, 150, 40);
    addButton->setStyleSheet("background-color: lightBlue");

    removeButton = new QPushButton("Remove Person", this);
    removeButton->setGeometry(190, 80, 150, 40);
    removeButton->setStyleSheet("background-color: lightGreen");

    removeAllButton = new QPushButton("Remove All People", this);
    removeAllButton->setGeometry(360, 80, 150, 40);
    removeAllButton->setStyleSheet("background-color: lightCoral");

    checkButton = new QPushButton("Check Person", this);
    checkButton->setGeometry(20, 140, 150, 40);
    checkButton->setStyleSheet("background-color: Yellow");

    showButton = new QPushButton("Show", this);
    showButton->setGeometry(190, 140, 150, 40);
    showButton->setStyleSheet("background-color: Pink");

    tableView = new QTableView(this);
    int tableSize = 300;
    tableView->setGeometry(20, 200, tableSize, tableSize);

    model = new QSqlTableModel(this);
    model->setTable("people");
    model->select();
    tableView->setModel(model);


    connect(showButton, &QPushButton::clicked, this, &dbVisual::showData);
    connect(addButton, &QPushButton::clicked, this, &dbVisual::addPerson);
    connect(removeButton, &QPushButton::clicked, this, &dbVisual::removePerson);
    connect(removeAllButton, &QPushButton::clicked, this, &dbVisual::removeAllPeople);
    connect(checkButton, &QPushButton::clicked, this, &dbVisual::checkPerson);
}




dbVisual::~dbVisual() {
    delete manager;
}

void dbVisual::showData() {
    model->select();

}

void dbVisual::addPerson() {
    QString name = nameLineEdit->text();
    if (!name.isEmpty()) {
        if (manager->addPerson(name)) {
            //qDebug() << "Person added successfully";
            QMessageBox::information(this,"Success","Person added successfully");
            nameLineEdit->clear();
        } else {
            //qDebug() << "Failed to add person";
            QMessageBox::warning(this,"Error","Failed to add person");
        }
    }
    else
    {
        QMessageBox::warning(this,"Error","Please, enter the name");
    }
}

void dbVisual::removePerson() {
    QString name = nameLineEdit->text();
    if (!name.isEmpty()) {
        if (manager->removePerson(name)) {
            //qDebug() << "Person removed successfully";
            QMessageBox::information(this,"Success","Person removed successfully");
        } else {
            //qDebug() << "Failed to remove person";
            QMessageBox::warning(this,"Error","Failed to remove person");
        }
    }
    else
    {
        QMessageBox::warning(this,"Error","Please, enter the name");
    }
}

void dbVisual::removeAllPeople() {
    if (manager->removeAll()) {
        //qDebug() << "All people removed successfully";
        QMessageBox::information(this,"Success","All people removed successfully");
    } else {
        //qDebug() << "Failed to remove all people";
        QMessageBox::warning(this,"Error","Failed to remove all people");

    }

}

void dbVisual::checkPerson() {
    QString name = nameLineEdit->text();
    if (!name.isEmpty()) {
        if (manager->personExists(name)) {
            //qDebug() << "Person exists";
            QMessageBox::information(this,"Success","Person exists");
        } else {
            //qDebug() << "Person doesn't exist";
            QMessageBox::warning(this,"Error","Person doesn't exist");
        }
    }
    else
    {
        QMessageBox::warning(this,"Error","Please, enter the name");
    }
}
