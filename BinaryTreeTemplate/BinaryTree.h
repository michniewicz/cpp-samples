#pragma once

#include "Node.h"
//class Node;

template<typename T>
class BinaryTree
{
	Node<T>* root;
public:

	BinaryTree();

	BinaryTree(const BinaryTree& bt);

	~BinaryTree();

	// get root address
	Node<T>* GetRoot() const 
	{
		return root;	
	}

	// add new node
	void Add(Node<T>* n);

	// delete node
	void Delete(Node<T>* n);
	// delete all tree elements
	void DeleteAll();

	// init root
	void Init();

	// minimum from this node
	Node<T>* Minimum(Node<T>* n);
	// maximum from this node
	Node<T>* Maximum(Node<T>* n);

	// sorted output
	void Out(Node<T>* n);
	// preorder output
	void PreorderOut(Node<T>* root);

	// max depth
	int MaxDepth()
	{
		return MaxDepth(this->GetRoot());
	}

	// print to console (win only)
	void PrintStructure() 
	{
		PrintLevelOrder(this->root);
	}

	BinaryTree& operator = (const BinaryTree& bt);

private:
	
	int MaxDepth(Node<T>* n);
	
	Node<T>* Next(Node<T>* n);
	
	Node<T>* Previous(Node<T>* n);

	string PrintSpaces(int level);

	
	void PrintGivenLevel(Node<T>* n, int level, string s);
	
	void PrintLevelOrder(Node<T>* n);

	void PreorderCopy(Node<T>* n);

};

template<typename T>
BinaryTree<T>::BinaryTree(void)
{
	Init();
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& bt)
{
	Init();

	PreorderCopy(bt.GetRoot());
}

template<typename T>
BinaryTree<T>::~BinaryTree(void)
{
	DeleteAll();
}

template<typename T>
void BinaryTree<T>::Add(Node<T>* n)
{
	Node<T>* tmp = n;

	// no children
	tmp->Left(NULL);
	tmp->Right(NULL);

	Node<T> * newParent = NULL;
	Node<T> * node = root;

	// search for place
	while(node != 0)
	{

		newParent = node;
		if(tmp->GetKey() < node->GetKey())
			node = node->Left();
		else
			node = node->Right();
	}


	tmp->Parent(newParent);

	if(newParent == 0) // first element
		root = tmp;

	// which key is greater
	else if(tmp->GetKey() < newParent->GetKey()) 
		newParent->Left(tmp);
	else
		newParent->Right(tmp);
}

template<typename T>
void BinaryTree<T>::Init() 
{
	root = NULL;
}

template<typename T>
void BinaryTree<T>::Delete(Node<T>* n) 
{
	Node<T>* deleteNode = n;

	Node<T>* tmp		= NULL;
	Node<T>* newNode	= NULL;

	// not 2 children
	if(deleteNode->Left() == 0 || deleteNode->Right() == 0)
		newNode = deleteNode;
	else
		newNode = Next(deleteNode);

	if(newNode->Left())
		tmp = newNode->Left();
	else
		tmp = newNode->Right();

	if(tmp)
		tmp->Parent(newNode->Parent());

	// is root node is deleted?
	if(!newNode->Parent()) 
		root = tmp;

	else if(newNode == newNode->Parent()->Left()) // to the left of parent?
		newNode->Parent()->Left(tmp);

	else
		newNode->Parent()->Right(tmp);  // to the right of parent?

	deleteNode = NULL;
	newNode = NULL;
}

template<typename T>
void BinaryTree<T>::DeleteAll() 
{
	while(root)
		Delete(this->GetRoot());
}

template<typename T>
Node<T>* BinaryTree<T>::Minimum(Node<T>* n)
{
	Node<T>* tmp = n;

	// search for the most left node
	if(tmp)
	{
		while(tmp->Left())
			tmp = tmp->Left();
	}

	return tmp;
}

template<typename T>
Node<T>* BinaryTree<T>::Maximum(Node<T>* n)
{
	Node<T>* tmp = n;

	// search for the most right node
	if(tmp)
	{
		while(tmp->Right())
			tmp = tmp->Right();
	}

	return n;
}

template<typename T>
void BinaryTree<T>::Out(Node<T>* n)
{
	if(n != NULL)
	{
		Out(n->Left());

		cout << *n->GetData() << " " << n->GetKey() << endl;

		Out(n->Right());
	}
}

template<typename T>
void BinaryTree<T>::PreorderOut(Node<T>* n) 
{
    if (n != NULL) 
	{
        cout << n->GetKey() << " ";

        PreorderOut(n->Left());
        PreorderOut(n->Right()); 
    }
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator = (const BinaryTree& bt)
{
	if(this == &bt)
		return *this;
	this->DeleteAll();
	this->Init();
	PreorderCopy(bt.GetRoot());

	return *this;
}

template<typename T>
int BinaryTree<T>::MaxDepth(Node<T>* n) 
{
	if (n == NULL) 
	{
		return(0);
	}

	else 
	{
		int lDepth = MaxDepth(n->Left());
		int rDepth = MaxDepth(n->Right());

	
		if (lDepth > rDepth) 
			return(lDepth+1);
		else 
			return(rDepth+1);
	}

} 

template<typename T>
Node<T>* BinaryTree<T>::Next(Node<T>* n)
{
	Node<T>* tmp = NULL;

	if(n)
	{
		// if there is right child
		if(n->Right())
			return Minimum(n->Right());
		
		tmp = n->Parent();
		// if n is not root and n is right
		while(tmp != 0 && n == tmp->Right())
		{
			// go up
			n = tmp;
			tmp = tmp->Parent();
		}
	}

	return tmp;
}

template<typename T>
Node<T>* BinaryTree<T>::Previous(Node<T>* n)
{
   Node<T>* tmp = NULL;

   if(n)
   {
      // if there is left child
      if(n->Left())
         return Maximum(n->Left());
		
      // node parent
      tmp = n->Parent();
      // if n is not root and n is left
      while(tmp != 0 && n == tmp->Left())
      {
         // go up
         n = tmp;
         tmp = tmp->Parent();
      }
   }

   return tmp;
}

template<typename T>
string BinaryTree<T>::PrintSpaces(int level)
{
	string s = "";

	for(int i = 0; i < level; i++)
	{
		s += " ";
	}

	return s;
}

template<typename T>
void BinaryTree<T>::PrintLevelOrder(Node<T>* n)
{
	int h = MaxDepth();
	
	int spaces = MaxDepth()*3;

	for(int i = 1; i <= h; i++)
	{

		for(int j = 0; j < spaces; j++)
			cout << " ";

		string s = PrintSpaces(spaces*2);

		PrintGivenLevel(n, i, s);

		cout << endl << endl;

		spaces /= 2;
	}
}    
 
template<typename T>
void BinaryTree<T>::PrintGivenLevel(Node<T>* n, int level, string s)
{
	if(n == NULL)
	{
		cout << " " << s.c_str();
		return;
	}

	if(level == 1)
	{
		cout << n->GetKey() << s.c_str();
	}
	else if (level > 1)
	{
		PrintGivenLevel(n->Left(), level-1, s);
		PrintGivenLevel(n->Right(), level-1, s);
	}
}

template<typename T>
void BinaryTree<T>::PreorderCopy(Node<T>* n)
{
	if(n != NULL) 
	{
		Node<T>* left		= n->Left();
		Node<T>* right		= n->Right();
		Node<T>* parent		= n->Parent();

		this->Add(n);

		n->Left(left);
		n->Right(right);
		n->Parent(parent);

        PreorderCopy(n->Left());
        PreorderCopy(n->Right()); 
    }
	
}