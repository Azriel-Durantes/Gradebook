#ifndef GRADEBOOK_HPP
#define GRADEBOOK_HPP

#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

inline vector<double> collectValidatedGrades() {
    vector<double> grades;
    string input;

    while (true) {
        cout << "Enter a grade (0-100) or 'done' to finish: ";
        if (!getline(cin, input)) {
            throw runtime_error("Input stream closed unexpectedly.");
        }

        if (input == "done" || input == "DONE") {
            if (!grades.empty()) {
                return grades;
            }
            cout << "Error: Enter at least one valid grade before finishing.\n";
            continue;
        }

        stringstream ss(input);
        double grade;
        char extra;
        if (ss >> grade && !(ss >> extra)) {
            if (grade >= 0.0 && grade <= 100.0) {
                grades.push_back(grade);
            } else {
                cout << "Error: Grade must be between 0 and 100.\n";
            }
        } else {
            cout << "Error: Invalid input. Enter a numeric value or 'done'.\n";
        }
    }
}

inline double calculateAverage(const vector<double>& grades) {
    if (grades.empty()) {
        throw invalid_argument("Cannot calculate average of an empty grade list.");
    }
    double sum = accumulate(grades.begin(), grades.end(), 0.0);
    return sum / static_cast<double>(grades.size());
}

inline char determineLetterGrade(double average) {
    if (average >= 90.0) return 'A';
    if (average >= 80.0) return 'B';
    if (average >= 70.0) return 'C';
    if (average >= 60.0) return 'D';
    return 'F';
}

inline string determinePassFail(double average, double passingThreshold = 60.0) {
    return (average >= passingThreshold) ? "Pass" : "Fail";
}

inline void displaySummary(
    const string& studentName,
    const vector<double>& grades,
    double average,
    char letterGrade,
    const string& status
) {
    cout << "\n" << string(40, '=') << "\n";
    cout << "Student Name : " << studentName << "\n";
    cout << "Grades       : [";
    cout << fixed << setprecision(2);
    for (size_t i = 0; i < grades.size(); ++i) {
        cout << grades[i] << (i + 1 < grades.size() ? ", " : "");
    }
    cout << "]\n";
    cout << "Average      : " << average << "\n";
    cout << "Letter Grade : " << letterGrade << "\n";
    cout << "Status       : " << status << "\n";
    cout << string(40, '=') << "\n\n";
}

#endif
