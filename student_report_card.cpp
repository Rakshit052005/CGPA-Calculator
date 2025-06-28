#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Student {
    int rollNo;
    string name;
    string subjects[5];
    float marks[5];
    float cgpa;
};

vector<Student> students;

void calculateCGPA(Student &s) {
    float sum = 0;
    for (int i = 0; i < 5; ++i)
        sum += s.marks[i];
    s.cgpa = (sum / 5.0) / 10.0;  // Convert percentage to CGPA out of 10
}

void addStudent() {
    Student s;
    cout << "Enter Roll No: ";
    cin >> s.rollNo;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter names and marks for 5 subjects:\n";
    for (int i = 0; i < 5; ++i) {
        cout << "Subject " << (i + 1) << " Name: ";
        getline(cin, s.subjects[i]);
        cout << "Marks in " << s.subjects[i] << ": ";
        cin >> s.marks[i];
        cin.ignore();  // Ignore leftover newline
    }

    calculateCGPA(s);
    students.push_back(s);
}

void displayAll() {
    for (auto &s : students) {
        cout << "\nRoll No: " << s.rollNo
             << "\nName: " << s.name
             << "\nSubjects and Marks:\n";
        for (int i = 0; i < 5; ++i) {
            cout << "  " << s.subjects[i] << ": " << s.marks[i] << "\n";
        }
        cout << "CGPA (out of 10): " << fixed << setprecision(2) << s.cgpa << "\n";
    }
}

void saveToFile() {
    ofstream fout("students.txt");
    for (auto &s : students) {
        fout << s.rollNo << "\n" << s.name << "\n";
        for (int i = 0; i < 5; ++i)
            fout << s.subjects[i] << "\n";
        for (int i = 0; i < 5; ++i)
            fout << s.marks[i] << " ";
        fout << "\n" << s.cgpa << "\n";
    }
    fout.close();
}

void loadFromFile() {
    ifstream fin("students.txt");
    Student s;
    while (fin >> s.rollNo) {
        fin.ignore();
        getline(fin, s.name);
        for (int i = 0; i < 5; ++i)
            getline(fin, s.subjects[i]);
        for (int i = 0; i < 5; ++i)
            fin >> s.marks[i];
        fin >> s.cgpa;
        fin.ignore();
        students.push_back(s);
    }
    fin.close();
}

void editStudent(int roll) {
    for (auto &s : students) {
        if (s.rollNo == roll) {
            cout << "Editing student " << s.name << "\n";
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, s.name);
            cout << "Enter new subject names and marks:\n";
            for (int i = 0; i < 5; ++i) {
                cout << "Subject " << (i + 1) << " Name: ";
                getline(cin, s.subjects[i]);
                cout << "Marks in " << s.subjects[i] << ": ";
                cin >> s.marks[i];
                cin.ignore();
            }
            calculateCGPA(s);
            return;
        }
    }
    cout << "Student not found!\n";
}

void deleteStudent(int roll) {
    auto it = remove_if(students.begin(), students.end(), [roll](Student s) {
        return s.rollNo == roll;
    });
    if (it != students.end()) {
        students.erase(it, students.end());
        cout << "Student deleted.\n";
    } else {
        cout << "Student not found!\n";
    }
}

void sortStudentsByCGPA() {
    sort(students.begin(), students.end(), [](Student a, Student b) {
        return a.cgpa > b.cgpa;
    });
    cout << "Students sorted by CGPA.\n";
}

int main() {
    int choice, roll;
    loadFromFile();
    do {
        cout << "\n1. Add Student\n2. Display All\n3. Edit Student\n4. Delete Student\n5. Sort by CGPA\n6. Save & Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: cout << "Enter roll number to edit: "; cin >> roll; editStudent(roll); break;
            case 4: cout << "Enter roll number to delete: "; cin >> roll; deleteStudent(roll); break;
            case 5: sortStudentsByCGPA(); break;
            case 6: saveToFile(); cout << "Saved and exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);
    return 0;
}
