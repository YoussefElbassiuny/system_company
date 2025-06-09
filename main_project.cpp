/*
==============================================================================
 Project Title: Employee Management System (Console-Based) 
 Developer: youssef elbassiuny

==============================================================================
  Description:

This C++ console application is an **Employee Management System** built to:
-> Add new employees  
-> Delete existing employees  
-> Apply bonuses and deductions to salaries  
-> Display current and deleted employee records  
-> Persist data using file I/O (employees.txt, deleted_employees.txt)

It uses:
-> Vectors and structs to manage and store employee data  
-> File handling for permanent storage  
-> String processing for input validation and standardization  
-> Modular functions for clarity and maintainability  

==============================================================================
  Features:

- Add multiple employees at once.
- Automatically prevents duplicate entries.
- Restore deleted employees if re-added with same data.
- Maintains a log of deleted employees.
- Net salary auto-adjusts with bonuses or deductions.
- Menu-driven interface for simple navigation.

==============================================================================
 Files Used:
1. `employees.txt` - Stores current active employee data.
2. `deleted_employees.txt` - Logs all deleted employees for audit/recovery.

==============================================================================
 How to Run:
1. Compile with any C++ compiler (e.g., g++, Visual Studio, Code::Blocks).
2. Run the executable file.
3. Follow the menu to interact with the system.

==============================================================================
 Future Improvements (Optional):
- GUI version using Qt or another library.
- Use of database instead of file-based storage.
- Authentication system for admin access.
- Export data to CSV or Excel.

==============================================================================
*/
#include <iostream>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <fstream>
using namespace std;

//*********************************************************************************************

#define endl '\n'
#define debug(x) cerr << #x << " = " << x << endl;

//*********************************************************************************************

struct epmloyee
{
    string first_name;
    string last_name;
    string type_job;
    int salary;
};

struct all_information_epmloyee
{
    string first_name;
    string last_name;
    string type_job;
    int salary;
    int net_salary;
    int bonus = 0;
    int deduction = 0;
};

//*********************************************************************************************

vector<all_information_epmloyee> about_company;
vector<all_information_epmloyee> delated_employee;

void add_employee(long long number_employee);
void delate_employee();
void show_data_employee();
void employee_delated(all_information_epmloyee data);
void show_delated_employee();
void about_strings(string &s);
void valid_string(string &s);
void add_bouns();
void add_deduction();

//*********************************************************************************************

void load_data_from_file()
{
    ifstream file("employees.txt");
    all_information_epmloyee emp;
    while (file >> emp.first_name >> emp.last_name >> emp.type_job >> emp.salary >> emp.net_salary >> emp.bonus >> emp.deduction)
    {
        about_company.push_back(emp);
    }
    file.close();
}

//*********************************************************************************************

void save_data_to_file()
{
    ofstream file("employees.txt");
    for (const auto &emp : about_company)
    {
        file << emp.first_name << " " << emp.last_name << " "
             << emp.type_job << " " << emp.salary << " "
             << emp.net_salary << " " << emp.bonus << " " << emp.deduction << endl;
    }
    file.close();
}

//*********************************************************************************************

void save_deleted_to_file(const all_information_epmloyee &emp)
{
    ofstream file("deleted_employees.txt");
    file << emp.first_name << " " << emp.last_name << " "
         << emp.type_job << " " << emp.salary << " "
         << emp.net_salary << " " << emp.bonus << " " << emp.deduction << endl;
    file.close();
}

//*********************************************************************************************

void load_deleted_from_file()
{
    ifstream file("deleted_employees.txt");
    all_information_epmloyee emp;
    while (file >> emp.first_name >> emp.last_name >> emp.type_job >> emp.salary >> emp.net_salary >> emp.bonus >> emp.deduction)
    {
        delated_employee.push_back(emp);
    }
    file.close();
}

//*********************************************************************************************

void remove_employee_from_deleted_file(const all_information_epmloyee &emp)
{

    for (auto it = delated_employee.begin(); it != delated_employee.end();)
    {
        if (it->first_name == emp.first_name &&
            it->last_name == emp.last_name &&
            it->type_job == emp.type_job &&
            it->salary == emp.salary)
        {
            it = delated_employee.erase(it);
        }
        else
        {
            ++it;
        }
    }
    ofstream file("deleted_employees.txt");
    for (const auto &e : delated_employee)
    {
        file << e.first_name << " " << e.last_name << " "
             << e.type_job << " " << e.salary << " "
             << e.net_salary << " " << e.bonus << " " << e.deduction << endl;
    }
    file.close();
}

