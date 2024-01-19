#include "utils.h"

/**
 * @brief print on pros screen
 * 
 * @param value 
 * @param line 0-7
 */
void print(int value, int line){
    pros::lcd::clear_line(line);
    pros::lcd::set_text(line, std::to_string(value));
}

/**
 * @brief print on pros screen
 * 
 * @param value 
 * @param line 0-7
 */
void print(double value, int line){
    pros::lcd::clear_line(line);
    pros::lcd::set_text(line, std::to_string(value));
}

void print(std::string text, int value, int line){
    pros::lcd::clear_line(line);
    pros::lcd::set_text(line, text + ": " + std::to_string(value));
}

/**
 * @brief print on pros screen
 * 
 * @param value 
 * @param line 0-7
 */
void print(std::string text, double value, int line){
    pros::lcd::clear_line(line);
    pros::lcd::set_text(line, text + ": " + std::to_string(value));
}

//basically runs pros::delay(t)
void wait(double t){
    pros::delay(t);
}