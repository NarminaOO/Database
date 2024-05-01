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
  
