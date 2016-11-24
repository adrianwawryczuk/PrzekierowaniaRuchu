#include "XmlReader.h"

inline char * stringToChar(string & s) {
	size_t N = s.length();
	char * out = new char[N + 1];
	::copy(s.c_str(), (s.c_str() + N - 1), out); // (2)
	return out;
}

char * plikDoChar(const char * nazwa_pliku) {
	ifstream plik(nazwa_pliku);
	if (plik.bad()) {
		Logger::getLogger().Log(Logger::ERROR, "Plik nie istnieje lub nie masz do niego praw!");
		exit(-1);
	}

	filebuf * pbuf = plik.rdbuf();
	streamoff wielkosc_pliku = pbuf->pubseekoff(0, ios::end, ios::in);
	plik.seekg(0);

	char * wyjscie = new char[(int)wielkosc_pliku + 1];

	plik.read(wyjscie, wielkosc_pliku);

	return wyjscie;
}

void writeAllNodesFromOSM(xml_node <> * korzen) {

	Logger::getLogger().Log(Logger::DEBUG, "Starting writeAllNodesFromOSM");

	sql::PreparedStatement  *prep_stmt = MySqlConnection::getMySqlConnection().con->prepareStatement("Insert into node(id, lat, lon) values(?, ?, ?)");
	for (xml_node <> * galazka = korzen->first_node(); galazka; galazka = galazka->next_sibling()) {

		if (boost::iequals(galazka->name(), "node")) {
			for (xml_attribute <>* atrybut = galazka->first_attribute(); atrybut; atrybut = atrybut->next_attribute()) {

				if (boost::iequals(atrybut->name(), "id"))
					prep_stmt->setBigInt(1, atrybut->value());
				else if (boost::iequals(atrybut->name(), "lat"))
					prep_stmt->setString(2, atrybut->value());
				else if (boost::iequals(atrybut->name(), "lon"))
					prep_stmt->setString(3, atrybut->value());
			}

			prep_stmt->executeQuery();
		}
	}

	prep_stmt = nullptr;
}

void addAllLengthToEdges(xml_node <> * korzen) {

	Logger::getLogger().Log(Logger::DEBUG, "Starting addAllLengthToEdges");

	sql::Statement  *prep_stmt = MySqlConnection::getMySqlConnection().con->createStatement();
	for (xml_node <> * galazka = korzen->first_node(); galazka; galazka = galazka->next_sibling()) {
		string sql = "Update edge set length = ";
		string temp = " WHERE fromId = ";
		if (boost::iequals(galazka->name(), "edge")) {

			for (xml_attribute <>* atrybut = galazka->first_attribute(); atrybut; atrybut = atrybut->next_attribute()) {
				if (boost::iequals(atrybut->name(), "from")) {
					temp += atrybut->value();
					temp += " AND toId = ";
				}
				else if (boost::iequals(atrybut->name(), "to")) {
					temp += atrybut->value();
				}
			}

			for (xml_attribute <>* atrybut = galazka->first_node()->first_attribute(); atrybut; atrybut = atrybut->next_attribute()) {
				if (boost::iequals(atrybut->name(), "length")) {
					
					sql += atrybut->value();
					sql += temp;
					prep_stmt->execute(sql);
				}
			}
		}
	}

	prep_stmt = nullptr;
}

