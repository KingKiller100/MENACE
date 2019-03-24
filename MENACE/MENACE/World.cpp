#include "iWorld.h"
#include <iostream>

void World::DrawMap()
{
	for (unsigned y = 0; y < rows; ++y)
	{
		for (unsigned x = 0; x < columns; ++x)
		{
			unsigned short offset = x + y * 3;

			if (y % 2 == 0 && y != 2)
			{
				if (x % 2 != 0)
					matrix[offset] = '|';
				else
					matrix[offset] = (y == 0 && x % 2 == 0) ? "X" + std::to_string(short(x*.5 + 1)) : "O" + std::to_string(short(x*.5 + 1));
			}
			else if (y % 2 == 0)
				matrix[offset] = x % 2 != 0 ?  "|" : std::to_string(short((x + y) * .5 + 3)) + " ";
			else
				matrix[offset] = x % 2 == 0 ? "--" : " ";
	
			std::cout << matrix[offset];
		}

		std::cout << "\n";
	}
}
