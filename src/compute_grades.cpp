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
    size_t quiz_count = quiz.size();
    switch (quiz_count) {
        case 0:
            quiz_avg = 0;
            break;
        case 1:
            quiz_avg = quiz[0];
            break;
        default:
            std::vector<int> adjustedQuiz(quiz.begin() + 1, quiz.end());
            std::sort(adjustedQuiz.begin(), adjustedQuiz.end());
            quiz_avg = std::accumulate(adjustedQuiz.begin(), adjustedQuiz.end(), 0.0) / adjustedQuiz.size();
            break;
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

    if (course_score >= 97) {
        course_grade = "A+";
    } else if (course_score >= 93) {
        course_grade = "A";
    } else if (course_score >= 90) {
        course_grade = "A-";
    } else if (course_score >= 87) {
        course_grade = "B+";
    } else if (course_score >= 83) {
        course_grade = "B";
    } else if (course_score >= 80) {
        course_grade = "B-";
    } else if (course_score >= 77) {
        course_grade = "C+";
    } else if (course_score >= 73) {
        course_grade = "C";
    } else if (course_score >= 70) {
        course_grade = "C-";
    } else if (course_score >= 67) {
        course_grade = "D+";
    } else if (course_score >= 63) {
        course_grade = "D";
    } else if (course_score >= 60) {
        course_grade = "D-";
    } else {
        course_grade = "F";
    }
}

void Student::validate() const {
    auto isValidScore = [](int score) {
        bool isInvalid = score < 0 || score > 100;
        if (isInvalid) {
            throw std::domain_error("Error: invalid percentage " + score);
        }
    };

    for (const auto& q : quiz) {
        isValidScore(q);
    }
    for (const auto& h : hw) {
        isValidScore(h);
    }

    isValidScore(final_score);
}



std::vector<std::string> read_all_lines(std::istream& input_stream) {
    std::vector<std::string> result;
    std::ostringstream buffer;
    std::string line;
    while (std::getline(input_stream, line)) {
        if (line.empty()) {
            result.push_back(buffer.str());
            buffer.str("");
            buffer.clear();
        } else {
            buffer << line << '\n';
        }
    }
    if (!buffer.str().empty()) {
        result.push_back(buffer.str());
    }

    return result;
}


std::istream& operator>>(std::istream& in, Student& s) {
    std::vector<std::string> lines;
    std::string temp;
    while(getline(in, temp)) {lines.push_back(temp);}

    std::unordered_map<std::string, std::function<void(std::istringstream&)>> actions {
        {"Name", [&](std::istringstream& stream){
            stream >> s.first_name;
            if (!stream.eof()) s.last_name = std::string();
            std::for_each(std::istream_iterator<std::string>(stream), {}, 
                [&](std::string str){s.last_name += ' ' + str;});
        }},
        {"Quiz", [&](std::istringstream& stream){
            std::for_each(std::istream_iterator<std::string>(stream), {},
                [&](std::string str){s.quiz.push_back(std::stoi(str));});
        }},
        {"HW", [&](std::istringstream& stream){
            std::for_each(std::istream_iterator<std::string>(stream), {},
                [&](std::string str){s.hw.push_back(std::stoi(str));});
        }},
        {"Final", [&](std::istringstream& stream){
            std::string string_final;
            stream >> string_final;
            s.final_score = std::stod(string_final);
        }}
    };
    
    std::for_each(begin(lines), end(lines), [&](std::string line){
        std::istringstream stream(line); std::string keyword;
        stream >> keyword;
        auto action = actions.find(keyword);
        if (action != actions.end()) action->second(stream);
    });
    
    return in;
}


std::istream& operator>>(std::istream& in, Gradebook& b) {
    std::vector<std::string> data = read_all_lines(in);
    for (const auto& str : data) {
        std::stringstream stream(str);
        Student s;
        stream >> s;
        b.students.push_back(s);
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
        out << [&]() -> std::string {
            std::stringstream ss;
            ss << student << '\n';
            return ss.str();
        }();
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
