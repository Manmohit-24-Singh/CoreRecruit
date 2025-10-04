#include "ApplicantService.h"
#include <stdexcept>

ApplicantService::ApplicantService(std::shared_ptr<ApplicantDAO> d) : dao(d) {}

void ApplicantService::addApplicant(const Applicant& applicant) {
    if (applicant.getName().empty() || applicant.getEmail().empty()) {
        throw std::invalid_argument("Name and email are required");
    }
    dao->insert(applicant);
}

std::vector<Applicant> ApplicantService::getAllApplicants() {
    return dao->findAll();
}

std::vector<Applicant> ApplicantService::searchByPosition(const std::string& position) {
    return dao->findByPosition(position);
}

void ApplicantService::changeStatus(int id, const std::string& status) {
    if (status != "pending" && status != "interviewed" && 
        status != "hired" && status != "rejected") {
        throw std::invalid_argument("Invalid status");
    }
    dao->updateStatus(id, status);
}

void ApplicantService::removeApplicant(int id) {
    dao->deleteById(id);
}

Applicant ApplicantService::getApplicant(int id) {
    return dao->findById(id);
}
