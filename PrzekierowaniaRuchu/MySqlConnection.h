#pragma once

#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include "Logger.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <warning.h>
#pragma comment(lib,"mysqlcppconn.lib")
#pragma comment(lib,"libmysql.lib")

using namespace std;
using namespace sql;

class MySqlConnection
{
public:
	static MySqlConnection& getMySqlConnection()
	{
		static MySqlConnection singleton;
		return singleton;
	}

	void getMinMaxLatLon(string* resultTable);

	ResultSet* getBothEdgeEnds(int startIndex);
	Statement* createStatement();

	Connection* con;
	PreparedStatement* prep_stmt;
private:
	MySqlConnection();
	MySqlConnection(const MySqlConnection&);
	~MySqlConnection();
	string getFirstRowArgument(ResultSet* resultSet, string colName);
};
