#include <algorithm>
#include <numeric>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>
#include <string>
#include <compare>
#include <iosfwd>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <sstream>
#include <istream>
#include "compute_grades.hpp"

void Student::compute_quiz_avg() {
    int num_quizzes = quiz.size();
    
    if (num_quizzes == 0) {
        quiz_avg = 0;
    } else if (num_quizzes == 1) {
        quiz_avg = quiz[0];
    } else {
        std::vector<int> tempQuiz = quiz;
        std::sort(tempQuiz.begin(), tempQuiz.end());
        tempQuiz.erase(tempQuiz.begin());

        double total = std::accumulate(tempQuiz.begin(), tempQuiz.end(), 0.0);
        quiz_avg = total / tempQuiz.size();
    }
}

void Student::compute_hw_avg() {
    hw_avg = hw.empty() ? 0 : std::accumulate(hw.begin(), hw.end(), 0.0) / hw.size();
}

void Student::compute_course_score() {
    double quiz_contrib = 0.4 * quiz_avg;
    double hw_contrib = 0.3 * hw_avg;
    double final_contrib = 0.3 * final_score;

    course_score = std::round(quiz_contrib + hw_contrib + final_contrib);
}

void Student::compute_grade() {
    compute_quiz_avg();
    compute_hw_avg();
    compute_course_score();

    if (course_score >= 97) course_grade = "A+";
    else if (course_score >= 93) course_grade = "A";
    else if (course_score >= 90) course_grade = "A-";
    else if (course_score >= 87) course_grade = "B+";
    else if (course_score >= 83) course_grade = "B";
    else if (course_score >= 80) course_grade = "B-";
    else if (course_score >= 77) course_grade = "C+";
    else if (course_score >= 73) course_grade = "C";
    else if (course_score >= 70) course_grade = "C-";
    else if (course_score >= 67) course_grade = "D+";
    else if (course_score >= 63) course_grade = "D";
    else if (course_score >= 60) course_grade = "D-";
    else course_grade = "F";
}

void Student::validate() const {
    auto validateScore = [](int score) {
        if (score < 0 || score > 100) {
            throw std::domain_error("Error: invalid percentage " + std::to_string(score));
        }
    };

    std::for_each(quiz.begin(), quiz.end(), validateScore);
    std::for_each(hw.begin(), hw.end(), validateScore);

    validateScore(final_score);
}

std::vector<std::string> read_all_lines(std::istream& input) {
    std::vector<std::string> lines;
    for (std ::string line; std::getline(input, line) && !line.empty();) {
        lines.push_back(line);
    }
    return lines;
}

std::istream& operator>>(std::istream& in, Student& s) {
    std::vector<std::string> lines = read_all_lines(in);
    std::string keyword;

    for (const std::string& line : lines) {
        std::istringstream stream(line);
        stream >> keyword;

        if (keyword == "Name") {
            stream >> s.first_name;
            std::string part;
            s.last_name.clear();
            while (stream >> part) {
                if (!s.last_name.empty()) {
                    s.last_name += " ";
                }
                s.last_name += part;
            }
        } else if (keyword == "Quiz") {
            int score;
            while (stream >> score) {
                s.quiz.push_back(score);
            }
        } else if (keyword == "HW") {
            int score;
            while (stream >> score) {
                s.hw.push_back(score);
            }
        } else if (keyword == "Final") {
            stream >> s.final_score;
        } else {
            std::cout << "Unknown keyword: " << keyword << std::endl;
        }
    }
    return in;
}

std::istream& operator>>(std::istream& in, Gradebook& b) {
    for (Student s; in >> s;) {
        b.students.emplace_back(s);
    }
    return in;
}

void Gradebook::compute_grades() {
    for (auto& student : students) {
        student.compute_grade();
    }
}

void Gradebook::validate() const {
    for (const auto& student : students) {
        student.validate();
    }
}

void Gradebook::sort() {
    std::vector<Student> sorted_students(students);
    std::sort(sorted_students.begin(), sorted_students.end());
    students = sorted_students;
}

std::strong_ordering Student::operator<=>(const Student& other) const {
    if (auto cmp = last_name.compare(other.last_name); cmp != 0) {
        return cmp <=> 0;
    }
    return first_name.compare(other.first_name) <=> 0;
}

bool Student::operator==(const Student& other) const {
    if (this->last_name != other.last_name) {
        return false;
    }
    if (this->first_name != other.first_name) {
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, const Gradebook& b) {
    for (const auto& student : b.students) {
        out << student << std::endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << std::left << std::setw(8) << "Name: " << s.first_name << s.last_name << '\n' <<
           std::setw(8) << "HW Ave: " << s.hw_avg << '\n' <<
           std::setw(8) << "QZ Ave: " << s.quiz_avg << '\n' <<
           std::setw(8) << "Final: " << s.final_score << '\n' <<
           std::setw(8) << "Total: " << s.course_score << '\n' <<
           std::setw(8) << "Grade: " << s.course_grade << std::endl;
    return out;
}
