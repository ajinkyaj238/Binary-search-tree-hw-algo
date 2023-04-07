/*******************************************************************************
* Homework 6
* author          :Ajinkya Joshi
* Date            :April 5, 2023
* File name       :Student.cpp
* Purpose         :Contains the method implementations for the Student class.
 *******************************************************************************/

#include "Student.h"

// Constructor for the Student class that initializes the member variables with the given parameters.
Student::Student(int id, string name, string major, int year) {
    IDNumber = id;
    this->name = name;
    this->major = major;
    this->year = year;
}

// Getter function that returns the ID number of the student.
int Student::getIDNumber() {
    return IDNumber;
}

// Setter function that sets the ID number of the student.
void Student::setIDNumber(int id) {
    IDNumber = id;
}

// Getter function that returns the name of the student.
string Student::getName() {
    return name;
}

// Setter function that sets the name of the student.
void Student::setName(string name) {
    this->name = name;
}

// Getter function that returns the major of the student.
string Student::getMajor() {
    return major;
}

// Setter function that sets the major of the student.
void Student::setMajor(string major) {
    this->major = major;
}

// Getter function that returns the current year of the student.
int Student::getYear() {
    return year;
}

// Setter function that sets the current year of the student.
void Student::setYear(int year) {
    this->year = year;
}

// Comparison operator function that checks if two student objects are equal based on their ID numbers.
bool operator == (const Student& lhs, const Student& rhs) {
    return lhs.IDNumber == rhs.IDNumber;
}

// Comparison operator function that checks if the ID number of the first student object is greater than the second.
bool operator > (const Student& lhs, const Student& rhs) {
    return lhs.IDNumber > rhs.IDNumber;
}

// Comparison operator function that checks if the ID number of the first student object is less than the second.
bool operator < (const Student& lhs, const Student& rhs) {
    return lhs.IDNumber < rhs.IDNumber;
}
