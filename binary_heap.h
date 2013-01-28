//Zhengchao Tian
//binary_heap.h
//These codes are from textbook.
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

template <typename T>
class binary_heap
{
public:
	explicit binary_heap(int capacity = 100);
	
	bool isEmpty() const;
	const T &findMin() const;

	void insert(const T &x);
	void deleteMin();
	void deleteMin(T &minItem);
	void makeEmpty();
	int get_size() const;

private:
	int currentSize;
	vector<T> heap_vec;

	void buildHeap();
	void percolateDown(int hole);

};

//Default constructor of the heap.
template <typename T>
binary_heap<T>::binary_heap(int capacity) : heap_vec(capacity + 1), currentSize(0)
	{}

//Find the minimum value in the heap.
template <typename T>
const T &binary_heap<T>::findMin() const 
{
	if(isEmpty())
	{
		cout << "Binary heap is empty." << endl;
		exit(1);
	}
	return heap_vec[1];
}

//Insert item x, allowing duplicates.
template <typename T>
void binary_heap<T>::insert(const T &x)
{
	if(currentSize == heap_vec.size() - 1)
		heap_vec.resize(heap_vec.size() * 2);

	int hole = ++currentSize;
	for(; hole > 1 && x < heap_vec[hole/2]; hole /= 2)
		heap_vec[hole] = heap_vec[hole/2];
	heap_vec[hole] = x;
}

//this function for deleting minimum data from the heap
template <typename T>
void binary_heap<T>::deleteMin()
{
	if(isEmpty())
		throw exception();

	heap_vec[1] = heap_vec[currentSize--];
	percolateDown(1);

}

//this function for deleting minimum data from the heap and return deleted data.
template <typename T>
void binary_heap<T>::deleteMin(T &minItem)
{
	if(isEmpty())
		throw exception();

	minItem = heap_vec[1];
	heap_vec[1] = heap_vec[currentSize--];
	percolateDown(1);//call this function to make percolatedown

}

//PercolateDown method.
template <typename T>
void binary_heap<T>::percolateDown(int hole)
{
	int child;
	T temp = heap_vec[hole];

	for(; hole * 2 <= currentSize; hole = child)
	{
		child = hole * 2;
		if(child != currentSize && heap_vec[child + 1] < heap_vec[child])
			child++;
		if(heap_vec[child] < temp)
			heap_vec[hole] = heap_vec[child];
		else
			break;
	}
	heap_vec[hole] = temp;
}

//If the heap is empty, return true.
template <typename T>
bool binary_heap<T>::isEmpty() const
{
	return heap_vec.size() == 0;
}

//Get the size of heap.
template <typename T>
int binary_heap<T>::get_size() const
{
	return currentSize;
}

