//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Link-based implementation of the ADT binary search tree.
 @file BinarySearchTree.h */
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "Student.h"

template<class T>
class BinarySearchTree : public BinaryNodeTree<T>
{
private:
   BinaryNode<T>* rootPtr;
   
protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------
   // Recursively finds where the given node should be placed and
   // inserts it in a leaf at that point.
   BinaryNode<T>* insertInorder(BinaryNode<T>* subTreePtr,
                                       BinaryNode<T>* newNode);
   
   // Removes the given target value from the tree while maintaining a
   // binary search tree.
   BinaryNode<T>* removeValue(BinaryNode<T>* subTreePtr,
                                     const T target,
                                     bool& success);
   
   // Removes a given node from a tree while maintaining a
   // binary search tree.
   BinaryNode<T>* removeNode(BinaryNode<T>* nodePtr);
   
   // Removes the leftmost node in the left subtree of the node
   // pointed to by nodePtr.
   // Sets inorderSuccessor to the value in this node.
   // Returns a pointer to the revised subtree.
   BinaryNode<T>* removeLeftmostNode(BinaryNode<T>* subTreePtr,
                                            T& inorderSuccessor);
   
   // Returns a pointer to the node containing the given value,
   // or nullptr if not found.
   BinaryNode<T>* findNode(BinaryNode<T>* treePtr,
                                  const T& target) const;
   
public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
   BinarySearchTree();
   BinarySearchTree(const T& rootItem);
   BinarySearchTree(const BinarySearchTree<T>& tree);
   virtual ~BinarySearchTree();
   
   //------------------------------------------------------------
   // Public Methods Section.
   //------------------------------------------------------------
   bool isEmpty() const;
   int getHeight() const;
   int getNumberOfNodes() const;
   T getRootData() const throw(PrecondViolatedExcep);
   void setRootData(const T& newData) const throw(PrecondViolatedExcep);
   bool add(const T& newEntry);
   bool remove(const T& anEntry);
   void clear();
   T getEntry(const T& anEntry) const throw(NotFoundException);
   bool contains(const T& anEntry) const;
   
   //------------------------------------------------------------
   // Public Traversals Section.
   //------------------------------------------------------------
   void preorderTraverse(void visit(T&)) const;
   void inorderTraverse(void visit(T&)) const;
   void postorderTraverse(void visit(T&)) const;

   //------------------------------------------------------------
   // Overloaded Operator Section.
   //------------------------------------------------------------
   BinarySearchTree<T>& operator=(const BinarySearchTree<T>& rightHandSide);   
}; // end BinarySearchTree

#include "BinarySearchTree.cpp"
#endif
