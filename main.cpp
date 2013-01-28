//Zhengchao Tian
//main.cpp
//This program reads in a graph in Graphviz dot/neato format and 
//prints out the Minimum Spanning Tree in Graphviz format using Kruskal's Algorithm.
#include "binary_heap.h"
#include "edge.h"
#include "disjoint_sets.h"
#include <fstream>
#include <string>
using namespace std;

int main()
{
	cout << "CPS 350 Assignment 5 for Zhengchao Tian." << endl;
	ifstream ins;
	ofstream outs;
	string input_name;
	string output_name;
	int num_vertices;
	binary_heap<edge> myHeap;
	binary_heap<edge> entire_heap;
	binary_heap<edge> output_heap;
	edge myEdge;
	vector<int> numbers;

	//Prompt user for the name of input file.
	cout << "Please enter the name of input file: ";
	cin >> input_name;
	ins.open(input_name);
	//Check for open failure.
	if(ins.fail())
	{
		cout << "Error in openning file." << endl;
		exit(1);
	}

	string str;
	//For numbers in the input file.
	string num_string = "";
	//Read input file
	while(!ins.eof())
	{	
		str = ins.get();
		//Read numbers.
		if(str <= "9" && str >= "0")
			num_string += str;
		if(num_string != "" && (str > "9" || str < "0"))
		{
			//Convert string into int.
			numbers.push_back(atoi(num_string.c_str()));
			num_string = "";
		}
	}
	//This is number of vertices in the graph.
	num_vertices = numbers[0];

	//Use disjoint_sets to check if 2 vertices are in same set.
	disjoint_sets graph_set(num_vertices);

	//Insert edges into binary_heap.
	for(int i = 0; i < numbers.size() / 3; i++)
	{
		myEdge.vertex1 = numbers[i*3 + 1];
		myEdge.vertex2 = numbers[i*3 + 2];
		myEdge.weight = numbers[i*3 + 3];
		myHeap.insert(myEdge);
		entire_heap.insert(myEdge);
	}
	
	//Find smallest edge, if two vertices are not in same set, union these 2 sets.
	while(myHeap.get_size() > 0)
	{
		myHeap.deleteMin(myEdge);
		if(graph_set.find(myEdge.vertex1) != graph_set.find(myEdge.vertex2))
		{
			graph_set.unionSets(graph_set.find(myEdge.vertex1), graph_set.find(myEdge.vertex2));
			//Insert this edge into output edge.
			output_heap.insert(myEdge);
		}
	}
	cout << endl;
	cout << num_vertices << " vertices in this graph." << endl;
	cout << "\nSuccessfully found the Minimum Spanning Tree." << endl;
	//Prompt user for name of output file.
	cout << "\nPlease enter the name for output file: ";
	cin >> output_name;
	outs.open(output_name);
	//Check the open failure.
	if(outs.fail())
	{
		cout << "Fail to open output file." << endl;
		exit(1);
	}
	cout << "\nPrinting the Minimum spanning tree into output file now." << endl << endl;

	//Output graph infomation into output file.
	outs << "// " << num_vertices << " vertices" << endl;
	outs << "graph G {" << endl;
	while(entire_heap.get_size() > 0)
	{
		bool in_heap = false;
		entire_heap.deleteMin(myEdge);
		edge temp_edge;
		binary_heap<edge> temp_heap = output_heap;
		while(temp_heap.get_size() > 0)
		{
			temp_heap.deleteMin(temp_edge);
			if(temp_edge == myEdge)
				in_heap = true;
		}
		//Mark the minimum spanning tree edges with red bold line.
		if(in_heap)
		{
			outs << "   " << myEdge.vertex1 << " -- " << myEdge.vertex2;
			outs << " [style=bold,color=red,label=" << myEdge.weight << "];" << endl;
		}
		//The rest of the graph.
		else
		{
			outs << "   " << myEdge.vertex1 << " -- " << myEdge.vertex2;
			outs << " [label=" << myEdge.weight << "];" << endl;
		}
	}
	outs << "}" << endl;

	//Close files.
	outs.close();
	ins.close();
	return 0;
}

