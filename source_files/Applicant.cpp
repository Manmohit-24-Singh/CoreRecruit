#include "Applicant.h"

Applicant::Applicant() : id(0), experienceYears(0), status("pending") {}

Applicant::Applicant(const std::string& n, const std::string& e, const std::string& p, 
                     const std::string& pos, int exp)
    : id(0), name(n), email(e), phone(p), position(pos), 
      experienceYears(exp), status("pending") {}

int Applicant::getId() const { return id; }
std::string Applicant::getName() const { return name; }
std::string Applicant::getEmail() const { return email; }
std::string Applicant::getPhone() const { return phone; }
std::string Applicant::getPosition() const { return position; }
int Applicant::getExperienceYears() const { return experienceYears; }
std::string Applicant::getStatus() const { return status; }

void Applicant::setId(int i) { id = i; }
void Applicant::setName(const std::string& n) { name = n; }
void Applicant::setEmail(const std::string& e) { email = e; }
void Applicant::setPhone(const std::string& p) { phone = p; }
void Applicant::setPosition(const std::string& pos) { position = pos; }
void Applicant::setExperienceYears(int exp) { experienceYears = exp; }
void Applicant::setStatus(const std::string& s) { status = s; }

void Applicant::display() const {
    std::cout << "ID: " << id << "\n"
              << "Name: " << name << "\n"
              << "Email: " << email << "\n"
              << "Phone: " << phone << "\n"
              << "Position: " << position << "\n"
              << "Experience: " << experienceYears << " years\n"
              << "Status: " << status << "\n";
}
