#include "ApplicantDAO.h"
#include <stdexcept>
#include <cstdlib>

ApplicantDAO::ApplicantDAO(std::shared_ptr<DatabaseConnection> db) : dbConn(db) {}

PGresult* ApplicantDAO::executeQuery(const std::string& query) {
    PGresult* res = PQexec(dbConn->getConnection(), query.c_str());
    return res;
}

void ApplicantDAO::executeCommand(const std::string& query) {
    PGresult* res = executeQuery(query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK &&
        PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::string error = PQerrorMessage(dbConn->getConnection());
        PQclear(res);
        throw std::runtime_error("Query execution failed: " + error);
    }
    PQclear(res);
}

void ApplicantDAO::createTable() {
    std::string query = 
        "CREATE TABLE IF NOT EXISTS applicants ("
        "id SERIAL PRIMARY KEY,"
        "name VARCHAR(100) NOT NULL,"
        "email VARCHAR(100) UNIQUE NOT NULL,"
        "phone VARCHAR(20),"
        "position VARCHAR(100),"
        "experience_years INT,"
        "status VARCHAR(20) DEFAULT 'pending'"
        ");";
    executeCommand(query);
    std::cout << "Applicants table ready." << std::endl;
}

void ApplicantDAO::insert(const Applicant& applicant) {
    std::string query = "INSERT INTO applicants (name, email, phone, position, experience_years) "
                      "VALUES ('" + applicant.getName() + "', '" + 
                      applicant.getEmail() + "', '" + applicant.getPhone() + "', '" + 
                      applicant.getPosition() + "', " + 
                      std::to_string(applicant.getExperienceYears()) + ");";
    executeCommand(query);
    std::cout << "Applicant added successfully!" << std::endl;
}

std::vector<Applicant> ApplicantDAO::findAll() {
    std::vector<Applicant> applicants;
    PGresult* res = executeQuery("SELECT * FROM applicants ORDER BY id;");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        throw std::runtime_error("Failed to retrieve applicants");
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; i++) {
        Applicant app;
        app.setId(atoi(PQgetvalue(res, i, 0)));
        app.setName(PQgetvalue(res, i, 1));
        app.setEmail(PQgetvalue(res, i, 2));
        app.setPhone(PQgetvalue(res, i, 3));
        app.setPosition(PQgetvalue(res, i, 4));
        app.setExperienceYears(atoi(PQgetvalue(res, i, 5)));
        app.setStatus(PQgetvalue(res, i, 6));
        applicants.push_back(app);
    }

    PQclear(res);
    return applicants;
}

std::vector<Applicant> ApplicantDAO::findByPosition(const std::string& position) {
    std::vector<Applicant> applicants;
    std::string query = "SELECT * FROM applicants WHERE position ILIKE '%" + 
                       position + "%';";
    PGresult* res = executeQuery(query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        throw std::runtime_error("Search failed");
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; i++) {
        Applicant app;
        app.setId(atoi(PQgetvalue(res, i, 0)));
        app.setName(PQgetvalue(res, i, 1));
        app.setEmail(PQgetvalue(res, i, 2));
        app.setPhone(PQgetvalue(res, i, 3));
        app.setPosition(PQgetvalue(res, i, 4));
        app.setExperienceYears(atoi(PQgetvalue(res, i, 5)));
        app.setStatus(PQgetvalue(res, i, 6));
        applicants.push_back(app);
    }

    PQclear(res);
    return applicants;
}

void ApplicantDAO::updateStatus(int id, const std::string& status) {
    std::string query = "UPDATE applicants SET status = '" + status + 
                       "' WHERE id = " + std::to_string(id) + ";";
    executeCommand(query);
    std::cout << "Status updated successfully!" << std::endl;
}

void ApplicantDAO::deleteById(int id) {
    std::string query = "DELETE FROM applicants WHERE id = " + std::to_string(id) + ";";
    executeCommand(query);
    std::cout << "Applicant deleted successfully!" << std::endl;
}

Applicant ApplicantDAO::findById(int id) {
    std::string query = "SELECT * FROM applicants WHERE id = " + std::to_string(id) + ";";
    PGresult* res = executeQuery(query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
        PQclear(res);
        throw std::runtime_error("Applicant not found");
    }

    Applicant app;
    app.setId(atoi(PQgetvalue(res, 0, 0)));
    app.setName(PQgetvalue(res, 0, 1));
    app.setEmail(PQgetvalue(res, 0, 2));
    app.setPhone(PQgetvalue(res, 0, 3));
    app.setPosition(PQgetvalue(res, 0, 4));
    app.setExperienceYears(atoi(PQgetvalue(res, 0, 5)));
    app.setStatus(PQgetvalue(res, 0, 6));

    PQclear(res);
    return app;
}
