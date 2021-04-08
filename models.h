#pragma once
#include <map>
#include <string>
#include <vector>

namespace Models {
    enum class Permissions: char {
        student='S',
        faculty='F',
        staff='A'
    };

    struct person_t {
        std::string name;
        std::string email;
    };

    struct user_data_t {
        std::string name;
        std::string password;
        char permissions;
        std::map<std::string, int> grades;
    };

    class User {
        private:
            std::string _name, _password;
            Permissions _permissions;
        public:
            void setName(std::string name) {
                this->_name = name;
            }
            std::string getName() {
                return this->_name;
            }
            void setPassword(std::string password) {
                this->_password = password;
            }
            std::string getPassword()  {
                return this->_password;
            }
            void setPermissions(char permissions) {
                if (permissions == 'S') {
                    this->_permissions = Permissions::student;
                } 
                else if (permissions == 'F') {
                    this->_permissions = Permissions::faculty;
                }
                else if (permissions == 'A') {
                    this->_permissions = Permissions::staff;
                } else {
                    std::cerr << "Invalid permissions set" << std::endl;
                    std::cerr << "Current permissions set to: " << permissions << std::endl;
                    std::exit(EXIT_FAILURE);
                }
            }
            Permissions getPermissions() {
                return this->_permissions;
            }
    };

    class Student : User {
        private:
            std::string _grades;
        public:
            void setGrades(std::string grades) {
                this->_grades = grades;
            }
            std::string getGrades() {
                return this->_grades;
            }
    };

    class Teacher : User {};
};