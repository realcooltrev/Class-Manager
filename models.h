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

    // This class will be used to store information about a user that logs in
    class User {
        private:
            std::string _name, _password;
            Permissions _permissions; // This will tell if the user is a teacher or student
            std::string _grades; // This will store five grades, if the user is a student
        public:
            // Getter and setter prototypes
            void setName(std::string name) {
                _name = name;
            }
            std::string getName() {
                return _name;
            }
            void setPassword(std::string password) {
                _password = password;
            }
            std::string getPassword()  {
                return _password;
            }
            void setPermissions(char permissions) {
                if (permissions == 'S') {
                    _permissions = Permissions::student;
                } 
                else if (permissions == 'F') {
                    _permissions = Permissions::faculty;
                }
                else if (permissions == 'A') {
                    _permissions = Permissions::staff;
                } else {
                    std::cerr << "Invalid permissions set" << std::endl;
                    std::cerr << "Current permissions set to: " << permissions << std::endl;
                }
            }
            Permissions getPermissions() {
                return _permissions;
            }
            void setGrades(std::string grades) {
                _grades = grades;
            }
            std::string User::getGrades() {
                return _grades;
            }
    };
};