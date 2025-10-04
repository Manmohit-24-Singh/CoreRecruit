#ifndef APPLICANTCONTROLLER_H
#define APPLICANTCONTROLLER_H

#include "ApplicantService.h"
#include <memory>

class ApplicantController {
private:
    std::shared_ptr<ApplicantService> service;

    void displayMenu();
    void addApplicantUI();
    void viewAllApplicantsUI();
    void searchByPositionUI();
    void updateStatusUI();
    void deleteApplicantUI();
    void viewApplicantDetailsUI();

public:
    ApplicantController(std::shared_ptr<ApplicantService> s);
    void run();
};

#endif
