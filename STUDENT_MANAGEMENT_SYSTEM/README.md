# 🎓 Student Record Management System (C)

A complete **file-based Student Record Management System** built in C, implementing full CRUD operations with advanced features like safe deletion, data integrity checks, sorting, and extensible system design.

---

## 🚀 Overview

This project simulates a **mini database system** using binary file handling in C. It allows users to manage student records efficiently through a menu-driven interface.

The system is designed with a focus on:

* Data consistency
* Safe file operations
* Modular design
* Real-world system behavior

---

## ✨ Features

### 🔹 Core Features (Implemented)

* ➕ Add Student
* 📄 Display All Records
* 🔍 Search Student by Roll Number
* ✏️ Update Student Details
* ❌ Delete Student (with confirmation)

---

### 🔹 Data Integrity

* Prevents duplicate Roll Numbers
* Validates updates to avoid conflicts
* Maintains sorted records automatically

---

### 🔹 File Handling (Binary)

* Uses `fread`, `fwrite`, `fseek`, `rewind`
* Efficient storage using structures
* Persistent data storage

---

### 🔹 Sorting System

* Automatic sorting after:

  * Adding a student
  * Updating roll number
  * Deleting a record
* Implemented using in-memory sorting (Bubble Sort)

---

### 🔹 Safe Deletion System 🔥

* Uses **temporary file method**
* Deleted records are not lost — stored in:

  * `bin.txt` (Recycle Bin)

---

## 🚧 Advanced Features (Planned / Extended Version)

> These features are part of the extended version of the system.

* ♻️ Restore deleted records from recycle bin
* 🔍 Search by Name
* 📊 Student Statistics:

  * Total Students
  * Average CGPA
  * Highest & Lowest CGPA
* 🔁 Multi-field update mode
* 🔐 Optional secure deletion (passcode-based)
* 🎯 Improved UI formatting

---

## 🧠 Concepts Used

* Structures (`struct`)
* File Handling (Binary Mode)
* Dynamic Memory Allocation (`malloc`)
* Pointers
* Modular Programming
* Control Flow & Menu Systems
* Data Validation Techniques

---

## 📂 File Structure

```text
Data.txt     → Main database (binary file)
temp.txt     → Temporary file for safe updates/deletions
bin.txt      → Recycle bin (stores deleted records)
```

---

## ⚙️ How It Works

### 🔹 Add Operation

* Takes user input
* Checks for duplicate roll numbers
* Writes to file
* Sorts data

---

### 🔹 Delete Operation

1. Read original file
2. Copy all records except selected one → temp file
3. Store deleted record → bin file
4. Replace original file

---

### 🔹 Update Operation

* Searches record
* Uses `fseek()` to overwrite data in-place
* Validates duplicate roll number changes

---

## ▶️ How to Run

### Compile:

```bash
gcc student_management.c -o app
```

### Run:

```bash
./app
```

---

## 📌 Sample Menu

```text
========= STUDENT RECORD MANAGEMENT SYSTEM =========
1. Add Student
2. Display
3. Search
4. Update
5. Delete
6. Exit
```

---

## 💡 Key Learning Outcomes

* Real-world file-based data management
* Safe modification of persistent data
* Understanding limitations of file systems (no direct deletion)
* Designing modular and scalable C programs

---

## 📈 Project Level

🟢 Beginner → 🔵 Intermediate → 🔴 Advanced

This project sits at:

👉 **🟠 Intermediate (System-Level C Programming)**

---

## 🧑‍💻 Author

Developed as part of a structured learning path in C programming, focusing on building real-world systems and strong fundamentals.

---

## 📜 License

This project is open-source and free to use for educational purposes.

---

## 🔥 Future Scope

This system can be extended into:

* GUI-based application
* Database-integrated system (MySQL)
* Web-based student portal
* Embedded system-based record manager

---

# ⭐ Final Note

This project is not just about CRUD operations —
it demonstrates **how real systems manage data safely and efficiently using low-level programming**.
