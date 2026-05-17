#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_SUBJECTS = 5;

struct Student {
    int id;
    string name;
    float marks[MAX_SUBJECTS];
    int subjectCount;
    float gpa;
};

// ─── Helper Functions ───────────────────────────────────────────────────────

float calculateGPA(float marks[], int count) {
    float total = 0;
    for (int i = 0; i < count; i++) {
        total += marks[i];
    }
    float avg = total / count;

    if (avg >= 90) return 4.0;
    else if (avg >= 85) return 3.7;
    else if (avg >= 80) return 3.3;
    else if (avg >= 75) return 3.0;
    else if (avg >= 70) return 2.7;
    else if (avg >= 65) return 2.3;
    else if (avg >= 60) return 2.0;
    else if (avg >= 55) return 1.7;
    else if (avg >= 50) return 1.0;
    else return 0.0;
}

string getGrade(float gpa) {
    if (gpa >= 4.0) return "A+";
    else if (gpa >= 3.7) return "A";
    else if (gpa >= 3.3) return "A-";
    else if (gpa >= 3.0) return "B+";
    else if (gpa >= 2.7) return "B";
    else if (gpa >= 2.3) return "B-";
    else if (gpa >= 2.0) return "C";
    else if (gpa >= 1.0) return "D";
    else return "F";
}

void printLine() {
    cout << string(55, '-') << endl;
}

// ─── Core Features ──────────────────────────────────────────────────────────

void addStudent(Student students[], int &count) {
    if (count >= MAX_STUDENTS) {
        cout << "\n[!] Student limit reached.\n";
        return;
    }

    Student s;
    s.id = count + 1;

    cout << "\n--- Add New Student ---\n";
    cin.ignore();
    cout << "Enter student name: ";
    getline(cin, s.name);

    cout << "How many subjects? (1-" << MAX_SUBJECTS << "): ";
    cin >> s.subjectCount;

    if (s.subjectCount < 1 || s.subjectCount > MAX_SUBJECTS) {
        cout << "[!] Invalid subject count.\n";
        return;
    }

    for (int i = 0; i < s.subjectCount; i++) {
        cout << "Enter marks for Subject " << i + 1 << " (0-100): ";
        cin >> s.marks[i];
        while (s.marks[i] < 0 || s.marks[i] > 100) {
            cout << "[!] Invalid marks. Enter again: ";
            cin >> s.marks[i];
        }
    }

    s.gpa = calculateGPA(s.marks, s.subjectCount);
    students[count++] = s;

    cout << "\n[✓] Student added successfully! GPA: " << fixed << setprecision(2) << s.gpa << " (" << getGrade(s.gpa) << ")\n";
}

void viewAllStudents(Student students[], int count) {
    if (count == 0) {
        cout << "\n[!] No students found.\n";
        return;
    }

    cout << "\n--- All Students ---\n";
    printLine();
    cout << left << setw(5) << "ID"
         << setw(20) << "Name"
         << setw(10) << "GPA"
         << setw(8)  << "Grade" << endl;
    printLine();

    for (int i = 0; i < count; i++) {
        cout << left << setw(5) << students[i].id
             << setw(20) << students[i].name
             << setw(10) << fixed << setprecision(2) << students[i].gpa
             << setw(8)  << getGrade(students[i].gpa) << endl;
    }
    printLine();
}

void searchStudent(Student students[], int count) {
    if (count == 0) {
        cout << "\n[!] No students found.\n";
        return;
    }

    cout << "\nEnter student name to search: ";
    cin.ignore();
    string name;
    getline(cin, name);

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (students[i].name == name) {
            found = true;
            cout << "\n--- Student Report ---\n";
            printLine();
            cout << "ID     : " << students[i].id << endl;
            cout << "Name   : " << students[i].name << endl;
            for (int j = 0; j < students[i].subjectCount; j++) {
                cout << "Subject " << j + 1 << ": " << students[i].marks[j] << endl;
            }
            cout << "GPA    : " << fixed << setprecision(2) << students[i].gpa << endl;
            cout << "Grade  : " << getGrade(students[i].gpa) << endl;
            printLine();
        }
    }

    if (!found) cout << "\n[!] Student not found.\n";
}

void generateReport(Student students[], int count) {
    if (count == 0) {
        cout << "\n[!] No data to report.\n";
        return;
    }

    float totalGPA = 0;
    float highest = students[0].gpa;
    float lowest  = students[0].gpa;
    string topStudent = students[0].name;

    for (int i = 0; i < count; i++) {
        totalGPA += students[i].gpa;
        if (students[i].gpa > highest) {
            highest = students[i].gpa;
            topStudent = students[i].name;
        }
        if (students[i].gpa < lowest) {
            lowest = students[i].gpa;
        }
    }

    cout << "\n===== Grade Report =====\n";
    printLine();
    cout << "Total Students : " << count << endl;
    cout << "Average GPA    : " << fixed << setprecision(2) << totalGPA / count << endl;
    cout << "Highest GPA    : " << highest << " (" << topStudent << ")" << endl;
    cout << "Lowest GPA     : " << lowest << endl;
    printLine();
}

void deleteStudent(Student students[], int &count) {
    if (count == 0) {
        cout << "\n[!] No students to delete.\n";
        return;
    }

    cout << "\nEnter student ID to delete: ";
    int id;
    cin >> id;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            found = true;
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            cout << "[✓] Student deleted successfully.\n";
            break;
        }
    }

    if (!found) cout << "[!] Student ID not found.\n";
}

// ─── Main Menu ───────────────────────────────────────────────────────────────

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    cout << "====================================\n";
    cout << "  Student Grade Management System  \n";
    cout << "====================================\n";

    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Generate Class Report\n";
        cout << "5. Delete Student\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(students, count); break;
            case 2: viewAllStudents(students, count); break;
            case 3: searchStudent(students, count); break;
            case 4: generateReport(students, count); break;
            case 5: deleteStudent(students, count); break;
            case 0: cout << "\nGoodbye!\n"; break;
            default: cout << "[!] Invalid option. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
