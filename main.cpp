/**************************************************************************
* Homework 6
* author          :Ajinkya Joshi
* Date            :April 5, 2023
* File name       :main.cpp
* Purpose         :Contains the main menu options to add, remove, etc.
 **************************************************************************/

// All libraries and header files used in the program
#include <iostream>
#include "Student.h"
#include "BinarySearchTree.h"
#include <fstream>
#include <iomanip>
using namespace std;

/**
 * prints the student information
 * @param stu
 * @return void
 */
void print(Student& stu)
{
    cout << setw(5) << stu.getIDNumber();
    cout << setw(10) << stu.getName();
    cout << setw(10) << stu.getMajor();
    cout << setw(10) << stu.getYear() << endl;
}

/**
 * main
 * main function for the program
 */
int main()
{
    BinarySearchTree<Student>* stuTreePtr = new BinarySearchTree<Student>(); // create a new tree

    // Student Variables defined only once
    int id;
    string name;
    string major;
    int year;
    int option; // menu option

    // Display Menu
    cout<< "Menu Options:" << endl;
    cout<< "+--------------------------+"<< endl;
    cout<< "| [0] DISPLAY MENU" << endl;
    cout<< "| [1] NUMBER OF RECORDS" << endl;
    cout<< "| [2] ADD RECORD" << endl;
    cout<< "| [3] PRINT RECORDS" << endl;
    cout<< "| [4] RETRIEVE BY IDNO" << endl;
    cout<< "| [5] REMOVE RECORD" << endl;
    cout<< "| [6] REMOVE ALL RECORDS" << endl;
    cout<< "| [7] READ RECORDS FROM FILE" << endl;
    cout<< "| [8] TERMINATE PROGRAM" << endl;
    cout<< "+--------------------------+" << endl;

    // Menu
    while(option != 8)
    {
        cout<< "===> Enter an integer menu option[0-8]:";
        cin >> option;

        // Option displays menu again by looping
        if (option == 0){
            // Display Menu
            cout<< "Menu Options:" << endl;
            cout<< "+--------------------------+"<< endl;
            cout<< "| [0] DISPLAY MENU" << endl;
            cout<< "| [1] NUMBER OF RECORDS" << endl;
            cout<< "| [2] ADD RECORD" << endl;
            cout<< "| [3] PRINT RECORDS" << endl;
            cout<< "| [4] RETRIEVE BY IDNO" << endl;
            cout<< "| [5] REMOVE RECORD" << endl;
            cout<< "| [6] REMOVE ALL RECORDS" << endl;
            cout<< "| [7] READ RECORDS FROM FILE" << endl;
            cout<< "| [8] TERMINATE PROGRAM" << endl;
            cout<< "+--------------------------+" << endl;
        }

        // Prints the number of record in the tree
        else if(option == 1)
        {
            if (stuTreePtr->isEmpty())
                cout<< "The List is empty. No records found!" << endl;
            else
                cout<< "The List contains " << stuTreePtr->getNumberOfNodes() << " records" << endl;
        }

        // Adds a new record to the tree
        else if(option == 2)
        {
            cout<< "ID: ";
            cin >> id;
            cout<< "Name: ";
            cin >> name;
            cout<< "Major: ";
            cin >> major;
            cout<< "Year: ";
            cin >> year;
            Student* stuPtr = new Student(id, name, major, year);
            stuTreePtr->add(*stuPtr);
            cout << "One record has been added to the list." << endl;
        }

        // Prints all the records in the tree
        else if(option == 3)
        {
            if (stuTreePtr->isEmpty())
            {
                cout << "List is empty. Nothing to print..." << endl;
            }
            else
            {
                cout<< "  ID#      Name     Major      Year" << endl;
                stuTreePtr->inorderTraverse(print);
                cout<< endl;
            }

        }

        // Retrieves a record from the tree
        else if(option == 4)
        {
            if(stuTreePtr->isEmpty())
            {
                cout << "Unable to perform this action on an empty list." << endl;
            }
            else
            {
                int idno;
                cout << "Enter student's ID for record to search: ";
                cin >> idno;
                try {
                    Student *stuPtr2 = new Student(idno);
                    stuTreePtr->getEntry(*stuPtr2);
                    Student stuPtr3 = stuTreePtr->getEntry(*stuPtr2);
                    cout << "  ID#      Name     Major      Year" << endl;
                    print(stuPtr3);
                }
                catch (NotFoundException) {
                    cout << "Student not found in records...!" << endl;
                }
                catch (PrecondViolatedExcep) {
                    cout << "Student not found in records...!" << endl;
                }
            }

        }

        // Removes a record from the tree
        else if(option == 5)
        {
            if (stuTreePtr->isEmpty())
            {
                cout << "Unable to perform this action on an empty list." << endl;
            }
            else
            {
                int idno2;
                bool remove;
                cout<< "Enter ID Number: ";
                cin >> idno2;
                Student* stuPtr3 = new Student(idno2);
                stuTreePtr->remove(*stuPtr3);

                try {
                    Student* stuPtr3 = new Student(idno2);
                    stuTreePtr->remove(*stuPtr3);
                }
                catch(NotFoundException)
                {
                    cout << "Student not found in records...!" << endl;
                }
                catch(PrecondViolatedExcep)
                {
                    cout << "Student not found in records...!" << endl;
                }
            }

        }

        // Removes all records from the tree
        else if(option == 6)
        {
            if (stuTreePtr->isEmpty())
            {
                cout << "Unable to perform this action on an empty list." << endl;
            }
            else
            {
                cout << "All records have been deleted from the list." << endl;
                stuTreePtr->clear();
            }
        }

        // Reads records from a file
        else if(option == 7)
        {
            string fileName = "StudentRecords.txt";
            ifstream inFile(fileName.c_str());
            if (!inFile)
            {
                cout << "File could not be opened." << endl;
            }
            else
            {
                cout << "Reading records from file...." << endl;
                while(getline(inFile, fileName))
                {
                    inFile >> id;
                    inFile >> name;
                    inFile >> major;
                    inFile >> year;
                    Student* stuPtr = new Student(id, name, major, year);
                    stuTreePtr->add(*stuPtr);
                }
                inFile.close();
            }

        }

        // Terminates the program
        else if(option == 8)
        {
            cout<< "Processing completed. Terminating........" << endl;
            break;
        }

        // Invalid option
        else
        {
            cout<< "Invalid option. Please try again." << endl;
        }

    }


    return 0;
}
