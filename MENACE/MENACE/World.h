#pragma once
#include <string>
#include <map>

class iWorld
{
public:
	iWorld(const unsigned columns, const unsigned rows);
	virtual ~iWorld() = default;

	virtual void DrawMap();

	virtual bool ValidPiece(const int piece) const						{ return piece >= 1 && piece <= 3; }

	bool ValidLocation(const int location) const						{ return location >= 1 && location <= (rows - 2) * (columns - 2) ; }

	bool MoveableLocation(const int location) const						{ return matrix.find(location) != matrix.end(); }

private:
	unsigned rows;
	unsigned columns;
	std::map<unsigned short, std::string> matrix;
};
