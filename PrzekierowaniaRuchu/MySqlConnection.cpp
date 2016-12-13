#include "MySqlConnection.h"

MySqlConnection::MySqlConnection(): prep_stmt(nullptr)
{
	try
	{
		Driver* driver;

		driver = get_driver_instance();
		Logger::getLogger().Log(Logger::DEBUG, "Got driver instance MySqlServer");

		con = driver->connect("tcp://127.0.0.1:3306", "root", "1111");
		con->setSchema("przekierowaniaruchu");
		Logger::getLogger().Log(Logger::DEBUG, "Created connection to MySqlServer");
	}
	catch (sql::SQLException& e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		Logger::getLogger().Log(Logger::FATAL, "Failed in creating connection to MySqlServer");
	}
}

MySqlConnection::~MySqlConnection()
{
	Logger::getLogger().Log(Logger::DEBUG, "Called destructor for connection to MySqlServer");
}

string MySqlConnection::getFirstRowArgument(ResultSet* resultSet, string colName)
{
	try
	{
		resultSet->next();
		return resultSet->getString(colName);
	}
	catch (...)
	{
		auto eptr = std::current_exception();

		Logger::getLogger().Log(Logger::ERROR, "ERROR in getFirstRowArgument");

		return "-1";
	}
}

void MySqlConnection::getMinMaxLatLon(string* resultTable)
{
	Logger::getLogger().Log(Logger::TRACE, "Started function getting max and min values of lat and long columns from node table");
	try
	{
		Statement* statm = getMySqlConnection().con->createStatement();
		ResultSet* resultSet = nullptr;

		resultSet = statm->executeQuery("SELECT MAX(lat) from node");
		resultTable[0] = getFirstRowArgument(resultSet, "MAX(lat)");

		resultSet = statm->executeQuery("SELECT MIN(lat) from node");
		resultTable[1] = getFirstRowArgument(resultSet, "MIN(lat)");

		resultSet = statm->executeQuery("SELECT MIN(lon) from node");
		resultTable[2] = getFirstRowArgument(resultSet, "MIN(lon)");

		resultSet = statm->executeQuery("SELECT MAX(lon) from node");
		resultTable[3] = getFirstRowArgument(resultSet, "MAX(lon)");
	}
	catch (sql::SQLException e)
	{
		cout << e.what();
		Logger::getLogger().Log(Logger::ERROR, "ERROR IN getMinMaxLatLon function");
	}
}

Statement* MySqlConnection::createStatement()
{
	auto statement = getMySqlConnection().con->createStatement();
	return statement;
}

ResultSet* MySqlConnection::getBothEdgeEnds(int startIndex) const
{
	auto* statement = createStatement();
	ResultSet* result;

	string query = "SELECT e.id, n1.lat as latFrom, n1.lon as lonFrom, n2.lat as latTo, n2.lon as lonTo FROM przekierowaniaruchu.edge as e left join node as n1	on e.fromId = n1.id	left join node as n2 on e.toId = n2.id order by e.id limit ";
	query += to_string(startIndex);
	query += " , 1000";

	return statement->executeQuery(query);
}
