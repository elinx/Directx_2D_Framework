#pragma once

#include <string>

class CTile {
public:
	CTile();
	~CTile();

private:
	//std::wstring	m_wstrTilePath;		// The path of the tile
	//int				m_iWidth;
	//int				m_iHeight;
	int				m_iLayerIndex;		// Which layer the tile is in
	int				m_iTileIndex;		// Index to the tile in the map
};