#include <iostream>
#include <fstream>
using namespace std;

class Admission {
    string studentName, studentID, course, admissionDate;
    string sID, sName;
    fstream file;

public:
    void addStudent();
    void displayStudents();
    void searchStudent();
    void updateStudent();
    void deleteStudent();
    void issueAdmissionLetter();
    void returnAdmissionLetter();
}obj;