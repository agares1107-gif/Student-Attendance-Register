# Student Attendance Register

A beginner-friendly, menu-driven **Student Attendance Register** developed using **C++**. The application helps a teacher register students, record daily attendance, search student details, and view attendance summaries.

## Project Information

- **Project Name:** Student Attendance Register
- **Language:** C++
- **Application Type:** Console-based application
- **Standard:** C++11 or later (C++17 recommended)
- **Storage:** Local text files

## Objectives

1. Maintain student information in one place.
2. Record each student's daily attendance as Present or Absent.
3. View attendance for a selected date.
4. Calculate each student's attendance percentage.
5. Save records locally so they are available the next time the program runs.

## Features

| Feature | Description |
|---|---|
| Add Student | Register a student using an ID, name, and class/section. |
| View Students | Display all registered students. |
| Mark Attendance | Record Present (P) or Absent (A) for a date. |
| View Attendance | Display attendance records for a selected date. |
| Attendance Report | Show present days, recorded days, and attendance percentage. |
| Search Student | Find a student using their ID. |
| File Storage | Store student and attendance data in text files. |

## Technologies Used

- C++
- Standard Template Library (STL)
- File handling (`ifstream` and `ofstream`)
- Structures and functions
- Vectors and string processing

## Project Structure

```text
Student-Attendance-Register/
├── main.cpp
├── students.txt
├── attendance.txt
├── README.md
└── screenshots/
    └── (add your application screenshots here)
```

## Requirements

- A C++ compiler such as GCC / MinGW or Clang
- A terminal or code editor such as Visual Studio Code, Code::Blocks, or an IDE with C++ support

## How to Compile and Run

### Windows (MinGW)

Open a terminal in the project folder and run:

```bash
g++ -std=c++17 main.cpp -o attendance
attendance.exe
```

### Linux / macOS

```bash
g++ -std=c++17 main.cpp -o attendance
./attendance
```

In Visual Studio Code, open the project folder, open the integrated terminal, and run the command for your operating system.

## How to Use

1. Run the compiled program.
2. Select **1** to add students. Enter a unique positive student ID, name, and class/section.
3. Select **2** to view registered students.
4. Select **3** to mark attendance. Enter the date in `YYYY-MM-DD` format, then enter `P` or `A` for each student.
5. Select **4** to view attendance for a date.
6. Select **5** to view attendance percentages.
7. Select **6** to search for a student by ID.
8. Select **7** to exit.

## Data Files

- `students.txt` stores student records in the format `ID|Name|Class`.
- `attendance.txt` stores attendance records in the format `Date|StudentID|P/A`.

The program creates or updates these files in its current working directory. Keep the files in the same folder as the program when running it to retain your records.

**Note:** This is a simple educational project. It uses local text files and does not include user login, cloud storage, or a database. The date is entered by the user; the program checks the format but does not verify the calendar date.

## Future Enhancements

- Add an edit/delete student option.
- Add an option to correct an attendance entry.
- Export reports to CSV.
- Add a graphical user interface.
- Add database support and user authentication.

## Conclusion

The Student Attendance Register demonstrates basic C++ programming concepts such as structures, functions, vectors, loops, conditional statements, and file handling. It provides a simple way to maintain student details and daily attendance records.

## Author

**Your Name**

> Replace this with your name before submitting the project.
