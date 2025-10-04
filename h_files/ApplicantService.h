#ifndef APPLICANTSERVICE_H
#define APPLICANTSERVICE_H

#include "ApplicantDAO.h"
#include <vector>
#include <memory>

class ApplicantService {
private:
    std::shared_ptr<ApplicantDAO> dao;

public:
    ApplicantService(std::shared_ptr<ApplicantDAO> d);

    void addApplicant(const Applicant& applicant);
    std::vector<Applicant> getAllApplicants();
    std::vector<Applicant> searchByPosition(const std::string& position);
    void changeStatus(int id, const std::string& status);
    void removeApplicant(int id);
    Applicant getApplicant(int id);
};

#endif
