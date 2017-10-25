#ifndef BIN_TREE_H
#define BIN_TREE_H

//#include <vector>

#include <vector>
using namespace std;

template <class keyType, class dataType>
class BinaryTree
{
public:	
	//constructor
	BinaryTree();

	~BinaryTree();
	//Insert Fn
	bool insert(const keyType &, const dataType &);

	// CHECK IF THE TREE IS EMPTY
	bool empty() const;

	// SEARCH FOR A KEY IN THE TREE
	bool search(const keyType &) const;

	// RETRIEVE DATA FOR A GIVEN KEY
	bool retrieve(const keyType &, dataType &) const;
	
	//Gets the number of total nodes
	int TotalNodes();
	
	//Gets the number of internal nodes
	int InternalNodes();
	
	//Gets the number of leaves
	int Leaves();
	
	//Gets the hight of the tree
	int height();
	
	//Gets the minimum in the tree
	void MinNode(keyType &);
	
	//Gets the maximum in the tree
	void MaxNode(keyType &);
	
	// TRAVERSE A TREE
    void traverse(vector<keyType>& , vector<dataType>&) const;
	// Iterative Pre-order Traversal
	void preorder (vector<keyType>&, vector<dataType>&) const;
	// Iterative Level-order Traversal
	void levelorder (vector<keyType>&, vector<dataType>&) const;
	// GRAPHIC OUTPUT
  //  void graph() const;
	// REMOVE AN ELEMENT FROM THE TREE
    void remove (keyType &);


private:
	// Node Class
	class treeNode
	{
	public:
		keyType key; 		// key 
		dataType data;		// Data
		treeNode *left;		// left subtree	       
		treeNode *right;	// right subtree
		
	/*	treeNode()
		{
			left=NULL;
			right=NULL;
		}
		*/
	}; // end of class treeNode declaration

	typedef treeNode* NodePointer;
	NodePointer root;

	// Inserts an item in a subtree
	bool insert2(NodePointer&, const keyType &, const dataType &);
	// Searches a subtree for a key
	bool search2(NodePointer, const keyType &) const;
	// Searches a subtree for a key and retrieves data
	bool retrieve2(NodePointer, const keyType &, dataType &) const;
	//Pub Functions
	int TotalNodesPrivate(NodePointer);
	int InternalNodesPrivate(NodePointer);
	int LeavesPrivate(NodePointer);
	int heightPrivate(NodePointer);
	void MinNode(NodePointer,  keyType &);
	void MaxNode(NodePointer,keyType &);
	int max(int, int);
	
	// Traverses a subtree
	void traverse2 (NodePointer, vector<keyType>&, vector<dataType>&) const;
	// Graphic output of a subtree
//	void graph2 ( int , NodePointer ) const;
	// LOCATE A NODE CONTAINING ELEMENT AND ITS 
	// PARENT
    void parentSearch( const keyType &, bool &, NodePointer &,	NodePointer &) const;
	

};
#include "binaryTree.cpp"

#endif // BIN_TREE_H
