#include "ApplicantController.h"
#include "ApplicantService.h"
#include "ApplicantDAO.h"
#include "DatabaseConnection.h"
#include <memory>
#include <iostream>

int main() {
    try {
        std::string host = "localhost";
        std::string dbname = "applicant_db";
        std::string user = "corerecruit_user";
        std::string password = "StrongPassword123";
        std::string port = "5433";


        auto dbConn = std::make_shared<DatabaseConnection>(host, port, dbname, user, password);
        auto dao = std::make_shared<ApplicantDAO>(dbConn);
        dao->createTable();

        auto service = std::make_shared<ApplicantService>(dao);
        auto controller = std::make_shared<ApplicantController>(service);

        controller->run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
