// MAIN
// g++ main.cpp -o main database.cpp; ./main;

# include <iostream>
# include <string>
# include <fstream>
# include <vector>
# include "database.h"
using namespace std;

StudentDatabase SD;
Student *current_student; // = Student("", 0, 0, 0, 0);
ifstream inFile;
ofstream outFile;
// string for inputting strings
string input_string;
string input_string2;

// for selecting menu options
int choice;

// ???
int student_id;

// for initialize and register new student
string name_string;
int id_int;
int birthyear_int;
int total_classes_int;
int absences_int;

// void initialize();

void initialization () {
  
  inFile.open("students.txt");
  if (inFile.fail()) {
    cout << endl << "File not found!" << endl;
  }
  else {
    while (!inFile.eof()){
      // name
      getline(inFile, name_string);
      // id
      getline(inFile, input_string);
      id_int = stoi(input_string);
      // birthyear
      getline(inFile, input_string);
      birthyear_int = stoi(input_string);
      // total_classes
      getline(inFile, input_string);
      total_classes_int = stoi(input_string);
      // absences
      getline(inFile, input_string);
      absences_int = stoi(input_string);
      // create student
      SD.add_student(name_string, id_int, birthyear_int, total_classes_int, absences_int);
    }
  }
}

int num_input () {
  int return_int;
  cin >> input_string;
  try {
    return_int = stoi(input_string);
  }
  catch (...) {
    return_int = -1;
  }
  // cout << "Return int: " << return_int << endl;
  return return_int;  
}

void rewrite_student_file () {
  outFile.open("students.txt");
  if (outFile.fail()) {
    cout << endl << "File not found!" << endl;
  }
  else {
    for (int i = 0; i < SD.get_latest_id(); i++) {
      current_student = &SD.get_student(i + 1);
      if (i > 0) {
        outFile << endl;
      }
      outFile << current_student -> get_name() << endl;
      outFile << current_student -> get_id() << endl;
      outFile << current_student -> get_birthyear() << endl;
      outFile << current_student -> get_total_classes() << endl;
      outFile << current_student -> get_absences();
    }
  }
  outFile.close();
  
}

void database_id_search () {
  id_int = 0;
  while (id_int == 0) {
    cout << "Input ID:\n (0 to go back)" << endl;
    id_int = num_input();
    if (id_int == 0) {
      return;
    }
    else if (0 > id_int || id_int > SD.get_latest_id()) {
      cout << endl << "There is no student with that ID." << endl;
      id_int = 0; 
      cout << endl;
    }
  }
}

void search_student_by_id () {
  database_id_search();
  if (id_int == 0) {
    return;
  }
  cout << endl;
  current_student = &SD.get_student(id_int);
  current_student->print_info();
}

void search_student_by_name () {
  name_string = "";
  while (name_string == "") {
    cout << "Enter student's family name" << endl;
    cin >> input_string;
    cout << "\nEnter student's first name" << endl;
    cin >> input_string2;
    input_string2 = input_string + ", " + input_string2;
    cout << "Search for name " << input_string2 << "?\n (1 for yes, 2 for no, 0 for quit)" << endl;
    choice = num_input();
    switch (choice) {
      case 1:
        try {
          current_student = &SD.get_student_by_name(input_string2);
          cout << endl;
          current_student -> print_info();
          name_string = input_string2;
        }
        catch (...) {
          cout << "Student does not exist." << endl;
          input_string2 = "";
        }
        break;
      case 2:
        cout << endl;
        break;
      case 0:
        return;
    }
  }
  try {
    current_student = &SD.get_student(id_int);
  }
  catch (...) {
    
  }
}

void report_student_attendence () {
  while (true) {
    database_id_search();
    // cout << id_int << " | " << (id_int == 0) << endl;
    if (id_int == 0) {
      return;
    }
    cout << endl;
    current_student = &SD.get_student(id_int);
    id_int = 0;
    while (id_int == 0) {
      cout << "Was " << current_student->get_name() << " present?\n (1 for yes, 2 for no, 0 for go back)" << endl;
      id_int = num_input();
      if (id_int == 0) {
        return;
      }
      else if (0 < id_int <= 2) {
        current_student->update_attendence(id_int);
        rewrite_student_file();
        cout <<  current_student->get_name() << " file updated successfully!" << endl;
        return;
      }
      else {
        id_int = 0;
      }
    }
  }
}

void register_new_student () {
  // get name
  name_string = "";
  while (name_string == "") {
    cout << "Enter student's family name" << endl;
    cin >> input_string;
    cout << "\nEnter student's first name" << endl;
    cin >> input_string2;
    input_string2 = input_string + ", " + input_string2;
    cout << "Use name " << input_string2 << "?\n (1 for yes, 2 for no, 0 for quit)" << endl;
    choice = num_input();
    switch (choice) {
      case 1:
        try {
          current_student = &SD.get_student_by_name(input_string2);
          cout << "\nA student named " << input_string2 << " is already registered as student #" << current_student->get_id() << ". Is this a new student?\n (1 for yes, anything else for no)" << endl;
          choice = num_input();
          if (choice == 1) {
            name_string = input_string2;
          }
        }
        catch (...) {
          name_string = input_string2;
        }
        break;
      case 2:
        cout << endl;
        break;
      case 0:
        return;
    }
  }

  birthyear_int = 0;
  while (birthyear_int == 0) {
    cout << "\nEnter student's birthyear" << endl;
    birthyear_int = num_input();
    if ((2022 - birthyear_int - 5) < 1 || (2022 - birthyear_int - 5) > 12) {
      cout << "Student age not appropriate" << endl;
      birthyear_int = 0;
    }
  }

  id_int = 0;  // used as while condition 
  while (id_int == 0) {
    cout << "Register new student: " << name_string << " (Grade " << (2022 - birthyear_int - 5) << ")?\n (1 for yes, 2 for no, 0 for quit)" << endl;
    choice = num_input();
    switch (choice) {
      case 1:
        id_int = SD.get_latest_id() + 1;
        break;
      case 2:
        cout << endl;
        break;
      case 0:
        return;
    }
  }

  SD.add_student(name_string, id_int, birthyear_int, 0, 0);
  
  outFile.open("students.txt", fstream::app);
  if (outFile.fail()) {
    cout << endl << "File not found!" << endl;
  }
  else {
    outFile << endl << name_string << endl << id_int << endl << birthyear_int << endl << 0 << endl << 0;
  }
  outFile.close();
  cout << "\nNew student registered!" << endl;
}

int main(){
  initialization();
  while (true) {
    cout << "\n -- MADAN ACADEMY STUDENT ATTENDENCE KEEPER -- "
      << "\n\nWhat would you like to do?"
      << "\n 1. Get single student attendence by student ID"
      << "\n 2. Get single student attendence by student name"
      << "\n 3. Get all student attendence"
      << "\n 4. Report student attendence by student ID"
      << "\n 5. Register new student"
      << "\n 0. Close" << endl;
    choice = num_input();
    cout << endl;
    
    switch(choice) {
      case 1:
        search_student_by_id();
        break;
      case 2:
        search_student_by_name();
        break;
      case 3:
        SD.print_all_student_info();
        break;
      case 4:
        report_student_attendence();
        break;
      case 5:
        register_new_student();
        break;
      case 0:
        return(0);
        break;
      default:
        cout << "Not found" << endl;
        break;
    }
  }
  return(0);
}