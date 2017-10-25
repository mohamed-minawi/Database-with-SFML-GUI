#include <iostream>
#include <iomanip>
#include <vector>
#include "Stackt.h"
#include "Deque.h"

using namespace std;

// constructor - create an empty tree
template <class keyType, class dataType>
BinaryTree<keyType, dataType>::BinaryTree()
{
	root = NULL;
}

///////////////////////////////////////////////////////////////
template <class keyType, class dataType>
BinaryTree<keyType, dataType>::~BinaryTree()
{
	if (root != NULL) {
		while (root != NULL && (root->left != NULL || root->right != NULL))
		{
			if (root->left != NULL)
				remove(root->left->key);
			if (root->right != NULL)
				remove(root->right->key);
		}

		delete root;
	}
}

////////////////////////////////////////////////////////////

//____________ Public insert __________________
// If there is a node with the same key value as k, returns false.
template <class keyType, class dataType>
bool BinaryTree<keyType, dataType>::insert(const keyType &k, const dataType &d)
{
	return insert2(root, k, d);
} // end of public insert

//____________ Private insert __________________
template <class keyType, class dataType>
bool BinaryTree<keyType, dataType>::insert2(NodePointer &aRoot, const keyType &k, const dataType &d)
{
	// Check for empty tree.
	if (aRoot == NULL)
	{ // Attach new node
		aRoot = new treeNode;
		aRoot->left = NULL;
		aRoot->right = NULL;
		aRoot->key = k;
		aRoot->data = d;
		return true;
	}
	else if (k == aRoot->key)
		return false;
	else if (k < aRoot->key)
		return insert2(aRoot->left, k, d);
	else
		return insert2(aRoot->right, k, d);
} // end of private insert

//____________ Public search __________________
// Searches for the item with same key as k
template <class keyType, class dataType>
bool BinaryTree<keyType, dataType>::search(const keyType &k) const
{
	return search2(root, k);
} // end of public search   

template <class keyType, class dataType>
bool BinaryTree<keyType, dataType>::search2(NodePointer aRoot, const keyType &k)	const
{
	if (aRoot == NULL)
		return false;
	else if (k == aRoot->key)
		return true;
	else if (k < aRoot->key)
		return search2(aRoot->left, k);
	else
		return search2(aRoot->right, k);
} // end of private search

//____________ Public retrieve __________________
// Searches for the item with same key as k and retrieves data part if found
template <class keyType, class dataType>
bool BinaryTree<keyType, dataType>::retrieve(const keyType &k, dataType &d) const
{
	return retrieve2(root, k, d);
} // end of public retrieve   

template <class keyType, class dataType>
bool BinaryTree<keyType, dataType>::retrieve2(NodePointer aRoot, const keyType &k, dataType &d)	const
{
	if (aRoot == NULL)
		return false;
	else if (k == aRoot->key)
	{
		d = aRoot->data; return true;
	}
	else if (k < aRoot->key)
		return retrieve2(aRoot->left, k, d);
	else
		return retrieve2(aRoot->right, k, d);
} // end of private retrieve

//____________ Public empty __________________ 
// Check if tree is empty
template <class keyType, class dataType>
bool BinaryTree<keyType, dataType>::empty() const
{
	return(root == NULL);
} // end of empty

template <class keyType, class dataType>
int BinaryTree<keyType, dataType>::height()
{
	return heightPrivate(root);
} // end of public retrieve   

template <class keyType, class dataType>
int BinaryTree<keyType, dataType>::heightPrivate(NodePointer aRoot)
{
	if (aRoot == NULL)
		return 0;

	return 1 + max(heightPrivate(aRoot->left), heightPrivate(aRoot->right));
}

template <class keyType, class dataType>
int BinaryTree<keyType, dataType>::max(int a, int b){

	if (a > b)
		return a;
	else return b;

}


template <class keyType, class dataType>
int BinaryTree<keyType, dataType>::Leaves()
{
	return LeavesPrivate(root);
} // end of public retrieve   

template <class keyType, class dataType>
int BinaryTree<keyType, dataType>::LeavesPrivate(NodePointer aRoot)
{
	if (aRoot == NULL)
		return 0;

	if (aRoot->left == NULL && aRoot->right == NULL)
		return 1;

	return LeavesPrivate(aRoot->left) + LeavesPrivate(aRoot->right);
}

template <class keyType, class dataType>
int BinaryTree<keyType, dataType>::InternalNodes()
{
	return InternalNodesPrivate(root);
} // end of public retrieve   

template <class keyType, class dataType>
int BinaryTree<keyType, dataType>::InternalNodesPrivate(NodePointer aRoot)
{
	if (aRoot == NULL)
		return 0;

	if (aRoot->left == NULL && aRoot->right == NULL)
		return 0;

	return 1 + InternalNodesPrivate(aRoot->left) + InternalNodesPrivate(aRoot->right);
}

template <class keyType, class dataType>
int BinaryTree<keyType, dataType>::TotalNodes()
{
	return TotalNodesPrivate(root);
} // end of public retrieve   

template <class keyType, class dataType>
int BinaryTree<keyType, dataType>::TotalNodesPrivate(NodePointer aRoot)
{
	if (aRoot == NULL)
		return 0;

	return 1 + TotalNodesPrivate(aRoot->left) + TotalNodesPrivate(aRoot->right);
}

template <class keyType, class dataType>
void BinaryTree<keyType, dataType>::MinNode(keyType& k){
	return MinNodePrivate(root, k);
}

