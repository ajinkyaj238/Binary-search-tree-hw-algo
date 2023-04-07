#ifndef _STUDENT
#define _STUDENT

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/**
 * Class Student
*/
class Student {
private:
    int IDNumber;
    string name;
    string major;
    int year;

public:
    Student(int id = 0, string name = "", string major = "", int year = 0);
    // getters and setters
    int getIDNumber();             // returns IDNumber
    void setIDNumber(int year);    // sets the IDNumber
    string getName();              // returns Name
    void setName(string name);     // sets the name
    string getMajor();             // returns Major
    void setMajor(string major);   // sets the major
    int getYear();                 // returns Year
    void setYear(int year);        // set the year

    // Overload as friend functions
    // Comparison should be based on the IDNumber only assuming each
    // student has a unique ID. No need to compare the other fields.
    friend bool operator== (const Student& lhs, const Student& rhs);
    friend bool operator>  (const Student& lhs, const Student& rhs);
    friend bool operator<  (const Student& lhs, const Student& rhs);
};

#endif
