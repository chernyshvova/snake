#include "stdafx.h"
#include "ContentConstructorUtils.h"
#include "GameConfig.h"

std::vector<std::string> game::createBorderMap(const size_t maxWith, const size_t maxHeight)
{
	std::string emptyLine = std::string(maxWith, config::MAP_EMPTY_SYMB);
	std::vector<std::string> resultMap(maxHeight, emptyLine);

	for (int i = 0; i < maxHeight; ++i)
	{
		for (int j = 0; j < maxWith; ++j)
		{
			if (i == 0 || i == maxHeight - 1)
			{
				resultMap[i][j] = (config::BORDER_SYMB_HORISONTAL);
			}
			else if (j == 0 || j == maxWith - 1)
			{
				resultMap[i][j] = (config::BORDER_SYMB_VERTICAL);
			}
			else
			{
				resultMap[i][j] = (config::MAP_EMPTY_SYMB);
			}
		}
	}

	return resultMap;
}
