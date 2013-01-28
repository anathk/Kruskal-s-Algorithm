//Zhengchao Tian
//edge.h
//Edge class contains edge informain. Each edge of graph is specified
//as 2 vertices and a weight.
#include <iostream>
using namespace std;

//Edge class
class edge
{
public:
	edge();
	edge(int, int, int);
	~edge();
	bool operator< (const edge &rhs) const;
	bool operator== (const edge &rhs) const;

	//Smaller vertex
	int vertex1;
	//Larger vertex
	int vertex2;
	//The weight of an edge
	int weight;
};

//Default constructor
edge::edge() : vertex1(-1), vertex2(-1), weight(-1)
{}

//Constructor
edge::edge(int v1, int v2, int w) : vertex1(v1), vertex2(v2), weight(w)
{}

//Destructor.
edge::~edge()
{
	vertex1 = -1;
	vertex2 = -1;
	weight = -1;
}

//Overload < operator, compare 2 edges by their weight.
bool edge::operator< (const edge &rhs) const
{
	return (weight < rhs.weight);
}

//Overload == operator for extra credit.
bool edge::operator== (const edge &rhs) const
{
	return (vertex1 == rhs.vertex1 && vertex2 == rhs.vertex2 && weight == rhs.weight);
}