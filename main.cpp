/* Author: Trevor Pierce
 * Date of last edit: 12/11/17
 *
 * Final Project
 * Description: This file will allow a user to log in and then perform various
 * course activities, like viewing grades, sending fake emails, and viewing the class roster.
 * The program will also write all of the user's activities to a log file for
 * security purposes
 */
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "data.h"
#include "models.h"

using namespace Models;

// Main function prototypes
void check_password(std::string stored_password);
User get_account_info();
void view_roster();
void view_grades(User &);
void send_email(User &);

int main() {
    // Setup logging
    std::ofstream log("info.log");
    auto old_rdbuf = std::clog.rdbuf();
    std::clog.rdbuf(log.rdbuf());

    bool logout = false;
    int menu_choice;

    User current_user = get_account_info();

    while (!logout) { // If the user hasn't pressed 4
        std::system("CLS"); // This clears the screen
        std::cout << "1. View Class Roster\n";
        std::cout << "2. View Your Grades\n";
        std::cout << "3. Send Email\n";
        std::cout << "4. Exit\n";

        std::cin >> menu_choice;
        std::system("CLS");
        std::time_t now = std::time(nullptr);

        switch (menu_choice) {
            case 1: view_roster(); // Calls a function to allow the user to view the class roster
                std::clog << current_user.get_username() << " Action: " << menu_choice << " Time/Date: " << std::asctime(std::localtime(&now)) << std::endl;
                break;
            case 2: view_grades(current_user); // Allows students to view their grades
                std::clog << current_user.get_username() << " Action: " << menu_choice << " Time/Date: " << std::asctime(std::localtime(&now)) << std::endl;
                break;
            case 3: send_email(current_user); // Allows users to feel like they're sending an email
                std::clog << current_user.get_username() << " Action: " << menu_choice << " Time/Date: " << std::asctime(std::localtime(&now)) << std::endl;
                break;
            case 4: logout = true;
                std::clog.rdbuf(old_rdbuf);
                log.close();
                break;
            default: break;
        }
    }

    return EXIT_SUCCESS;
}

void check_password(std::string stored_password) {
    bool invalid_password = true;
    std::string in_password;

    while (invalid_password) {
        std::cout << "Please enter your password: ";
        std::cin >> in_password;

        if (in_password == "EXIT") {
            std::exit(EXIT_FAILURE);
        }

        if (in_password == stored_password) {
            invalid_password = false;
        } else {
            std::cerr << "Invalid password" << std::endl;
        }
    }
}

User get_account_info() {
    bool invalid_username = true;
    std::string in_username;
    User current_user;

    while (invalid_username) {
        std::cout << "Hello! Please enter your username: ";
        std::cin >> in_username;

        for (user_data_t user : Data::user_data) {
            if (in_username == "EXIT") {
                std::exit(EXIT_FAILURE);
            }

            if (user.username == in_username) {
                invalid_username = false;
                check_password(user.password);
                current_user = User(user.username, user.permissions, user.grades);
                break;
            }
        }

        if (invalid_username) {
            std::cerr << "Invalid username" << std::endl;
        }
    }

    return current_user;
}

// This function displays the names and emails of people in the class
void view_roster() {
    for (person_t person : Data::roster) {
        std::cout << "Name: " << person.name;
        std::cout << " | Email: " << person.email;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::system("pause");
}

// Check grades if user is a student.
// Otherwise, the user is told they cannot view their grades.
void view_grades(User &user) {
    if (user.get_permissions() == Permissions::student) {
        std::vector<assignment_t> grades = user.get_grades();

        for (assignment_t grade : grades) {
            std::cout << "Assignment name: " << grade.name << std::endl;
            std::cout << "Score          : " << grade.score << std::endl;
        }

        std::cout << std::endl;
    } else {
        std::cerr << "Only students can view grades, since only they have assignments";
    }
    std::cout << std::endl;
    system("pause");
}

void send_email(User &user) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string email, receiver;

    std::cout << "Please write an email below\n";
    std::getline(std::cin, email);

    std::cout << "Who would like to send the email to?\n";
    std::getline(std::cin, receiver);

    bool email_found = false;

    for (person_t person : Data::roster) {
        if (person.name == receiver) {
            email_found = true;
            break;
        }
    }

    if (email_found) {
        std::cout << "Email has been sent from " << user.get_username() << " to " << receiver;
    } else {
        std::cerr << "Sorry, we could not find " << receiver << " in our database";
    }

    std::cout << std::endl;
    std::system("pause");
}

