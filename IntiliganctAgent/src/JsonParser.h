#pragma once

// Headers needed to parse the json format file
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
//#include <boost/date_time.hpp>
#include "Map.h"
#include <string>

class CJsonParser {
public:
	CJsonParser();
	~CJsonParser();

	bool ReadFromFile(std::wstring wstrFilePath, CMap* map);// Read information from json file
	bool ReadFromStream(std::istream& iStream, CMap* map);	// Read information from a spefic stream, like file stream, string stream and io stream
};