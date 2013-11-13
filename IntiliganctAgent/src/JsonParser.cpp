#include "JsonParser.h"

CJsonParser::CJsonParser()
{
}

CJsonParser::~CJsonParser()
{
}

bool CJsonParser::ReadFromFile(std::wstring wstrFilePath, CMap* map)
{
	std::ifstream	infile(wstrFilePath.c_str());

	return this->ReadFromStream(infile, map);
}

bool CJsonParser::ReadFromStream(std::istream& iStream, CMap* map)
{
	boost::property_tree::ptree ptree;
	boost::property_tree::read_json(iStream, ptree);
	
	try 
	{
		// Get the basic information
		map->SetMapTileCountW(ptree.get<int>("width"));
		map->SetMapTileCountH(ptree.get<int>("height"));
		map->SetTileWidth(ptree.get<int>("tilewidth"));
		map->SetTileHeight(ptree.get<int>("tileheight"));

		/* Taverse the json property tree and and get the layer information, like w/h, name,
		// Most importently, the data information */
		int layerCount = 0;
		boost::property_tree::ptree layerTree = ptree.get_child("layers");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, layerTree)
		{
				assert(v.first.empty()); // array elements have no names

				std::string name		= v.second.get<std::string>("name");
				std::string type		= v.second.get<std::string>("type");
				int	lw					= v.second.get<int>("width");
				int	lh					= v.second.get<int>("height");
				int	x					= v.second.get<int>("x");
				int	y					= v.second.get<int>("y");
				bool visible			= v.second.get<bool>("visible");

				boost::property_tree::ptree datatree = v.second.get_child("data");// Can not use "layers.data", why?
				std::vector<int>* data	= new std::vector<int>;
				BOOST_FOREACH(boost::property_tree::ptree::value_type& v, datatree)
				{
					data->push_back(v.second.get<int>(""));
				}

				//std::vector<int> tdata = v.second.get< std::vector<int> > ("data");
				//std::vector<int>* data	= new std::vector<int>(tdata); // copy here,, stupid any way.
				map->AddLayer(data, lw, lh, name, type, visible, x, y);
				++layerCount;
		}
		map->SetLayerCount(layerCount); /* Layer parser end */

		/* like the layer information, get the tileset information */
		int tilesetCount = 0;
		boost::property_tree::ptree tilesetTree = ptree.get_child("tilesets");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, tilesetTree)
		{
				assert(v.first.empty()); // array elements have no names

				std::string image		= v.second.get<std::string>("image");
				std::string name		= v.second.get<std::string>("name");
				int	iw					= v.second.get<int>("imagewidth");
				int	ih					= v.second.get<int>("imageheight");
				int	tw					= v.second.get<int>("tilewidth");
				int	th					= v.second.get<int>("tileheight");
				int firstgrid			= v.second.get<int>("firstgid");

				map->AddTileset(image, name, firstgrid, iw, ih, tw, th);
				++tilesetCount;
		}
		map->SetTilesetCount(tilesetCount); /* Tileset parser end */
	}
	catch(/*ptree_error &e*/...) 
	{
		return false;
	}

	return true;
}