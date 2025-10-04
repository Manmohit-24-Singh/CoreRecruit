#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <libpq-fe.h>
#include <string>
#include <stdexcept>
#include <iostream>

class DatabaseConnection {
private:
    PGconn* conn;
    std::string connectionString;

    void validateConnection();

public:
    DatabaseConnection(const std::string& host, const std::string& port, 
                       const std::string& dbname, const std::string& user, 
                       const std::string& password);
    ~DatabaseConnection();

    PGconn* getConnection();
    bool isConnected() const;
};

#endif
