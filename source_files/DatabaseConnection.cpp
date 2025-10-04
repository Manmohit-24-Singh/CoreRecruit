#include "DatabaseConnection.h"

DatabaseConnection::DatabaseConnection(const std::string& host, const std::string& port, 
                                       const std::string& dbname, const std::string& user, 
                                       const std::string& password) {
    connectionString = "host=" + host + " port=" + port +
                      " dbname=" + dbname + " user=" + user +
                      " password=" + password;
    conn = PQconnectdb(connectionString.c_str());
    validateConnection();
    std::cout << "Database connected successfully!" << std::endl;
}

DatabaseConnection::~DatabaseConnection() {
    if (conn) {
        PQfinish(conn);
        std::cout << "Database connection closed." << std::endl;
    }
}

void DatabaseConnection::validateConnection() {
    if (PQstatus(conn) != CONNECTION_OK) {
        throw std::runtime_error("Database connection failed: " +
                                 std::string(PQerrorMessage(conn)));
    }
}

PGconn* DatabaseConnection::getConnection() { return conn; }

bool DatabaseConnection::isConnected() const {
    return PQstatus(conn) == CONNECTION_OK;
}
