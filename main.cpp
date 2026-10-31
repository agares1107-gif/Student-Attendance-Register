#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

struct Student {
    int id{};
    string name;
    string className;
};

struct Attendance {
    string date;   // YYYY-MM-DD
    int studentId{};
    char status{}; // P or A
};

const string STUDENT_FILE = "students.txt";
const string ATTENDANCE_FILE = "attendance.txt";

vector<Student> students;
vector<Attendance> attendanceRecords;

string trim(const string& value) {
    const size_t first = value.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    const size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readLine(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return trim(value);
}

bool validDateFormat(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;
    for (size_t i = 0; i < date.size(); ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(static_cast<unsigned char>(date[i]))) return false;
    }
    return true;
}

Student* findStudent(int id) {
    for (auto& student : students) {
        if (student.id == id) return &student;
    }
    return nullptr;
}

void loadStudents() {
    students.clear();
    ifstream file(STUDENT_FILE);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idText, name, className;
        if (getline(ss, idText, '|') &&
            getline(ss, name, '|') &&
            getline(ss, className)) {
            try {
                students.push_back({stoi(idText), name, className});
            } catch (...) {
                // Ignore malformed rows.
            }
        }
    }
}

void saveStudents() {
    ofstream file(STUDENT_FILE);
    for (const auto& student : students) {
        file << student.id << '|' << student.name << '|'
             << student.className << '\n';
    }
}

void loadAttendance() {
    attendanceRecords.clear();
    ifstream file(ATTENDANCE_FILE);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string date, idText, statusText;
        if (getline(ss, date, '|') &&
            getline(ss, idText, '|') &&
            getline(ss, statusText)) {
            try {
                if (!statusText.empty()) {
                    attendanceRecords.push_back(
                        {date, stoi(idText), static_cast<char>(toupper(statusText[0]))}
                    );
                }
            } catch (...) {
                // Ignore malformed rows.
            }
        }
    }
}

void saveAttendance() {
    ofstream file(ATTENDANCE_FILE);
    for (const auto& record : attendanceRecords) {
        file << record.date << '|' << record.studentId << '|'
             << record.status << '\n';
    }
}

void addStudent() {
    cout << "\n--- Add Student ---\n";
    const int id = readInt("Enter student ID: ");
    if (id <= 0) {
        cout << "Student ID must be positive.\n";
        return;
    }
    if (findStudent(id)) {
        cout << "A student with this ID already exists.\n";
        return;
    }

    const string name = readLine("Enter student name: ");
    const string className = readLine("Enter class/section: ");
    if (name.empty() || className.empty() ||
        name.find('|') != string::npos || className.find('|') != string::npos) {
        cout << "Name and class are required; the | character is not allowed.\n";
        return;
    }

    students.push_back({id, name, className});
    saveStudents();
    cout << "Student added successfully.\n";
}

void viewStudents() {
    cout << "\n--- Student List ---\n";
    if (students.empty()) {
        cout << "No students registered yet.\n";
        return;
    }

    cout << left << setw(12) << "ID" << setw(28) << "Name" << "Class\n";
    cout << string(55, '-') << '\n';
    for (const auto& student : students) {
        cout << left << setw(12) << student.id
             << setw(28) << student.name << student.className << '\n';
    }
}

bool hasAttendance(const string& date, int studentId) {
    return any_of(attendanceRecords.begin(), attendanceRecords.end(),
        [&](const Attendance& record) {
            return record.date == date && record.studentId == studentId;
        });
}

