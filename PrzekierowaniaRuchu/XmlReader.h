#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <memory>

#include "rapidXml\rapidxml.hpp"
#include "rapidXml\rapidxml_print.hpp"

#include <boost/algorithm/string.hpp>

#include "Logger.h"
#include "MySqlConnection.h"

using namespace std;
using namespace rapidxml;

void readXmlFile(char* nazwa_pliku);
void addLengthToEdges();
