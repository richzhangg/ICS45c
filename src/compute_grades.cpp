#include "compute_grades.hpp"
#include <compare>
#include <iosfwd>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <iomanip>


using namespace std;


void Student::validate() const {
    for (int i : quiz)
        if (0 > i || 100 < i) throw std::domain_error(string("Error: invalid percentage " + to_string(i)));
    for (int i : hw)
        if (0 > i || 100 < i) throw std::domain_error(string("Error: invalid percentage " + to_string(i)));

    if (final_score < 0 || final_score > 100) throw std::domain_error(string("Error: invalid percentage " + to_string(final_score)));
}

bool Student::operator==(const Student& other) const {
    return (first_name == other.first_name && last_name == other.last_name);
}

vector<string> get_all_lines(istream& in) {
    vector<string> v;
    string k;
    while (getline(in, k)) {
        if (k.empty()) break;
        else v.push_back(k);
    }
    return v;
}

istream& operator>>(istream& in, Student& s) {
    vector<string> v = get_all_lines(in);
    // for (auto r : v) cout << r << " ";
    // cout << endl;
    // It is all good here.
    string keyword;
    for (string k : v) {
        istringstream str(k);
        str >> keyword;
        int n;
        if (keyword == "Name") {
            str >> s.first_name;
            str >> s.last_name;
            string l;
            while (str >> l) { s.last_name += (" " + l); }
        }
        else if (keyword == "Quiz") {
            while (str >> n) { s.quiz.push_back(n); }
        }
        else if (keyword == "HW") {
            while (str >> n) { s.hw.push_back(n); }
        }
        else if (keyword == "Final") {
            str >> s.final_score;
        }
    }
    return in;
}


istream& operator>>(istream& in, Gradebook& b) {
    Student s;
    while (in >> s) {
        b.students.push_back(Student(s));
        s = Student();
    }
    return in;
}

void Student::compute_quiz_avg() {
    quiz_avg = 0.0;
    double avg = 0.0;
    int total_num = 0;
    int min_num = 101;
    for_each(quiz.begin(), quiz.end(), [&](int x) { avg += x; total_num++; min_num = min(x, min_num); });
    if (total_num >= 2)
        quiz_avg = (avg-min_num)/(total_num-1);
    else if (total_num == 1)
        quiz_avg = avg;
    else if (total_num == 0)
        quiz_avg = 0.0;
}

void Student::compute_hw_avg() {
    double avg = 0.0;
    int total_num = 0;
    int min_num = 101;
    for_each(hw.begin(), hw.end(), [&](int x) { avg += x; total_num++; min_num = min(x, min_num); });
    if (total_num != 0) hw_avg = avg/total_num;
    else hw_avg = 0.0;
}

void Student::compute_grade() {
    Student::compute_quiz_avg();
    Student::compute_hw_avg();
    Student::compute_course_score();
}

void Student::compute_course_score() {
    double everything = 0.0;
    everything += ((hw_avg*0.3) + (quiz_avg*0.4) + (final_score*0.3));
    course_score = int(everything);
    int g = course_score;
    if (97 <= g && g <= 100) course_grade = "A+";
    if (93 <= g && g <= 96) course_grade = "A";
    if (90 <= g && g <= 92) course_grade = "A-";
    if (87 <= g && g <= 89) course_grade = "B+";
    if (83 <= g && g <= 86) course_grade = "B";
    if (80 <= g && g <= 82) course_grade = "B-";
    if (77 <= g && g <= 79) course_grade = "C+";
    if (73 <= g && g <= 76) course_grade = "C";
    if (70 <= g && g <= 72) course_grade = "C-";
    if (67 <= g && g <= 69) course_grade = "D+";
    if (63 <= g && g <= 66) course_grade = "D";
    if (60 <= g && g <= 62) course_grade = "D-";
    if (0 <= g && g <= 59) course_grade = "F";

}

void Gradebook::compute_grades() {
    for_each(students.begin(), students.end(), [](Student& s) { s.compute_grade(); });
}

strong_ordering Student::operator<=>(const Student& other) const {
    return (last_name+first_name) <=> (other.last_name+other.first_name);
}

void Gradebook::sort() {
    std::sort(students.begin(), students.end());
}

void Gradebook::validate() const {
    for_each(students.begin(), students.end(), [](Student s) { s.validate(); });
}

std::ostream& operator<<(std::ostream& out, const Gradebook& b) {
    for_each(b.students.begin(), b.students.end(), [&](Student s) { out << s << endl; });
    return out;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
    std::stringstream temp;
    // We don't want to set formatting flags globally.
    temp << std::setprecision(2) << std::fixed << std::left;

    temp << left << setw(8) << "Name: " << s.first_name << " " << s.last_name << endl;
    temp << left << setw(8) << "HW Ave: " << int(s.hw_avg) << endl;
    temp << left << setw(8) << "QZ Ave: " << int(s.quiz_avg) << endl;
    temp << left << setw(8) << "Final: " << int(s.final_score) << endl;
    temp << left << setw(8) << "Total: " << int(s.course_score) << endl;
    temp << left << setw(8) << "Grade: " << s.course_grade << endl;
    out << temp.str();
    return out;
}


