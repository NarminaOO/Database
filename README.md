# People Database 
This project allows to manage a SQLite database which contains the names of people. It provides functionalities to add, remove, check, and display people's information stored in the database.

![image](https://github.com/NarminaOO/Database/assets/149943881/ffcaf479-7c90-4918-affc-03223f83f107)



## Features
+ **Add Person:** Add a new person to the database.

+ **Remove Person:** Remove a person from the database.

+ **Remove All People:** Remove all records from the database.

+ **Check Person:** Check if a person exists in the database.

+ **Show :** View all the data stored in the database.

## Files 
+ dbmanager.cpp
  > contains a `dbmanager` class that provides main functionality of the database that was listed above (adding, removing etc.).
+ dbmanager.h
  > a header file of the class `dbmanager`.
+ dbvisual.cpp
  > a `dbVisual` class that contains all the code related to interface.
+ dbvisual.h
  > a header file of the class `dbVisual`
+ main.cpp
  > `main` function that calls for the database widget.

## Code Explanation 
### in dbmanager.cpp

**Constructor** (`dbmanager::dbmanager(const QString& path)`):
* This constructor initializes the `dbmanager` object with a path to the SQLite database file.
* It creates a QSqlDatabase object, sets its type to SQLite, and sets the database name to the provided path.
* Then it tries to open the database. If successful, it prints "Connection to database ok", otherwise "Connection to database failed".

**Function** `bool dbmanager::addPerson(const QString& name)`:
* This function is used to add a person's name to the database.
* It prepares an SQL query to insert a record into the "people" table with the provided name.
* If the query executes successfully, it sets `success` to true; otherwise, it prints an error message.

**Function** `bool dbmanager::personExists(const QString& name)`:
* This function checks if a person with the given name exists in the database.
* It prepares an SQL query to select records from the "people" table where the name matches the provided name.
* If the query executes successfully and at least one record is found, it sets `found` to true.

**Function** `bool dbmanager::removePerson(const QString& name)`:
* This function removes a person from the database.
* It first checks if the person exists by calling `personExists`.
* If the person exists, it prepares an SQL query to delete the person's record from the "people" table.
* If the deletion is successful, it sets `success` to true; otherwise, it prints an error message.

**Function** `void dbmanager::printAll() const`:
* This function prints all people stored in the database.
* It prepares an SQL query to select all records from the "people" table.
* It retrieves the names from the query results and prints them.

**Function** `bool dbmanager::removeAll()`:
* This function removes all records from the "people" table.
* It prepares an SQL query to delete all records from the "people" table.
* If the deletion is successful, it sets `success` to true; otherwise, it prints an error message.

**Destructor** (`dbmanager::~dbmanager()`):
* This destructor ensures that the database connection is closed when the `dbmanager` object is destroyed.

### in dbVisual.cpp
#### Header Inclusion:
```c++
#include "dbvisual.h"
```

The code includes the header file `"dbvisual.h"`, which contains declarations necessary for the `dbVisual` class.
#### Constructor `dbVisual::dbVisual`: 
This is the constructor for the `dbVisual` class. It initializes the GUI components and sets up the initial appearance and behavior of the window.
Here's what it does:
* Initializes a `dbmanager` object `manager` with the path to a SQLite database file.
  ```c++
  manager = new dbmanager("C:/Users/Narmina/Documents/SQL/SQLite/people.db");
  ```
* Sets the font for the application.
  ```c++
    QFont font("arial"); 
    font.setPointSize(10);
    QApplication::setFont(font);
  ```
* Sets the window title and minimum size.
  ```c++
    setWindowTitle("Manage People"); // Sets window title
    setMinimumSize(500, 400); // Sets minimum window size
  ```
* Creates various GUI elements such as line edits, buttons, and a table view.
  ```c++
    nameLineEdit = new QLineEdit(this); // Creates line edit for entering names
    nameLineEdit->setGeometry(20, 20, 300, 40);

    addButton = new QPushButton("Add Person", this); // Creates button for adding a person
    addButton->setGeometry(20, 80, 150, 40);
    addButton->setStyleSheet("background-color: lightBlue");

    removeButton = new QPushButton("Remove Person", this); // Creates button for removing a person
    removeButton->setGeometry(190, 80, 150, 40);
    removeButton->setStyleSheet("background-color: lightGreen");

    removeAllButton = new QPushButton("Remove All People", this); // Creates button for removing all people
    removeAllButton->setGeometry(360, 80, 150, 40);
    removeAllButton->setStyleSheet("background-color: lightCoral");

    checkButton = new QPushButton("Check Person", this); // Creates button for checking if a person exists
    checkButton->setGeometry(20, 140, 150, 40);
    checkButton->setStyleSheet("background-color: Yellow");

    showButton = new QPushButton("Show", this); // Creates button for showing data
    showButton->setGeometry(190, 140, 150, 40);
    showButton->setStyleSheet("background-color: Pink");

    tableView = new QTableView(this); // Creates table view
    int tableSize = 300;
    tableView->setGeometry(20, 200, tableSize, tableSize);
  ```
* Initializes a `QSqlTableModel` object `model` and associates it with the `"people"` table from the SQLite database.
  ```c++
    model = new QSqlTableModel(this); 
    model->setTable("people"); 
    model->select(); // Selects data from the table
    tableView->setModel(model); // Sets model for table view
  ```
* Connects various buttons to their respective slots (functions) using the `connect` function.
  ```c++
    connect(showButton, &QPushButton::clicked, this, &dbVisual::showData);
    connect(addButton, &QPushButton::clicked, this, &dbVisual::addPerson);
    connect(removeButton, &QPushButton::clicked, this, &dbVisual::removePerson);
    connect(removeAllButton, &QPushButton::clicked, this, &dbVisual::removeAllPeople);
    connect(checkButton, &QPushButton::clicked, this, &dbVisual::checkPerson);
  ``` 
#### Destructor `dbVisual::~dbVisual`: 
```c++
dbVisual::~dbVisual() {
    delete manager;
}
```
This is the destructor for the `dbVisual` class. It deallocates any resources acquired by the dbmanager object.

#### Slot Functions:
These are functions that are called when certain actions occur in the GUI.

+ `showData()`:
```c++
  void dbVisual::showData() {
    model->select();
}
```
Selects and displays data from the `"people"` table in the table view.
+ `addPerson()`:
```c++
  void dbVisual::addPerson() {
    QString name = nameLineEdit->text(); // Gets name from line edit
    if (!name.isEmpty()) { // Checks if name is not empty
        if (manager->addPerson(name)) { // Attempts to add person to database
            QMessageBox::information(this, "Success", "Person added successfully"); // Displays success message
            nameLineEdit->clear(); // Clears line edit
        } else {
            QMessageBox::warning(this, "Error", "Failed to add person"); // Displays error message
        }
    } else {
        QMessageBox::warning(this, "Error", "Please, enter the name"); // Displays error message for empty name
    }
}
```
  Adds a person to the database using the name entered in the line edit.
  
+ `removePerson()`:
```c++
  void dbVisual::removePerson() {
    QString name = nameLineEdit->text(); // Gets name from line edit
    if (!name.isEmpty()) { // Checks if name is not empty
        if (manager->removePerson(name)) { // Attempts to remove person from database
            QMessageBox::information(this, "Success", "Person removed successfully"); // Displays success message
        } else {
            QMessageBox::warning(this, "Error", "Failed to remove person"); // Displays error message
        }
    } else {
        QMessageBox::warning(this, "Error", "Please, enter the name"); // Displays error message for empty name
    }
}
```
  Removes a person from the database based on the name entered in the line edit.
+ `removeAllPeople()`:
```c++
 void dbVisual::removeAllPeople() {
    if (manager->removeAll()) { // Attempts to remove all people from database
        QMessageBox::information(this, "Success", "All people removed successfully"); // Displays success message
    } else {
        QMessageBox::warning(this, "Error", "Failed to remove all people"); // Displays error message
    }
}
```
  Removes all people from the database.
+ `checkPerson()`:
```c++
  void dbVisual::checkPerson() {
    QString name = nameLineEdit->text(); // Gets name from line edit
    if (!name.isEmpty()) { // Checks if name is not empty
        if (manager->personExists(name)) { // Checks if person exists in database
            QMessageBox::information(this, "Success", "Person exists"); // Displays success message
        } else {
            QMessageBox::warning(this, "Error", "Person doesn't exist"); // Displays error message
        }
    } else {
        QMessageBox::warning(this, "Error", "Please, enter the name"); // Displays error message for empty name
    }
}
```
  Checks if a person with the given name exists in the database.


#### Error Handling: 
Error Handling: If a user action fails (e.g., adding a person fails due to an empty name or a person not existing in the database), error messages are displayed using `QMessageBox`

### in main.cpp
```c++
#include <QApplication>
#include "dbvisual.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    dbVisual window;
    window.show();

    return app.exec();
}
```
This main function sets up the Qt application, creates an object of the `dbVisual` class, displays the window, and runs the application.


## How to use 
1. Clone the repository.
2. Download the database file and make sure that your code has a correct path to it.
3. Open the project in Qt Creator or your preferred IDE.
4. Build and run the project.
 
