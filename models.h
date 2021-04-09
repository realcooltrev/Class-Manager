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

    struct assignment_t {
        std::string name;
        int score;
    };

    struct user_data_t {
        std::string username;
        std::string password;
        Permissions permissions;
        std::vector<assignment_t> grades;
    };

    class User {
        private:
            std::vector<assignment_t> _grades;
            Permissions _permissions;
            std::string _username;
        public:
            User() {}
            User(std::string username, Permissions permissions, std::vector<assignment_t> grades) {
                this->_username = username;
                this->_permissions = permissions;

                if (this->_permissions == Permissions::student) {
                    this->_grades = grades;
                }
            }

            void add_grade(assignment_t assignment) {
                this->_grades.push_back(assignment);
            }

            std::vector<assignment_t> get_grades() {
                return this->_grades;
            }

            Permissions get_permissions() {
                return this->_permissions;
            }

            std::string get_username() {
                return this->_username;
            }

            void update_permissions(Permissions permissions) {
                this->_permissions = permissions;
            }
    };
};
