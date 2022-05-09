// MAIN

# include <iostream>
# include <string>
using namespace std;

string input_string;
int student_id;

int num_input () {
  int return_int;
  cin >> input_string;
  try {
    return_int = stoi(input_string);
  }
  catch (...) {
    return_int = 0;
  }
  // cout << "Return int: " << return_int << endl;
  return return_int;  
}

int main(){
  while (true) {
    cout << "\n -- MADAN ACADEMY STUDENT ATTENDENCE KEEPER -- "
      << "\n\nWhat would you like to do?"
      << "\n 1. Get single student attendence by student ID"
      << "\n 2. Get all student attendence"
      << "\n 3. Report student attendence by student"
      << "\n 4. Register new student"
      << "\n 0. Close" << endl;
    student_id = num_input();
    cout << endl;
    
    switch(student_id) {
      case 1:
        cout << "Get single student attendence" << endl;
        break;
      case 0:
        return(0);
        break;
      default:
        cout << "Not found" << endl;
    }
  }
  return(0);
}