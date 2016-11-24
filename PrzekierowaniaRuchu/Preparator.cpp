#include "Preparator.h"

Preparator::Preparator(int partitionX, int partitionY) {
	setPartitions(partitionX, partitionY);
	calculateLengthOfEdges();
}

Preparator::~Preparator() {
}

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 9)
{
	std::ostringstream out;
	out << std::setprecision(n) << a_value;
	return out.str();
}

void Preparator::setPartitions(int amountInRow, int amountInColumn) {
	string *minMaxLatLon = new string[4];
	MySqlConnection::getMySqlConnection().getMinMaxLatLon(minMaxLatLon);

	long double roznicaLat = (stod(minMaxLatLon[0]) - stod(minMaxLatLon[1])) / amountInColumn;
	long double roznicaLon = (stod(minMaxLatLon[3]) - stod(minMaxLatLon[2])) / amountInRow;
	long double downLat = stod(minMaxLatLon[1]);
	long double downLong = stod(minMaxLatLon[2]);

	string sql;
	int partitionNumber;
	Statement *statm = MySqlConnection::getMySqlConnection().con->createStatement();

	for (int i = 0; i < amountInColumn; i++) {

		downLong = stod(minMaxLatLon[2]);

		for (int j = 0; j < amountInRow; j++) { 
			sql = "UPDATE node set partitionNumber = ";
			sql += to_string_with_precision((i*amountInRow) + j);
			sql += " WHERE lat >= ";
			sql += to_string_with_precision(downLat);
			sql += " AND lat <= ";
			sql += to_string_with_precision(downLat + roznicaLat);
			sql += " AND lon >= ";
			sql += to_string_with_precision(downLong);
			sql += " AND lon <= ";
			sql += to_string_with_precision(downLong + roznicaLon);

			statm->executeUpdate(sql);

			downLong += roznicaLon;
		}
		downLat += roznicaLat;
	}
}	

void Preparator::calculateLengthOfEdges() {
	Statement *statement = MySqlConnection::getMySqlConnection().con->createStatement();
	Statement *statement2 = MySqlConnection::getMySqlConnection().con->createStatement();
	Statement *statement3 = MySqlConnection::getMySqlConnection().con->createStatement();
	Statement *statement4 = MySqlConnection::getMySqlConnection().con->createStatement();
	string sql = "";
	ResultSet *node1;
	ResultSet *node2;
	ResultSet *edges = statement->executeQuery("Select * from edge");

	while (edges->next()) {
		sql = "Select * from node WHERE id = ";
		sql += to_string_with_precision(edges->getInt("fromId"));
		node1 = statement2->executeQuery(sql);
		node1->next();

		sql = "Select * from node WHERE id = ";
		sql += to_string_with_precision(edges->getInt("toId"));
		node2 = statement3->executeQuery(sql);
		node2->next();
		
		sql = "Update edge set length = ";
		sql += to_string_with_precision(measure(node1->getDouble("lat"), node1->getDouble("lon"), node2->getDouble("lat"), node2->getDouble("lon")));
		sql += " WHERE id = ";
		sql += to_string_with_precision(edges->getInt("id"));

		node1 = nullptr;
		node2 = nullptr;
		statement4->executeUpdate(sql);
		sql = "";
	}
}

double Preparator::measure(double lat1, double lon1, double lat2, double lon2) {
	double R = 6378.137; // Radius of earth in KM
	double dLat = lat2 * M_PI / 180 - lat1 * M_PI / 180;
	double dLon = lon2 * M_PI / 180 - lon1 * M_PI / 180;
	double a = sin(dLat / 2) * sin(dLat / 2) +
		cos(lat1 * M_PI / 180) * cos(lat2 * M_PI / 180) *
		sin(dLon / 2) * sin(dLon / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	double d = R * c;
	return d * 1000; // meters
}