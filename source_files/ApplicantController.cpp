#include "ApplicantController.h"
#include <iostream>

ApplicantController::ApplicantController(std::shared_ptr<ApplicantService> s) : service(s) {}

void ApplicantController::displayMenu() {
    std::cout << "\n=== Job Applicant Inventory System ===" << std::endl;
    std::cout << "1. Add Applicant" << std::endl;
    std::cout << "2. View All Applicants" << std::endl;
    std::cout << "3. Search by Position" << std::endl;
    std::cout << "4. Update Applicant Status" << std::endl;
    std::cout << "5. Delete Applicant" << std::endl;
    std::cout << "6. View Applicant Details" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "Choice: ";
}

void ApplicantController::addApplicantUI() {
    std::string name, email, phone, position;
    int exp;

    std::cout << "\n--- Add New Applicant ---" << std::endl;
    std::cout << "Name: ";
    std::getline(std::cin, name);
    std::cout << "Email: ";
    std::getline(std::cin, email);
    std::cout << "Phone: ";
    std::getline(std::cin, phone);
    std::cout << "Position: ";
    std::getline(std::cin, position);
    std::cout << "Years of Experience: ";
    std::cin >> exp;
    std::cin.ignore();

    Applicant applicant(name, email, phone, position, exp);
    service->addApplicant(applicant);
}

void ApplicantController::viewAllApplicantsUI() {
    std::cout << "\n=== All Applicants ===" << std::endl;
    auto applicants = service->getAllApplicants();

    if (applicants.empty()) {
        std::cout << "No applicants found." << std::endl;
        return;
    }

    for (const auto& app : applicants) {
        std::cout << std::string(50, '-') << std::endl;
        app.display();
    }
}

void ApplicantController::searchByPositionUI() {
    std::string position;
    std::cout << "Position to search: ";
    std::getline(std::cin, position);

    auto results = service->searchByPosition(position);

    if (results.empty()) {
        std::cout << "No applicants found for position: " << position << std::endl;
        return;
    }

    std::cout << "\n=== Search Results ===" << std::endl;
    for (const auto& app : results) {
        std::cout << std::string(50, '-') << std::endl;
        app.display();
    }
}

void ApplicantController::updateStatusUI() {
    int id;
    std::string status;

    std::cout << "Applicant ID: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "New Status (pending/interviewed/hired/rejected): ";
    std::getline(std::cin, status);

    service->changeStatus(id, status);
}

void ApplicantController::deleteApplicantUI() {
    int id;
    std::cout << "Applicant ID to delete: ";
    std::cin >> id;
    std::cin.ignore();

    service->removeApplicant(id);
}

void ApplicantController::viewApplicantDetailsUI() {
    int id;
    std::cout << "Applicant ID: ";
    std::cin >> id;
    std::cin.ignore();

    auto app = service->getApplicant(id);
    std::cout << "\n=== Applicant Details ===" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    app.display();
}

void ApplicantController::run() {
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();

        try {
            switch (choice) {
                case 1: addApplicantUI(); break;
                case 2: viewAllApplicantsUI(); break;
                case 3: searchByPositionUI(); break;
                case 4: updateStatusUI(); break;
                case 5: deleteApplicantUI(); break;
                case 6: viewApplicantDetailsUI(); break;
                case 7: std::cout << "Goodbye!" << std::endl; return;
                default: std::cout << "Invalid choice!" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
