#include "compute_grades.hpp"
#include <iostream>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <map>

void Student::compute_quiz_avg() {
    if (quiz.empty()) {
        quiz_avg = 0.0;
    } else {
        double sum = std::accumulate(quiz.begin(), quiz.end(), 0.0);
        int count = static_cast<int>(quiz.size());
        if (count > 1) {
            int min_score = *std::min_element(quiz.begin(), quiz.end());
            sum -= min_score;  // Subtract the minimum score if more than one quiz
            --count;  // Decrement count since the lowest score is dropped
        }
        quiz_avg = count > 0 ? sum / count : 0.0;  // Ensure we don't divide by zero
    }
}

void Student::compute_hw_avg() {
    hw_avg = hw.empty() ? 0 : std::accumulate(hw.begin(), hw.end(), 0) / static_cast<double>(hw.size());
}

void Student::compute_course_score() {
    course_score = std::lround(quiz_avg * 0.4 + hw_avg * 0.3 + final_score * 0.3);
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
    else course_grade = "F"; // This covers everything below 60
}


void Student::validate() const {
    // Validate quiz scores
    std::for_each(quiz.begin(), quiz.end(), [](const int score) {
        if (score < 0 || score > 100) {
            throw std::domain_error("Error: invalid quiz percentage " + std::to_string(score));
        }
    });

    // Validate homework scores
    std::for_each(hw.begin(), hw.end(), [](const int score) {
        if (score < 0 || score > 100) {
            throw std::domain_error("Error: invalid homework percentage " + std::to_string(score));
        }
    });

    // Validate final score
    if (final_score < 0 || final_score > 100) {
        throw std::domain_error("Error: invalid final exam percentage " + std::to_string(static_cast<int>(final_score)));
    }
}

std::strong_ordering Student::operator<=>(const Student& other) const {
    if (auto cmp = last_name <=> other.last_name; cmp != 0) 
        return cmp;
    return first_name <=> other.first_name;
}

bool Student::operator==(const Student& other) const {
    return tie(last_name, first_name) == tie(other.last_name, other.first_name);
}

std::istream& operator>>(std::istream& in, Student& s) {
    std::string line, key;
    while (std::getline(in, line) && !line.empty()) {
        std::istringstream iss(line);
        iss >> key;
        if (key == "Name") {
            std::getline(iss >> std::ws, s.full_name); // Capture the rest of the line as the full name
        } else if (key == "Quiz") {
            s.quiz = std::vector<int>(std::istream_iterator<int>(iss), {});
        } else if (key == "HW") {
            s.hw = std::vector<int>(std::istream_iterator<int>(iss), {});
        } else if (key == "Final") {
            iss >> s.final_score;
        }
    }
    return in;
}


std::ostream& operator<<(std::ostream& out, const Student& s) {
    auto print_score = [&out](double score) {
        out << (score == static_cast<int>(score) ? std::to_string(static_cast<int>(score)) : std::to_string(score));
    };

    out << "Name:   " << s.full_name << "\n";
    out << "HW Ave: "; print_score(s.hw_avg); out << "\n";
    out << "QZ Ave: "; print_score(s.quiz_avg); out << "\n";
    out << "Final:  "; print_score(s.final_score); out << "\n";
    out << "Total:  " << s.course_score << "\n";
    out << "Grade:  " << s.course_grade << "\n"; // Ensure this is the only newline at the end of each student's block
    // Do not add an extra "\n" here
    return out;
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
    std::sort(students.begin(), students.end());
}

std::istream& operator>>(std::istream& in, Gradebook& b) {
    Student s;
    while (in >> s) {
        b.students.push_back(s);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Gradebook& b) {
    for (const auto& student : b.students) {
        out << student;
    }
    return out;
}

