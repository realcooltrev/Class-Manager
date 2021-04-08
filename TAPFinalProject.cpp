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
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

struct person_t {
    string name;
    string email;
};

vector<person_t> roster = {
    {"Diana", "dnixon4@ivytech.edu"},
    {"Andy", "andy@ivytech.edu"},
    {"Beth", "beth@ivytech.edu"},
    {"Henry", "henry@ivytech.edu"},
    {"Lily", "lili@ivytech.edu"},
    {"Trevor", "tpierce42@ivytech.edu"}
};

enum class Permissions: char {
    student='S',
    faculty='F',
    staff='A'
};

// This class will be used to store information about a user that logs in
class User {
    private:
        string _name, _password;
        Permissions _permissions; // This will tell if the user is a teacher or student
        string _grades; // This will store five grades, if the user is a student
    public:
        // Getter and setter prototypes
        void setName(string name);
        string getName();
        void setPassword(string password);
        string getPassword();
        void setPermissions(char permissions);
        Permissions getPermissions();
        void setGrades(string grades);
        string getGrades();
};

void User::setName(string name) {
    _name = name;
}

string User::getName() {
    return _name;
}

void User::setPassword(string password) {
    _password = password;
}

string User::getPassword() {
    return _password;
}

void User::setPermissions(char permissions) {
    if (permissions == 'S') {
        _permissions = Permissions::student;
    } 
    else if (permissions == 'F') {
        _permissions = Permissions::faculty;
    }
    else if (permissions == 'A') {
        _permissions = Permissions::staff;
    } else {
        cerr << "Invalid permissions set" << endl;
        cerr << "Current permissions set to: " << permissions << endl;
    }
}

Permissions User::getPermissions() {
    return _permissions;
}

void User::setGrades(string grades) {
    _grades = grades;
}

string User::getGrades() {
    return _grades;
}


// Main function prototypes
void updateUserInfo(User &, string, int);
bool checkPassword(User &, string);
void viewRoster();
void viewGrades(User &);
void sendEmail(User &);

int main() {
    // Time. The method in the book always gave me random results for some reason, but I found this method online and it always works perfectly due to time(0);
    time_t now = time(0);
    tm *localtm = localtime(&now);

    User currentUser; // The instance of the user class
    fstream userFile, logFile; // The files used for the program
    string input, userName, fileName, userPassword;
    bool logout = false; // How to determine if the user wants to exit the program
    int fileLine = 1, menuChoice;

    cout << "Hello! What is your name: ";
    cin >> userName;

    fileName = userName + ".txt";
    userFile.open(fileName, ios::in); // Opens the user's data file for reading
    logFile.open("log.txt", ios::app); // Opens the log file to append new data to the end of the current file

    if (userFile) {
        getline(userFile, input); // Gets the first line of the user's data file first

        while (userFile) {
            updateUserInfo(currentUser, input, fileLine); // Calls a function that updates the User class instance with the data in the user file, line by line
            getline(userFile, input);
            fileLine++;
        }

        cout << "Please enter your password: ";
        cin >> userPassword;

        if (checkPassword(currentUser, userPassword)) {
            while (!logout) { // If the user hasn't pressed 4
                system("CLS"); // This clears the screen
                cout << "1. View Class Roster\n";
                cout << "2. View Your Grades\n";
                cout << "3. Send Email\n";
                cout << "4. Exit\n";

                cin >> menuChoice;
                system("CLS");

                switch (menuChoice) {
                    case 1: viewRoster(); // Calls a function to allow the user to view the class roster
                        logFile << currentUser.getName() << " Action: " << menuChoice << " Time/Date: " << asctime(localtm) << endl; // This writes to the log the user, their action, and the time/date
                        break;
                    case 2: viewGrades(currentUser); // Allows students to view their grades
                        logFile << currentUser.getName() << " Action: " << menuChoice << " Time/Date: " << asctime(localtm) << endl;
                        break;
                    case 3: sendEmail(currentUser); // Allows users to feel like they're sending an email
                         logFile << currentUser.getName() << " Action: " << menuChoice << " Time/Date: " << asctime(localtm) << endl;
                        break;
                    case 4: logout = true;
                        userFile.close();
                        logFile.close();
                        break;
                    default: break;
                }
            }
        } else {
            cerr << "The password that you entered was incorrect and now the program will close";
        }
    } else {
        cerr << "Oh no! It looks like you do not have an account in our database!\n";
        cerr << "Please contact your administrator if you think that this is an error";
    }


    return EXIT_SUCCESS;
}

void updateUserInfo(User &currentUser, string input, int fileLine) {
    switch (fileLine) {
        case 1: currentUser.setName(input);
            break;
        case 2: currentUser.setPassword(input);
            break;
        case 3: currentUser.setPermissions(input[0]);
            break;
        case 4: currentUser.setGrades(input);
            break;
    }
}

// This function checks to see if the user entered the password matching the one stored in the data file. I know, not safe, but this is what I did. I should have looked into hashing the passwords
bool checkPassword(User &currentUser, string userPassword) {
    return currentUser.getPassword() == userPassword;
}

// This function displays the names and emails of people in the class
void viewRoster() {
    for (person_t person : roster) {
        cout << "Name: " << person.name;
        cout << " | Email: " << person.email;
        cout << endl;
    }
    cout << endl;
    system("pause"); // This allows for the screen to pause until the user presses a key. I love it!
}

// This function allows the user to view their grades if they're a student. If a teacher, then they are told they cannot view their grades
void viewGrades(User &currentUser) {
    if (currentUser.getPermissions() == Permissions::student) {
        string grades = currentUser.getGrades();

        // This whole block goes character by character and looks for $ delimiters that I placed between values in the string, then prints a new line
        // and moves onto the next iteration. This is because I had a very hard time get private class arrays to work right and I got this to work
        string currentChar;

        for (char grade : grades) {
            currentChar = grade;

            if (currentChar == "$") { // I put $'s to separate values in the string
                cout << endl;
                continue; // This skips to the next iteration of the loop
            } else {
                cout << currentChar; // This prints out the current character at the current index in the string
            }
        }
    } else {
        cerr << "Only students can view grades, since only they have assignments";
    }
    cout << endl;
    system("pause");
}

void sendEmail(User &currentUser) {
    cin.ignore(); // You have to use this to ignore the previous \n that might be in the input buffer, otherwise the program skips asking for the email and asks for the recipient
    string email, receiver;

    cout << "Please write an email below\n";
    getline(cin, email);

    cout << "Who would like to send the email to?\n";
    getline(cin, receiver);

    // The following block is a linear search to see if the program can find the user that you entered
    bool found = false;

    for (person_t person : roster) {
        if (person.name == receiver) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Email has been sent from " << currentUser.getName() << " to " << receiver;
    } else {
        cerr << "Sorry, we could not find " << receiver << " in our database";
    }
    cout << endl;
    system("pause");
}

