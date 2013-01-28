//Zhengchao Tian
//disjoint_sets.h
//These codes are from textbook.
#include <vector>
using namespace std;

//Disjoint set class.
class disjoint_sets
{
  public:
    explicit disjoint_sets(int numElements);

    //int find(int x) const;
    int find(int x);
    void unionSets(int root1, int root2);


  private:
    vector<int> s;
};

//This is constructor of disjoint sets.
disjoint_sets::disjoint_sets(int numElements) : s(numElements)
{
    for(int i = 0; i < s.size( ); i++)
        s[i] = -1;
}

//Union two disjoint sets.
//For simplicity, we assume root1 and root2 are distinct
//and represent set names.
void disjoint_sets::unionSets(int root1, int root2)
{
	if(find(root1) == find(root2))
	{
		cout << "Failed to union sets." << endl;
		exit(1);
	}
    if( s[root2] < s[root1] )   // root2 is deeper
        s[root1] = root2;        // Make root2 new root
    else
    {
        if(s[root1] == s[root2])
            s[root1]--;          // Update height if same
        s[root2] = root1;        // Make root1 new root
    }
}


//Perform a find with path compression.
//Return the set containing x.
int disjoint_sets::find(int x)
{
    if(s[x] < 0)
        return x;
    else
        return s[x] = find(s[x]);
}