void checkAllWays(xml_node <> * korzen) {
	Logger::getLogger().Log(Logger::DEBUG, "Starting writeAllEdgesFromOSMWays");

	//sql::PreparedStatement  *prep_stmt = MySqlConnection::getMySqlConnection().con->prepareStatement("Insert into way(id, from, to) values(?, ?, ?)");

	int all = 0, a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0, j = 0, k = 0, l = 0, withoutTags = 0, m = 0, n = 0;
	int o = 0, p = 0, r = 0, s = 0, t = 0;
	string restofnames = "", tempRestOfNames = "";
	bool foundTag = false, foundExpectedName = false;

	xml_node <> * parent = nullptr;
	for (xml_node <> * galazka = korzen->first_node(); galazka; galazka = galazka->next_sibling()) {

		if (boost::iequals(galazka->name(), "way")) {

			all++;

			for (xml_node <> * galazeczka = galazka->first_node(); galazeczka; galazeczka = galazeczka->next_sibling()) {

				if (boost::iequals(galazeczka->name(), "tag")) {
					foundExpectedName = false;
					foundTag = true;
					for (xml_attribute <>* atrybut = galazeczka->first_attribute(); atrybut; atrybut = atrybut->next_attribute()) {

						if (boost::iequals(atrybut->name(), "k") && !foundExpectedName) {

							if (boost::iequals(atrybut->value(), "highway")) {
								a++;
								foundExpectedName = true;
							}

							else if (boost::iequals(atrybut->value(), "amenity")) {
								b++;
								foundExpectedName = true;
							}

							else if (boost::iequals(atrybut->value(), "waterway")) {
								c++;
								foundExpectedName = true;
							}

							else if (boost::iequals(atrybut->value(), "leisure")) {
								d++;
								foundExpectedName = true;
							}

							else if (boost::iequals(atrybut->value(), "railway")) {
								e++;
								foundExpectedName = true;
							}

							else if (boost::iequals(atrybut->value(), "source:building") || boost::iequals(atrybut->value(), "building")) {
								f++;
								foundExpectedName = true;
							}

							else if (boost::iequals(atrybut->value(), "landuse")) {
								g++;
								foundExpectedName = true;
							}

							else if (boost::iequals(atrybut->value(), "boundary")) {
								h++;
								foundExpectedName = true;
							}

							else if (boost::iequals(atrybut->value(), "natural")) {
								i++;
								foundExpectedName = true;
							}

							else if (boost::iequals(atrybut->value(), "barrier")) {
								k++;
								foundExpectedName = true;
							}
							else if (boost::iequals(atrybut->value(), "power")) {
								l++;
								foundExpectedName = true;
							}
							else if (boost::iequals(atrybut->value(), "aeroway")) {
								m++;
								foundExpectedName = true;
							}
							else if (boost::iequals(atrybut->value(), "note")) {
								n++;
								foundExpectedName = true;
							}
							else if (boost::iequals(atrybut->value(), "service")) {
								o++;
								foundExpectedName = true;
							}
							else if (boost::iequals(atrybut->value(), "place")) {
								p++;
								foundExpectedName = true;
							}
						}
					}
				}
			}


			if (!foundTag)
				withoutTags++;

			foundTag = false;
			//prep_stmt->executeQuery();
		}
	}
	Logger::getLogger().Log(Logger::DEBUG, "Wszystkich " + to_string(all));
	Logger::getLogger().Log(Logger::DEBUG, "Highway " + to_string(a));
	Logger::getLogger().Log(Logger::DEBUG, "Amenity " + to_string(b));
	Logger::getLogger().Log(Logger::DEBUG, "Waterway " + to_string(c));
	Logger::getLogger().Log(Logger::DEBUG, "Leisure " + to_string(d));
	Logger::getLogger().Log(Logger::DEBUG, "Railway " + to_string(e));
	Logger::getLogger().Log(Logger::DEBUG, "Building " + to_string(f));
	Logger::getLogger().Log(Logger::DEBUG, "Landuse " + to_string(g));
	Logger::getLogger().Log(Logger::DEBUG, "Boundary " + to_string(h));
	Logger::getLogger().Log(Logger::DEBUG, "Natural " + to_string(i));
	Logger::getLogger().Log(Logger::DEBUG, "Barrier " + to_string(k));
	Logger::getLogger().Log(Logger::DEBUG, "Power " + to_string(l));
	Logger::getLogger().Log(Logger::DEBUG, "aeroway " + to_string(m));
	Logger::getLogger().Log(Logger::DEBUG, "note " + to_string(n));
	Logger::getLogger().Log(Logger::DEBUG, "service " + to_string(o));
	Logger::getLogger().Log(Logger::DEBUG, "place " + to_string(o));

	Logger::getLogger().Log(Logger::DEBUG, "Not expected " + to_string(j));
	Logger::getLogger().Log(Logger::DEBUG, "Without tags " + to_string(withoutTags));
	Logger::getLogger().Log(Logger::DEBUG, "Pozostalo nie znalezionych  " + to_string(all - (a + b + c + d + e + f + g + h + i + k + l + withoutTags + m + n + o + p)));
	Logger::getLogger().Log(Logger::FATAL, "Nazwy  " + restofnames);
	//prep_stmt = nullptr;
}

bool findTags(xml_node <> * galazka, sql::PreparedStatement *prepared_stmt) {
	
	bool isHighway = false;

	//Czyszczenie ustawianych tutaj wartosci z poprzednich commitow
	prepared_stmt->setInt(4, 0);
	prepared_stmt->setString(3, "");

	for (xml_node <> * galazeczka = galazka->first_node(); galazeczka; galazeczka = galazeczka->next_sibling()) {
		if (boost::iequals(galazeczka->name(), "tag")) {

			//Po jego atrybutach szukamy atrybutu okreslajacego czy jest to droga 
			for (xml_attribute <>* atrybut = galazeczka->first_attribute(); atrybut; atrybut = atrybut->next_attribute()) {

				//Jesli atrybut to k
				if (boost::iequals(atrybut->name(), "k")) {

					//Jesli tak opisuje typ drogi
					if (boost::iequals(atrybut->value(), "highway")) {

						xml_attribute <>* v_attr = atrybut->next_attribute();

						if (boost::iequals(v_attr->name(), "v")) {
							isHighway = true;
							prepared_stmt->setString(3, v_attr->value());
						}

						v_attr = nullptr;
					}
					else if (boost::iequals(atrybut->value(), "oneway")) {

						xml_attribute <>* v_attr = atrybut->next_attribute();

						if (boost::iequals(v_attr->name(), "v")) {
							if (boost::iequals(v_attr->value(), "true") ||
								boost::iequals(v_attr->value(), "yes") ||
								boost::iequals(v_attr->value(), "1")) {

								prepared_stmt->setInt(4, 1);
							}
							else if (boost::iequals(v_attr->value(), "-1")) {
								prepared_stmt->setInt(4, -1);
							}
							else {
								prepared_stmt->setInt(4, 0);
							}
						}

						v_attr = nullptr;
					}
				}
			}
		}
	}

	return isHighway;
}

