//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT binary tree: Link-based implementation.
 @file BinaryNodeTree.h */
 
#ifndef _BINARY_NODE_TREE
#define _BINARY_NODE_TREE

#include "BinaryNode.h"
#include "TreeExceptions.h"

template<class T>
class BinaryNodeTree
{
private:
   BinaryNode<T>* rootPtr;
   
protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------
   
   int getHeightHelper(BinaryNode<T>* subTreePtr) const;
   int getNumberOfNodesHelper(BinaryNode<T>* subTreePtr) const;
   
   // Recursively deletes all nodes from the tree.
   void destroyTree(BinaryNode<T>* subTreePtr);
   
   // Recursively adds a new node to the tree in a left/right fashion to
   // keep the tree balanced.
   BinaryNode<T>* balancedAdd(BinaryNode<T>* subTreePtr,
                                     BinaryNode<T>* newNodePtr);
   
   // Removes the target value from the tree by calling moveValuesUpTree
   // to overwrite value with value from child.
   BinaryNode<T>* removeValue(BinaryNode<T>* subTreePtr,
                                     const T target, bool& success);
   
   // Copies values up the tree to overwrite value in current node until
   // a leaf is reached; the leaf is then removed, since its value is
   // stored in the parent.
   BinaryNode<T>* moveValuesUpTree(BinaryNode<T>* subTreePtr);
   
   // Recursively searches for target value in the tree by using a
   // preorder traversal.
   BinaryNode<T>* findNode(BinaryNode<T>* treePtr,
                                  const T& target,
                                  bool& success) const;
   
   // Copies the tree rooted at treePtr and returns a pointer to
   // the copy.
   BinaryNode<T>* copyTree(const BinaryNode<T>* treePtr) const;
   
   // Recursive traversal helper methods:
   void preorder(void visit(T&), BinaryNode<T>* treePtr) const;
   void inorder(void visit(T&), BinaryNode<T>* treePtr) const;
   void postorder(void visit(T&), BinaryNode<T>* treePtr) const;
   
public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
   BinaryNodeTree();
   BinaryNodeTree(const T& rootItem);
   BinaryNodeTree(const T& rootItem,
                  const BinaryNodeTree<T>* leftTreePtr,
                  const BinaryNodeTree<T>* rightTreePtr);
   BinaryNodeTree(const BinaryNodeTree<T>& tree);
   virtual ~BinaryNodeTree();
   
   //------------------------------------------------------------
   // Public BinaryTreeInterface Methods Section.
   //------------------------------------------------------------
   bool isEmpty() const;
   int getHeight() const;
   int getNumberOfNodes() const;
   T getRootData() const throw(PrecondViolatedExcep);
   void setRootData(const T& newData);
   bool add(const T& newData); // Adds a node
   bool remove(const T& data); // Removes a node
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
   BinaryNodeTree& operator=(const BinaryNodeTree& rightHandSide);
}; // end BinaryNodeTree

#include "BinaryNodeTree.cpp"

#endif