template <class keyType, class dataType>
void BinaryTree<keyType, dataType>::MinNode(NodePointer aRoot, keyType& k) {
	/*	if (aRoot == NULL)
			return 0;

			dataType left, right;
			MinNode(aRoot->left, left);
			MinNode(aRoot->right, right);

			if (aRoot->data < left && aRoot->data < right)
			d = aRoot->data;
			else if (left < aRoot->data && left < right)
			d = left;
			else
			d = right;*/

	if (aRoot->left != NULL)
		MinNode(aRoot->left, k);
	else k = aRoot->key;
}

////////////////////////////////////////////////////////////////////////////////
template <class keyType, class dataType>
void BinaryTree<keyType, dataType>::MaxNode(keyType& k){
	return MaxNode(root, k);
}

template <class keyType, class dataType>
void BinaryTree<keyType, dataType>::MaxNode(NodePointer aRoot, keyType &k) {
	/*	if (aRoot == NULL)
			return 0;

			dataType left, right;
			MinNode(aRoot->left, left);
			MinNode(aRoot->right, right);

			if (aRoot->data < left && aRoot->data < right)
			d = aRoot->data;
			else if (left < aRoot->data && left < right)
			d = left;
			else
			d = right;*/

	if (aRoot->right != NULL)
		MaxNode(aRoot->right, k);
	else k = aRoot->key;
}


// TRAVERSE A TREE
template <class keyType, class dataType>
void BinaryTree<keyType, dataType>::traverse(vector<keyType>& k, vector<dataType>& d) const
{
	/*k=new keyType [TotalNodes()];
	d=new dataType[TotalNodes()];
	*/
	traverse2(root, k, d);

}

// Traverses a subtree INORDER
template <class keyType, class dataType>
void BinaryTree<keyType, dataType>::traverse2(NodePointer aRoot, vector<keyType>& k, vector<dataType>& d) const
{
	if (aRoot != NULL)
	{
		if (aRoot->left != NULL)
		{
			traverse2(aRoot->left, k, d);
		}

		k.push_back(aRoot->key);
		d.push_back(aRoot->data);

		if (aRoot->right != NULL)
		{
			traverse2(aRoot->right, k, d);
		}
	}
}

// Iterative Pre-order Traversal
template <class keyType, class dataType>
void BinaryTree<keyType, dataType>::preorder(vector<keyType>& k, vector<dataType>& d) const
{
	NodePointer t;
	t = root;

	//vector<keyType, dataType> x;

	Stackt<NodePointer> s;
	s.push(t);

	if (t != NULL)
	while (!s.stackIsEmpty())
	{
		s.pop(t);

		k.push_back(t->key);
		d.push_back(t->data);

		if (t->right != NULL) s.push(t->right);
		if (t->left != NULL) s.push(t->left);
	}

	//return x;


}

// Iterative Level-order Traversal
template <class keyType, class dataType>
void BinaryTree<keyType, dataType>::levelorder(vector<keyType>& k, vector<dataType>& d) const
{
	NodePointer t;
	t = root;

	//vector<keyType, dataType> x;

	Deque<NodePointer> q;
	q.pushback(t);
	if (t != NULL)
	while (!q.isEmpty())
	{
		t=q.Front();
		q.popfront();

		k.push_back(t->key);
		d.push_back(t->data);

		if (t->left != NULL)
			q.pushback(t->left);

		if (t->right != NULL)
			q.pushback(t->right);
	}
}
// REMOVE AN ELEMENT FROM THE TREE
template <class keyType, class dataType>
void BinaryTree<keyType, dataType>::remove(keyType & k)
{
	NodePointer t = root, p;

	if (search2(t, k))
	{
		bool found;

		parentSearch(k, found, t, p);

		if (found)
		{
			if (t->left == NULL&&t->right == NULL)
			{
				if (p->left == t)
				{
					p->left = NULL;
					delete t;
				}
				else
				{
					p->right = NULL;
					delete t;
				}
			}
			else if (t->left == NULL || t->right == NULL)
			{
				if (p->key > t->key)
				{
					if (t->left == NULL)
					{
						p->left = t->right;
						delete t;
					}
					else
					{
						p->left = t->left;
						delete t;
					}
				}
				else
				{
					if (t->left == NULL)
					{
						p->right = t->right;
						delete t;
					}
					else
					{
						p->right = t->left;
						delete t;
					}
				}
			}
			else
			{
				if (heightPrivate((t->left)->right) > heightPrivate((t->right)->left))
				{
					keyType g;

					MaxNode(t->left, g);

					NodePointer prex, temp;
					parentSearch(g, found, prex, temp);

					dataType d;

					retrieve(g, d);

					remove(prex->key);

					t->key = g;
					t->data = d;



				}
				else
				{
					keyType g;
					MinNode(t->right, g);

					NodePointer sx, temp;
					parentSearch(g, found, sx, temp);

					dataType d;

					retrieve(g, d);

					remove(sx->key);

					t->key =g;
					t->data = d;

					
				}
			}
		}
		else root = NULL;

	}

}


// LOCATE A NODE CONTAINING ELEMENT AND ITS 
// PARENT
template <class keyType, class dataType>
void BinaryTree<keyType, dataType>::parentSearch(const keyType &k, bool &found, NodePointer &locptr, NodePointer &parent) const
{
	locptr = root;
	parent = NULL;
	found = false;

	while ( !found&&(locptr != NULL))
	{
		if (k < locptr->key)
		{
			parent = locptr;
			locptr = locptr->left;
		}
		else if (k > locptr->key)
		{
			parent = locptr;
			locptr = locptr->right;
		}
		else found = true;
		//else found = true;
	}
	if (parent == NULL)
		found = false;

	if (locptr->key == k)
		found = true;
}
