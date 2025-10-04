#ifndef APPLICANT_H
#define APPLICANT_H

#include <string>
#include <iostream>

class Applicant {
private:
    int id;
    std::string name;
    std::string email;
    std::string phone;
    std::string position;
    int experienceYears;
    std::string status;

public:
    Applicant();
    Applicant(const std::string& n, const std::string& e, const std::string& p, 
              const std::string& pos, int exp);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getPosition() const;
    int getExperienceYears() const;
    std::string getStatus() const;

    // Setters
    void setId(int i);
    void setName(const std::string& n);
    void setEmail(const std::string& e);
    void setPhone(const std::string& p);
    void setPosition(const std::string& pos);
    void setExperienceYears(int exp);
    void setStatus(const std::string& s);

    void display() const;
};

#endif
