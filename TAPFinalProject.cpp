/* Author: Trevor Pierce
 * Date of last edit: 12/11/17
 *
 * Final Project
 * Description: This file will allow a user to log in and then perform various
 * course activities, like viewing grades, sending fake emails, and viewing the class roster.
 * The program will also write all of the user's activities to a log file for
 * security purposes
 */
 #include <ctime>
 #include <fstream>
 #include <iostream>
 #include <stdlib.h>
 #include <string>

 using namespace std;

 // The fake class roster and their fake emails, set globally
 const int NUM_PEOPLE = 6;
 const int NUM_PEOPLE_DATA = 2;
 string roster[NUM_PEOPLE][NUM_PEOPLE_DATA] = {{"Diana", "dnixon4@ivytech.edu"},
                         {"Andy", "andy@ivytech.edu"},
                         {"Beth", "beth@ivytech.edu"},
                         {"Henry", "henry@ivytech.edu"},
                         {"Lily", "lili@ivytech.edu"},
                         {"Trevor", "tpierce42@ivytech.edu"}};

// This class will be used to store information about a user that logs in
 class User {
 private:
    string name, password;
    string permissions; // This will tell if the user is a teacher or student
    string grades; // This will store five grades, if the user is a student
 public:
    // Getter and setter prototypes
    void setName(string in_name);
    string getName();
    void setPassword(string in_pass);
    string getPassword();
    void setPermissions(string in_permis);
    string getPermissions();
    void setGrades(string in_grades);
    string getGrades();
};

void User::setName(string in_name) {
    name = in_name;
}

string User::getName() {
    return name;
}

void User::setPassword(string in_pass) {
    password = in_pass;
}

string User::getPassword() {
    return password;
}

void User::setPermissions(string in_permis) {
    permissions = in_permis;
}

string User::getPermissions() {
    return permissions;
}

void User::setGrades(string in_grades) {
    grades = in_grades;
}

string User::getGrades() {
    return grades;
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

        while (userFile) { // Until the end of the file
            updateUserInfo(currentUser, input, fileLine); // Calls a function that updates the User class instance with the data in the user file, line by line
            getline(userFile, input);
            fileLine++;
        }

        cout << "Please enter your password: ";
        cin >> userPassword;

        if (checkPassword(currentUser, userPassword)) { // This checks is the password the user entered is correct. The password is line 2 of your user data file
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
            cout << "The password that you entered was incorrect and now the program will close";
        }
    } else {
        cout << "Oh no! It looks like you do not have an account in our database!\n";
        cout << "Please contact your administrator if you think that this is an error";
    }


    return 0;
}

void updateUserInfo(User &currentUser, string input, int fileLine) {
    switch (fileLine) {
        case 1: currentUser.setName(input);
            break;
        case 2: currentUser.setPassword(input);
            break;
        case 3: currentUser.setPermissions(input);
            break;
        case 4: currentUser.setGrades(input);
            break;
    }
}

// This function checks to see if the user entered the password matching the one stored in the data file. I know, not safe, but this is what I did. I should have looked into hashing the passwords
bool checkPassword(User &currentUser, string userPassword) {
    if (currentUser.getPassword() == userPassword) {
        return true;
    } else {
        return false;
    }
}

// This function displays the names and emails of people in the class
void viewRoster() {
    for (int i = 0; i < NUM_PEOPLE; i++) {
        for (int j = 0; j < NUM_PEOPLE_DATA; j++) {
            if (j == 0) {
                cout << "Name: " << roster[i][j];
            } else {
                cout << " | Email: " << roster[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
    system("pause"); // This allows for the screen to pause until the user presses a key. I love it!
}

// This function allows the user to view their grades if they're a student. If a teacher, then they are told they cannot view their grades
void viewGrades(User &currentUser) {
    if (currentUser.getPermissions() == "S") { // S for student
        string grades = currentUser.getGrades();

        // This whole block goes character by character and looks for $ delimiters that I placed between values in the string, then prints a new line
        // and moves onto the next iteration. This is because I had a very hard time get private class arrays to work right and I got this to work
        string currentChar;

        for (int i = 0; i < grades.length(); i++) {
            currentChar = grades[i];

            if (currentChar == "$") { // I put $'s to separate values in the string
                cout << endl;
                continue; // This skips to the next iteration of the loop
            } else {
                cout << currentChar; // This prints out the current character at the current index in the string
            }
        }
    } else {
        cout << "Teachers cannot view grades since they do not have assignments";
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
    int index = 0;
    int position = -1;
    bool found = false;

    while (index < 6 && !found) {
        if (roster[index][0] == receiver) {
            found = true;
            position = index;
        }
        index++;
    }

    if (found) {
        cout << "Email has been sent from " << currentUser.getName() << " to " << roster[position][1];
    } else {
        cout << "Sorry, we could not find " << receiver << " in our database";
    }
    cout << endl;
    system("pause");
}