void markAttendance() {
    cout << "\n--- Mark Attendance ---\n";
    if (students.empty()) {
        cout << "Add students before marking attendance.\n";
        return;
    }

    const string date = readLine("Enter date (YYYY-MM-DD): ");
    if (!validDateFormat(date)) {
        cout << "Invalid date format. Use YYYY-MM-DD.\n";
        return;
    }

    int added = 0;
    for (const auto& student : students) {
        if (hasAttendance(date, student.id)) {
            cout << student.name << " (ID " << student.id
                 << "): attendance already exists for this date; skipped.\n";
            continue;
        }

        cout << student.name << " (ID " << student.id << ") - "
             << "Present (P) / Absent (A): ";
        char status;
        cin >> status;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        status = static_cast<char>(toupper(static_cast<unsigned char>(status)));

        while (status != 'P' && status != 'A') {
            cout << "Enter P for Present or A for Absent: ";
            cin >> status;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            status = static_cast<char>(toupper(static_cast<unsigned char>(status)));
        }

        attendanceRecords.push_back({date, student.id, status});
        ++added;
    }

    saveAttendance();
    cout << added << " attendance record(s) saved for " << date << ".\n";
}

void viewAttendanceByDate() {
    cout << "\n--- View Attendance ---\n";
    const string date = readLine("Enter date (YYYY-MM-DD): ");
    if (!validDateFormat(date)) {
        cout << "Invalid date format. Use YYYY-MM-DD.\n";
        return;
    }

    bool found = false;
    cout << left << setw(12) << "ID" << setw(28) << "Name"
         << "Status\n";
    cout << string(50, '-') << '\n';

    for (const auto& record : attendanceRecords) {
        if (record.date == date) {
            const Student* student = nullptr;
            for (const auto& item : students) {
                if (item.id == record.studentId) {
                    student = &item;
                    break;
                }
            }
            cout << left << setw(12) << record.studentId
                 << setw(28) << (student ? student->name : "Unknown")
                 << (record.status == 'P' ? "Present" : "Absent") << '\n';
            found = true;
        }
    }

    if (!found) cout << "No attendance records found for this date.\n";
}

void searchStudent() {
    cout << "\n--- Search Student ---\n";
    const int id = readInt("Enter student ID: ");
    const Student* student = findStudent(id);
    if (!student) {
        cout << "Student not found.\n";
        return;
    }

    cout << "ID: " << student->id << "\nName: " << student->name
         << "\nClass: " << student->className << '\n';
}

void attendanceReport() {
    cout << "\n--- Attendance Report ---\n";
    if (students.empty()) {
        cout << "No students registered yet.\n";
        return;
    }

    cout << left << setw(12) << "ID" << setw(25) << "Name"
         << setw(12) << "Present" << setw(12) << "Recorded"
         << "Percentage\n";
    cout << string(75, '-') << '\n';

    for (const auto& student : students) {
        int present = 0;
        int recorded = 0;
        for (const auto& record : attendanceRecords) {
            if (record.studentId == student.id) {
                ++recorded;
                if (record.status == 'P') ++present;
            }
        }

        const double percentage = recorded == 0
            ? 0.0
            : (static_cast<double>(present) / recorded) * 100.0;

        cout << left << setw(12) << student.id
             << setw(25) << student.name
             << setw(12) << present
             << setw(12) << recorded
             << fixed << setprecision(1) << percentage << "%\n";
    }
}

void showMenu() {
    cout << "\n========== STUDENT ATTENDANCE REGISTER ==========\n"
         << "1. Add Student\n"
         << "2. View All Students\n"
         << "3. Mark Attendance\n"
         << "4. View Attendance by Date\n"
         << "5. Attendance Report\n"
         << "6. Search Student\n"
         << "7. Exit\n"
         << "=================================================\n";
}

int main() {
    loadStudents();
    loadAttendance();

    cout << "Welcome to Student Attendance Register!\n";
    while (true) {
        showMenu();
        const int choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: markAttendance(); break;
            case 4: viewAttendanceByDate(); break;
            case 5: attendanceReport(); break;
            case 6: searchStudent(); break;
            case 7:
                saveStudents();
                saveAttendance();
                cout << "Thank you for using the Student Attendance Register.\n";
                return 0;
            default:
                cout << "Invalid choice. Please select 1 to 7.\n";
        }
    }
}
