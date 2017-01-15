#pragma once

#define _USE_MATH_DEFINES

#include "MySqlConnection.h"
#include <iomanip>

using namespace sql;
using namespace std;

class Preparator
{
public:
	Preparator(int, int);

	void setPartitions(int amountInRow, int amountInColumn) const;
	static void setEmptyArcFlags(int partitionsAmount);
	void calculateLengthOfEdges() const;
	double measure(double, double, double, double) const;
};
