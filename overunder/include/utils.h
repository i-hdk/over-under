#ifndef UTILS_H
#define UTILS_H

#include "main.h"
#include "api.h"
#include <math.h>
#include <string>
#include <bits/stdc++.h>
using namespace okapi;


/**
 * @brief print on pros screen
 * 
 * @param value 
 * @param line 0-7
 */
void print(int value, int line);

/**
 * @brief print on pros screen
 * 
 * @param value 
 * @param line 0-7
 */
void print(double value, int line);

void print(std::string text, int value, int line);

/**
 * @brief print on pros screen
 * 
 * @param value 
 * @param line 0-7
 */
void print(std::string text, double value, int line);

void wait(double t);

#endif