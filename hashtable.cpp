#include <iostream>
#include <string>
using namespace std;

// Constructor with argument, size is nelements, default is 11
template <class keyType,class dataType>
hashTable<keyType, dataType>::hashTable(int nelements, float coefficeint)
{
	MaxSize = nelements;
	alpha=coefficeint;
	T = new slot[int(MaxSize/alpha)]; 
	h = -1;
	csize = 0,
	emptyTable();
}

// Destructor
template <class keyType,class dataType>
hashTable<keyType,dataType>::~hashTable()
{
	delete[]T;
}

// Empty all slots
template <class keyType,class dataType>
void hashTable<keyType,dataType>::emptyTable()
{
	Empty = int("EMPTY");
	for (int i = 0; i < MaxSize/alpha; i++) 
	T[i].key = Empty;
	h = -1; 
	csize = 0;
}

// return True if table is empty
template <class keyType,class dataType>
bool hashTable<keyType,dataType>::tableIsEmpty() const
{
	return (csize == 0);
}

// return True if table is full
template <class keyType,class dataType>
bool hashTable<keyType,dataType>::tableIsFull() const
{
	return (csize == MaxSize);
}

// to return the current occupancy of the table
template <class keyType,class dataType>
int hashTable<keyType,dataType>::size() const
{
	return csize;
}

// insert key and data at a hashed slot
template <class keyType,class dataType>
bool hashTable<keyType,dataType>::insert(const keyType &k, const dataType &d)
{
	if (!tableIsFull()&& k!=Empty)
	{
		h = hash(k);
		
		float x=h/alpha;
		
		h=x;
		
		while (T[h].key != Empty)
		{
			h = (h + 1) % int(MaxSize/alpha);
		}	
		T[h].key = k; 
		T[h].data = d; 
		csize++;
		
		return true;
	}
	return false;
}

// Search the table for the slot that matches key. 
// If found, return True, set current position to slot
template <class keyType,class dataType>
bool hashTable<keyType,dataType>::search(const keyType &k)
{

	if (!tableIsEmpty())
	{
		h = hash(k); 
		float x=h/alpha;
		h = x;
		int start = h;
		while (true)
		{
			if (T[h].key == Empty)
			return false;
			if (k == T[h].key) 
			return true;
			
			h = (h + 1) % int(MaxSize/alpha);
			if (h == start) return false;
		}
	}
	else return false;
}

template <class keyType,class dataType>
bool hashTable<keyType,dataType>::Update(const keyType & k, const dataType& d)
{ 
	if(search(k))
	{
		T[h].data=d;
		return true;
	}
	return false;
}

template <class keyType,class dataType>
void hashTable<keyType,dataType>:: Traverse(keyType* & k, dataType *& d) const
{
	k=new keyType[csize];
	d=new dataType[csize];
	float x=MaxSize/alpha;
	
	int i=0, count=0;
	while(i<x)
	{
		if(T[i].key!=Empty)
		{
			k[count]=T[i].key;
			d[count]=T[i].data;
			
			count++;
		}
		
		i++;
	}

}

// Retrieve the data part of the current slot
template <class keyType,class dataType>
bool hashTable<keyType,dataType>::retrieveData(const keyType & k, dataType &d) 
{
	if (search(k)) 
		{
		d= T[h].data;
		return true;
		}
	else false;
}

// Private Hashing Function
template <class keyType,class dataType>
int hashTable<keyType,dataType>::hash(const keyType &k) const
{
	int counter = 0;
	string S = convertostring(k);
	
	for (int i = 0; i < S.length(); i++)
		counter += int(S[i]);
	return counter% MaxSize;

}

template <class keyType, class dataType>
string hashTable<keyType, dataType>::convertostring(const string &k) const
{
	return k;
}

template <class keyType, class dataType>
string hashTable<keyType, dataType>::convertostring(const int &k) const
{

	return to_string(k);
}
