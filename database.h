#pragma once
#include <vector>
#include <string>

class Student{
private:
	std::string name;
	int id;
  int birthyear;
  int total_classes;
  int absences;

public:
	Student(std::string the_name,	int the_id, int the_birthyear, int the_total_classes, int the_absences);
	std::string get_name();
	int get_id();
  int get_birthyear();
  int get_age_grade();
  int get_absences();
  int get_total_classes();
	float get_average();  
  void update_attendence(int);
  void print_info();
};

class StudentDatabase{
private:
	std::vector<Student> students;
	
public:
	void add_student(std::string,	int, int, int, int);
  Student& get_student(int);
  Student& get_student_by_name(std::string);
  int get_latest_id();
  void print_all_student_info();
};