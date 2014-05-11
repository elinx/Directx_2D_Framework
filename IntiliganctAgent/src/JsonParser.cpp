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
		map->SetTileCountRow(ptree.get<int>("width"));
		map->SetTileCountColumn(ptree.get<int>("height"));
		map->SetTileWidth(ptree.get<int>("tilewidth"));
		map->SetTileHeight(ptree.get<int>("tileheight"));

		/* Taverse the json property tree and and get the layer information, like w/h, name,
		// Most importently, the data information */
		int layerCount = 0;
		boost::property_tree::ptree layerTree = ptree.get_child("layers");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, layerTree)
		{
				assert(v.first.empty()); // array elements have no names

				CMap::map_layer *maplayer = new CMap::map_layer;

				maplayer->name					= v.second.get<std::string>("name");
				maplayer->type					= v.second.get<std::string>("type");
				maplayer->width					= v.second.get<int>("width");
				maplayer->height				= v.second.get<int>("height");
				maplayer->x						= v.second.get<int>("x");
				maplayer->y						= v.second.get<int>("y");
				maplayer->visible				= v.second.get<bool>("visible");

				boost::property_tree::ptree datatree = v.second.get_child("data");

				BOOST_FOREACH(boost::property_tree::ptree::value_type& v, datatree)
				{
					maplayer->data.push_back(v.second.get<int>(""));
				}

				map->AddLayer(maplayer);

				++layerCount;
		}
		map->SetLayerCount(layerCount); /* Layer parser end */

		/* like the layer information, get the tileset information */
		int tilesetCount = 0;
		boost::property_tree::ptree tilesetTree = ptree.get_child("tilesets");
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, tilesetTree)
		{
				assert(v.first.empty()); // array elements have no names

				CMap::map_tilestet* tileset = new CMap::map_tilestet;

				tileset->image					= v.second.get<std::wstring>("image");
				tileset->name					= v.second.get<std::string>("name");
				tileset->img_width				= v.second.get<int>("imagewidth");
				tileset->img_height				= v.second.get<int>("imageheight");
				tileset->tile_width				= v.second.get<int>("tilewidth");
				tileset->tile_height			= v.second.get<int>("tileheight");
				tileset->firstGrid				= v.second.get<int>("firstgid");

				map->AddTileset(tileset);
				++tilesetCount;
		}
		map->SetTilesetCount(tilesetCount); /* Tileset parser end */
	}
	catch(std::exception& e) 
	{
		MessageBoxA(0, e.what(), "½âÎöµØÍ¼´íÎó", MB_OK);
		return false;
	}

	return true;
}