#include "gradebook.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void processRecords() {
    while (true) {
        string studentName;
        while (true) {
            cout << "Enter student name: ";
            if (!getline(cin, studentName)) {
                return;
            }
            if (!studentName.empty()) {
                break;
            }
            cout << "Error: Student name cannot be empty.\n";
        }

        vector<double> grades = collectValidatedGrades();
        double average = calculateAverage(grades);
        char letterGrade = determineLetterGrade(average);
        string status = determinePassFail(average);

        displaySummary(studentName, grades, average, letterGrade, status);

        string choice;
        while (true) {
            cout << "Process another student record? (y/n): ";
            if (!getline(cin, choice)) {
                return;
            }
            if (choice == "y" || choice == "Y" || choice == "n" || choice == "N") {
                break;
            }
            cout << "Error: Please enter 'y' or 'n'.\n";
        }

        if (choice == "n" || choice == "N") {
            cout << "Exiting gradebook.\n";
            break;
        }
    }
}

int main() {
    processRecords();
    return 0;
}
