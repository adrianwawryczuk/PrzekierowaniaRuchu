#pragma once

#define _USE_MATH_DEFINES

#include "MySqlConnection.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace sql;
using namespace std;

class Preparator
{
public:
	Preparator(int, int);
	~Preparator();

	void setPartitions(int amountInRow, int amountInColumn);
	void calculateLengthOfEdges();
	double measure(double, double, double, double);
};

