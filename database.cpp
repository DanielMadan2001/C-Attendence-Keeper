# include <iostream>
# include <vector>
# include "database.h"
using namespace std;

Student::Student(string the_name,	int the_id, int the_birthyear, int the_total_classes, int the_absences) {  // 
	name = the_name;
	id = the_id;
  birthyear = the_birthyear;
  absences = the_absences;
  total_classes = the_total_classes;
}

int Student::get_id() {
	return id;
}

string Student::get_name() {
	return name;
}

int Student::get_birthyear() {
	return birthyear;
}

int Student::get_age_grade() {
  return 2022 - birthyear - 5;
}

int Student::get_absences() {
  return absences;
}

int Student::get_total_classes() {
  return total_classes;
}

float Student::get_average() {
  return ((total_classes - absences) * 100) / total_classes;
}

void Student::update_attendence(int is_present = 1) {
  total_classes += 1;
  absences += is_present - 1;  // 1 is present, 2 is absent
}

void Student::print_info() {
  cout << "Student #" << id << ": " << name << " (Grade " << get_age_grade() << ")" << endl;
  if (total_classes > 0) {
    cout << "\tRecord: " << get_average() << "% (" << (total_classes - absences) << "/" << total_classes << ")" << endl;
  }
  else {
    cout << "\tRecord: 0% (0/0)" << endl;
  }
}


void StudentDatabase::add_student(string the_name, int the_id, int the_birthyear, int the_total_classes, int the_absences){
  students.push_back(Student(the_name, the_id, the_birthyear, the_total_classes, the_absences));
}

Student& StudentDatabase::get_student(int the_id) {
  for (Student& s : students) {
    if (s.get_id() == the_id) {
      return s;
    }
  }
}

Student& StudentDatabase::get_student_by_name(string the_name) {
  for (Student& s : students) {
    if (s.get_name() == the_name) {
      return s;
    }
  }
}

int StudentDatabase::get_latest_id() {
  return students[students.size() - 1].get_id();
}

void StudentDatabase::print_all_student_info(){
  for (Student& s : students) {
      s.print_info();
  }
}