//*********************************************************************************************

void valid_string(string &s)
{
    while (true)
    {
        if (s == "accountant" || s == "generalmanager" || s == "softwareengneer" || s == "graficdesign" || s == "departmentmanager")
        {
            break;
        }
        else
        {
            cout << "invalid input , please chooes valid type job" << endl;
            cin >> s;
            valid_string(s);
        }
    }
}

//*********************************************************************************************

void list()
{
    cout << "choose what do you need" << endl;
    cout << "(1) add employee" << endl;
    cout << "(2) delate employee" << endl;
    cout << "(3) show the data of employee" << endl;
    cout << "(4) show the employee were delated" << endl;
    cout << "(5) add bonus to employee" << endl;
    cout << "(6) add deduction to employee" << endl;
    cout << "(7) exit of programming" << endl;
    long long this_choose;
    cin >> this_choose;
    cout << endl
         << endl;
    if (this_choose == 1)
    {
        cout << "please , enter the number of employee" << endl;
        long long numer_employee;
        cin >> numer_employee;
        add_employee(numer_employee);
    }
    else if (this_choose == 2)
    {
        delate_employee();
    }
    else if (this_choose == 3)
    {
        show_data_employee();
    }
    else if (this_choose == 4)
    {
        show_delated_employee();
    }
    else if (this_choose == 5)
    {
        add_bouns();
    }
    else if (this_choose == 6)
    {
        add_deduction();
    }
    else if (this_choose == 7)
    {
        exit(0);
    }
}

//*********************************************************************************************

void add_employee(long long number_employee)
{
    vector<epmloyee> about_employee(number_employee);

    for (long long i = 0; i < number_employee; ++i)
    {
        cout << "data of employee" << i + 1 << endl;
        cout << "enter the first name of employee" << i + 1 << endl;
        cin >> about_employee[i].first_name;
        about_strings(about_employee[i].first_name);
        cout << "enter the last name of employee" << i + 1 << endl;
        cin >> about_employee[i].last_name;
        about_strings(about_employee[i].last_name);
        cout << "choose the type of job ->";
        cout << " GeneralManager     " << " DepartmentManager     " << " SoftwareEngineer     " << " GraphicDesigner   " << " Accountant  " << endl;
        cout << "enter your choose" << endl;
        cin >> about_employee[i].type_job;
        about_strings(about_employee[i].type_job);
        valid_string(about_employee[i].type_job);

        cout << "enter the salary of employee " << about_employee[i].first_name << endl;
        cin >> about_employee[i].salary;
        all_information_epmloyee data{about_employee[i].first_name, about_employee[i].last_name, about_employee[i].type_job, about_employee[i].salary, about_employee[i].salary, 0, 0};
          bool exists_in_current = false;
        bool restored_from_deleted = false;

        for (auto it = about_company.begin(); it != about_company.end(); ++it)
        {
            if (it->first_name == about_employee[i].first_name && it->last_name == about_employee[i].last_name && it->type_job == about_employee[i].type_job && it->salary == about_employee[i].salary)
            {
                cout << "this employee is olready in compay" << endl;
                exists_in_current=true;
                break;
            }
            else
            {
                continue;
            }
        }
        for (auto it = delated_employee.begin(); it != delated_employee.end(); ++it)
        {
            if (it->first_name == about_employee[i].first_name && it->last_name == about_employee[i].last_name && it->type_job == about_employee[i].type_job && it->salary == about_employee[i].salary)
            {
                about_company.push_back(*it);
                save_data_to_file();
                remove_employee_from_deleted_file(data);
                restored_from_deleted = true;
                break;
            }
            else
            {
                continue;
            }
            cout << endl;
            about_company.push_back(*it);
            save_data_to_file();
        }
         if (!exists_in_current && !restored_from_deleted)
        {
            about_company.push_back(data);
            save_data_to_file();
            cout << "New employee added successfully!" << endl;
        }
    }
    list();
}

//*********************************************************************************************

void show_delated_employee()
{
    if (!delated_employee.empty())
    {
        for (long long i = 0; i < delated_employee.size(); ++i)
        {
            cout << "name of employee : ";
            cout << delated_employee[i].first_name << " " << delated_employee[i].last_name << endl;
            cout << "type job of employee : ";
            cout << delated_employee[i].type_job << endl;
            cout << "salary of employee : ";
            cout << delated_employee[i].salary << endl;
        }
    }
    else
    {
        cout << "there arenot employees delated" << endl;
    }
    cout << endl
         << endl;
    list();
}