void writeAllEdgesFromOSMWays(xml_node <> * korzen) {

		Logger::getLogger().Log(Logger::DEBUG, "Starting writeAllEdgesFromOSMWays");

		//Utworzenie prepared statesment
		sql::PreparedStatement  *prepared_stmt = 
			MySqlConnection::getMySqlConnection().con->
			prepareStatement("INSERT INTO edge (fromId, toId, typeCol, directionCol, length) VALUES (?, ?, ?, ?, ?)");
																				
		bool toExecute = false;

		//Petla przechodzaca po wszystkich wezlach zaraz po glownym
		for (xml_node <> * galazka = korzen->first_node(); galazka; galazka = galazka->next_sibling()) {

			//Jesli wezel to way bedziemy na podstawie niego tworzyc krawedzie
			if (boost::iequals(galazka->name(), "way")) {

				//Sprawdzamy czy way to droga o typie highway
				if (findTags(galazka, prepared_stmt)) {

					//Potrzebujemy pary wezlow do stworzenia krawedzi
					xml_node <> * next_galazeczka;

					//W wezle way skaczemy po jego dzieciach
					for (xml_node <> * galazeczka = galazka->first_node(); galazeczka; galazeczka = galazeczka->next_sibling()) {

						next_galazeczka = galazeczka->next_sibling();

						//Jesli dziecko to wezel nd = node  
						//i jesli nastepne dziecko istnieje
						//jesli nastepne dziecko to nd
						if (boost::iequals(galazeczka->name(), "nd") &&
							next_galazeczka &&
							boost::iequals(next_galazeczka->name(), "nd")) {

							//Po atrybutach pierwszego dziecka szukamy atrybutu ref = referencji do id NODE
							for (xml_attribute <>* atrybut = galazeczka->first_attribute(); atrybut; atrybut = atrybut->next_attribute()) {

								//Jesli atrybut to ref
								if (boost::iequals(atrybut->name(), "ref")) {
									prepared_stmt->setBigInt(1, atrybut->value());
								}
							}

							//Po atrybutach drugiego dziecka szukamy atrybutu ref = referencji do id NODE
							for (xml_attribute <>* atrybut = next_galazeczka->first_attribute(); atrybut; atrybut = atrybut->next_attribute()) {

								//Jesli atrybut to ref
								if (boost::iequals(atrybut->name(), "ref")) {
									toExecute = true;
									prepared_stmt->setBigInt(2, atrybut->value());
								}
							}
						}

						if (toExecute) {
							prepared_stmt->executeUpdate();
						}

						toExecute = false;
					}
					next_galazeczka = nullptr;
				}
			}
		}

		prepared_stmt = nullptr;
}

void deleteUnusedNodes() {
	Logger::getLogger().Log(Logger::DEBUG, "Deleting unused nodes");

	sql::Statement *statesment = MySqlConnection::getMySqlConnection().con->createStatement();

	statesment->executeQuery("delete FROM przekierowaniaruchu.node where id not in (select fromId from edge) and id not in (select toId from edge)");
}

void readXmlFile(char* nazwa_pliku) {

	Logger::getLogger().Log(Logger::DEBUG, "Starting to read xml file");

	auto_ptr < char > zawartosc_pliku(plikDoChar(nazwa_pliku));

	xml_document <> dokument;
	try {
		dokument.parse < 0 >(zawartosc_pliku.get());
	}
	catch (parse_error p) {
		p.what();
	}

	xml_node <> * korzen = dokument.first_node();

	Logger::getLogger().Log(Logger::DEBUG, "Got root of xml");

	writeAllNodesFromOSM(korzen);
	checkAllWays(korzen);
	writeAllEdgesFromOSMWays(korzen);
	deleteUnusedNodes();
	addLengthToEdges();

	dokument.clear();
}

void addLengthToEdges() {
	Logger::getLogger().Log(Logger::DEBUG, "Starting to read xml file");

	auto_ptr < char > zawartosc_pliku(plikDoChar("./wroclaw.net.xml"));

	xml_document <> dokument;
	try {
		dokument.parse < 0 >(zawartosc_pliku.get());
	}
	catch (parse_error p) {
		p.what();
	}

	xml_node <> * korzen = dokument.first_node();

	Logger::getLogger().Log(Logger::DEBUG, "Got root of xml");

	addAllLengthToEdges(korzen);

	dokument.clear();
}


