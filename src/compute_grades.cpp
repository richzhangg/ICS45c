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
        auto sum = std::accumulate(quiz.begin(), quiz.end(), 0.0);
        auto count = quiz.size();
        // Drop the lowest score if there's more than one quiz score
        if (count > 1) {
            auto min_quiz_score = *std::min_element(quiz.begin(), quiz.end());
            sum -= min_quiz_score;
            --count; // Decrease the count since the lowest score is dropped
        }
        quiz_avg = sum / count;
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
    // Map of letter grades to numeric score ranges
    static const std::map<int, std::string> grade_map {
        {97, "A+"}, {93, "A"}, {90, "A-"},
        {87, "B+"}, {83, "B"}, {80, "B-"},
        {77, "C+"}, {73, "C"}, {70, "C-"},
        {67, "D+"}, {63, "D"}, {60, "D-"},
        {0, "F"}
    };
    
    auto it = grade_map.lower_bound(course_score);
    if (it != grade_map.end()) {
        course_grade = it->second;
    } else {
        course_grade = "F"; // Default to F if not found
    }
}

void Student::validate() const {
    for (int score : quiz) {
        if (score < 0 || score > 100) {
            throw std::domain_error("Error: invalid percentage " + std::to_string(score));
        }
    }
    for (int score : hw) {
        if (score < 0 || score > 100) {
            throw std::domain_error("Error: invalid percentage " + std::to_string(score));
        }
    }
    if (final_score < 0 || final_score > 100) {
        throw std::domain_error("Error: invalid percentage " + std::to_string(static_cast<int>(final_score)));
    }
}

std::strong_ordering Student::operator<=>(const Student& other) const {
    if (auto cmp = last_name.compare(other.last_name); cmp != 0) return cmp < 0 ? std::strong_ordering::less : std::strong_ordering::greater;
    return first_name.compare(other.first_name) < 0 ? std::strong_ordering::less : std::strong_ordering::greater;
}


bool Student::operator==(const Student& other) const {
    return tie(last_name, first_name) == tie(other.last_name, other.first_name);
}

std::istream& operator>>(std::istream& in, Student& s) {
    std::string line, word;
    s.quiz.clear();
    s.hw.clear();
    while (std::getline(in, line) && !line.empty()) {
        std::istringstream iss(line);
        iss >> word;
        if (word == "Name") {
            iss >> s.first_name >> s.last_name;
        } else if (word == "Quiz") {
            std::copy(std::istream_iterator<int>(iss), std::istream_iterator<int>(), back_inserter(s.quiz));
        } else if (word == "HW") {
            std::copy(std::istream_iterator<int>(iss), std::istream_iterator<int>(), back_inserter(s.hw));
        } else if (word == "Final") {
            iss >> s.final_score;
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << std::left << std::setw(8) << "Name: " << s.first_name << " " << s.last_name << "\n"
        << std::setw(8) << "HW Ave: " << std::setprecision(1) << std::fixed << s.hw_avg << "\n"
        << std::setw(8) << "QZ Ave: " << s.quiz_avg << "\n"
        << std::setw(8) << "Final: " << s.final_score << "\n"
        << std::setw(8) << "Total: " << s.course_score << "\n"
        << std::setw(8) << "Grade: " << s.course_grade << "\n\n";
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