//*********************************************************************************************

void employee_delated(all_information_epmloyee Data)
{
    delated_employee.push_back(Data);
}

//*********************************************************************************************

void add_deduction()
{
    string f_name, l_name, type_job;
    long long deduction;
    cout << "enter the first name of employee that you need bouns him" << endl;
    cin >> f_name;
    about_strings(f_name);
    cout << "enter the last name of employee that you need bouns him" << endl;
    cin >> l_name;
    about_strings(l_name);
    cout << "enter the type job of employee that you need bouns him" << endl;
    cout << " GeneralManager     " << " DepartmentManager     " << " SoftwareEngineer     " << " GraphicDesigner     " << " Accountant " << endl;

    cin >> type_job;
    about_strings(type_job);
    valid_string(type_job);
    cout << "enter the value of deduction" << endl;
    cin >> deduction;

    for (long long i = 0; i < about_company.size(); ++i)
    {
        if (about_company[i].first_name == f_name && about_company[i].last_name == l_name && about_company[i].type_job == type_job)
        {
            about_company[i].net_salary = about_company[i].net_salary - deduction;
            cout << "deduction is done" << endl;
            save_data_to_file();
            list();
        }
        else
        {
            continue;
        }
    }
    cout << "this employee isnot exist" << endl;
    list();
}

//*********************************************************************************************

void add_bouns()
{
    string f_name, l_name, type_job;
    long long bonus;
    cout << "enter the first name of employee that you need bouns him" << endl;
    cin >> f_name;
    about_strings(f_name);
    cout << "enter the last name of employee that you need bouns him" << endl;
    cin >> l_name;
    about_strings(l_name);
    cout << "enter the type job of employee that you need bouns him" << endl;
    cout << " GeneralManager     " << " DepartmentManager     " << " SoftwareEngineer     " << " GraphicDesigner     " << " Accountant " << endl;
    cin >> type_job;
    about_strings(type_job);
    valid_string(type_job);
    cout << "enter the value of bonus" << endl;
    cin >> bonus;

    for (long long i = 0; i < about_company.size(); ++i)
    {
        if (about_company[i].first_name == f_name && about_company[i].last_name == l_name && about_company[i].type_job == type_job)
        {
            about_company[i].net_salary = about_company[i].net_salary + bonus;
            cout << "bonus is done" << endl;
            save_data_to_file();
            list();
        }
        else
        {
            continue;
        }
    }
    cout << "this employee isnot exist" << endl;
    list();
}

//*********************************************************************************************

void delate_employee()
{
    if (!about_company.empty())
    {
        cout << "enter the first name of employee" << endl;
        string f_name, l_name, type_job;
        long long salary;
        cin >> f_name;
        about_strings(f_name);
        cout << "enter the last name of employee" << endl;
        cin >> l_name;
        about_strings(l_name);

        cout << "enter the type of job :" << endl;
        cout << " GeneralManager     " << " DepartmentManager     " << " SoftwareEngineer     " << " GraphicDesigner     " << " Accountant " << endl;
        cin >> type_job;
        about_strings(type_job);
        valid_string(type_job);
        cout << "enter the salary of employee" << endl;
        cin >> salary;
        for (auto it = about_company.begin(); it != about_company.end(); ++it)
        {
            if (it->first_name == f_name && it->last_name == l_name && it->type_job == type_job && it->salary == salary)
            {
                save_deleted_to_file(*it);
                employee_delated(*it);

                it = about_company.erase(it);
                cout << "deleted is done" << endl
                     << endl;
                save_data_to_file();
                list();
            }
            else
            {
                continue;
            }
        }
        cout << "this employee isnot exist" << endl
             << endl;
        list();
    }
    else
    {
        cout << "theere arenot employees";
        list();
    }
}

//*********************************************************************************************

void show_data_employee()
{
    long long number_employee = about_company.size();
    for (long long i = 0; i < number_employee; ++i)
    {
        cout << "name of emmployee : " << about_company[i].first_name << " " << about_company[i].last_name << endl;
        cout << " type of job : " << about_company[i].type_job << endl;
        cout << "the salary : " << about_company[i].salary << endl;
        cout << "the net salary : " << about_company[i].net_salary << endl;
    }
    cout << endl;
    list();
}

//*********************************************************************************************

void about_strings(string &s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

//*********************************************************************************************

int main()
{
    load_deleted_from_file();
    load_data_from_file();
    list();
}
