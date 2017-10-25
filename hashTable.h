
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// Specification of the class
using namespace std;
#include <iostream>
#include<string>

template <class keyType,class dataType>
class hashTable
{
public:

	// Member Functions
	hashTable(int nelements = 20, float coefficeint = .5);		// Constructor
	~hashTable();						// Destructor

	// Functions Prototype Definitions
	void emptyTable();
	bool tableIsEmpty() const;
	bool tableIsFull() const;
	int  size() const;
	bool insert(const keyType &, const dataType &);
	bool search(const keyType &);
	bool retrieveData(const keyType &, dataType &d);

	///////////////////////////////////////////////
	bool Update(const keyType &, const dataType&);

	void Traverse(keyType* &, dataType *&) const;

	/////////////////////////////////////////////////

private:

	// Slot Class
	class slot
	{
		public:
		keyType key; 		// key 
		dataType data;		// Data		
	}; // end of class slot declaration

	slot *T;							// Pointer to Storage Array
	int h;								// Index to a slot
	int MaxSize, csize;					// Maximum and Current Sizes
	keyType Empty;						// empty symbol
	float alpha;

	// Private Member function
	int hash(const keyType &) const;
	string convertostring(const string &k) const;
	string convertostring(const int &k) const;
};
#endif 
#include "hashtable.cpp"
