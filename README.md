# Employee Management System (Console-Based)
**Developer:** youssef elbassiuny

---

## Description

This C++ console application is an **Employee Management System** built to:

- Add new employees  
- Delete existing employees  
- Apply bonuses and deductions to salaries  
- Display current and deleted employee records  
- Persist data using file I/O (`employees.txt`, `deleted_employees.txt`)

It uses:

- Vectors and structs to manage and store employee data  
- File handling for permanent storage  
- String processing for input validation and standardization  
- Modular functions for clarity and maintainability  

---

## Features

- Add multiple employees at once  
- Automatically prevents duplicate entries  
- Restore deleted employees if re-added with same data  
- Maintains a log of deleted employees  
- Net salary auto-adjusts with bonuses or deductions  
- Menu-driven interface for simple navigation  

---

## Files Used

1. `employees.txt` – Stores current active employee data  
2. `deleted_employees.txt` – Logs all deleted employees for audit/recovery  

---

## How to Run

1. Compile with any C++ compiler (e.g., `g++`, Visual Studio, Code::Blocks)  
2. Run the executable file  
3. Follow the menu to interact with the system  

---

## Future Improvements (Optional)

- GUI version using Qt or another library  
- Use of database instead of file-based storage  
- Authentication system for admin access  
- Export data to CSV or Excel  
