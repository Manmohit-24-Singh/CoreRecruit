#ifndef APPLICANTDAO_H
#define APPLICANTDAO_H

#include "Applicant.h"
#include "DatabaseConnection.h"
#include <vector>
#include <memory>

class ApplicantDAO {
private:
    std::shared_ptr<DatabaseConnection> dbConn;
    PGresult* executeQuery(const std::string& query);
    void executeCommand(const std::string& query);

public:
    ApplicantDAO(std::shared_ptr<DatabaseConnection> db);

    void createTable();
    void insert(const Applicant& applicant);
    std::vector<Applicant> findAll();
    std::vector<Applicant> findByPosition(const std::string& position);
    void updateStatus(int id, const std::string& status);
    void deleteById(int id);
    Applicant findById(int id);
};

#endif
