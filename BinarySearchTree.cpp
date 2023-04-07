//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file BinarySearchTree.cpp */
#include <iostream>

#include "BinarySearchTree.h" 
#include "BinaryNode.h"
#include "TreeExceptions.h"



//////////////////////////////////////////////////////////////
//
//      Protected Utility Methods Section
//
//////////////////////////////////////////////////////////////

template<class T>
BinaryNode<T>* BinarySearchTree<T>::insertInorder(BinaryNode<T>* subTreePtr, BinaryNode<T>* newNodePtr)
{
   if (subTreePtr == NULL)
      return newNodePtr;
   else
   {
      if (subTreePtr->getItem() > newNodePtr->getItem())
         subTreePtr->setLeftChildPtr(insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr));
      else 
         subTreePtr->setRightChildPtr(insertInorder(subTreePtr->getRightChildPtr(), newNodePtr));
      
      return subTreePtr;
   }  // end if
}  // end insertInorder

template<class T>
BinaryNode<T>* BinarySearchTree<T>::removeValue(BinaryNode<T>* subTreePtr, const T target, bool& success)
{
   if (subTreePtr == NULL)           
   {
      // Not found here
      success = false;
      return NULL;
   }
   if (subTreePtr->getItem() == target)
   {
      // Item is in the root of some subtree
      subTreePtr = removeNode(subTreePtr);
      success = true;
      return subTreePtr;
   }
   else 
   {
      if (subTreePtr->getItem() > target)
         // Search the left subtree
         subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, success));
      else 
         // Search the right subtree
         subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, success));
      
      return subTreePtr;
   }  // end if
}  // end removeValue

template<class T>
BinaryNode<T>* BinarySearchTree<T>::removeNode(BinaryNode<T>* nodePtr)
{
   // Case 1) Node is a leaf - it is deleted
   // Case 2) Node has one child - parent adopts child
   // Case 3) Node has two children:
   //               Traditional implementation: Find successor node.
   //               Alternate implementation: Find successor value and replace node's value;
   //                  alternate does not need pass-by-reference
   if (nodePtr->isLeaf())
   {
      delete nodePtr;
      return (nodePtr = NULL); // Assign and return (student maybe should have separate statements)
   }
   else if (nodePtr->getLeftChildPtr() == NULL)  // Has rightChild only
   {
      BinaryNode<T>* nodeToConnectPtr = nodePtr->getRightChildPtr();
      delete nodePtr;
      nodePtr = NULL;
      return nodeToConnectPtr;
   }
   else if (nodePtr->getRightChildPtr() == NULL) // Has left child only
   {
      BinaryNode<T>* nodeToConnectPtr = nodePtr->getLeftChildPtr();
      delete nodePtr;
      nodePtr = NULL;
      return nodeToConnectPtr;      
   }
   else                                             // Has two children
   {
      // Traditional way to remove a value in a node with two children
      T newNodeValue;
      nodePtr->setRightChildPtr(removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue));
      nodePtr->setItem(newNodeValue);
      return nodePtr;
   
   }  // end if
}  // end removeNode

template<class T> 
BinaryNode<T>* BinarySearchTree<T>::removeLeftmostNode(BinaryNode<T>* nodePtr, T& inorderSuccessor)
{
   if (nodePtr->getLeftChildPtr() == NULL)
   {
      inorderSuccessor = nodePtr->getItem();
      return removeNode(nodePtr);
   }
   else 
   {
      nodePtr->setLeftChildPtr(removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor));
      return nodePtr;
   }  // end if      
}  // end removeLeftmostNode

// Override findNode because now we can use a binary search:
template<class T>
BinaryNode<T>* BinarySearchTree<T>::findNode(BinaryNode<T>* subTreePtr, const T& target) const
{
   // Uses a binary search 
   if (subTreePtr == NULL)
      return NULL;                        // Not found 
   else if (subTreePtr->getItem() == target)  
      return subTreePtr;                     // Found
   else if (subTreePtr->getItem() > target)
      // Search left subtree
      return findNode(subTreePtr->getLeftChildPtr(), target);
   else
      // Search right subtree
      return findNode(subTreePtr->getRightChildPtr(), target);
}  // end findNode



//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

template<class T>
BinarySearchTree<T>::BinarySearchTree() : rootPtr(NULL)
{
}  // end default constructor

template<class T>
BinarySearchTree<T>::BinarySearchTree(const T& rootItem)
{
   rootPtr = new BinaryNode<T>(rootItem, NULL, NULL);
}  // end constructor

template<class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& treePtr)
{
   rootPtr = this->copyTree(treePtr.rootPtr); // Call inherited method
}  // end copy constructor

template<class T>
BinarySearchTree<T>::~BinarySearchTree()
{
   this->destroyTree(rootPtr); // Call inherited method
}  // end destructor



//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section
//////////////////////////////////////////////////////////////

template<class T>
bool BinarySearchTree<T>::isEmpty() const
{
   return rootPtr == NULL;
}  // end isEmpty

template<class T>
int BinarySearchTree<T>::getHeight() const
{
   return this->getHeightHelper(rootPtr); // Call inherited method
}  // end getHeight

template<class T>
int BinarySearchTree<T>::getNumberOfNodes() const
{
   return this->getNumberOfNodesHelper(rootPtr); // Call inherited method
}  // end getNumberOfNodes

template<class T>
void BinarySearchTree<T>::clear()
{
   this->destroyTree(rootPtr); // Call inherited method
   rootPtr = NULL;
}  // end clear

template<class T>
T BinarySearchTree<T>::getRootData() const throw(PrecondViolatedExcep)
{
   if (isEmpty())
      throw PrecondViolatedExcep("getRootData() called with empty tree."); 
   
   return rootPtr->getItem();
}  // end getRootData

// Must override setRootData to disable its affect:
template<class T>
void BinarySearchTree<T>::setRootData(const T& newItem) const throw(PrecondViolatedExcep)
{
   throw PrecondViolatedExcep("Cannot change root value in a BST!");
}  // end setRootData

template<class T>
bool BinarySearchTree<T>::add(const T& newData)
{
   BinaryNode<T>* newNodePtr = new BinaryNode<T>(newData);
   rootPtr = insertInorder(rootPtr, newNodePtr);
   
   return true;
}  // end add

template<class T>
bool BinarySearchTree<T>::remove(const T& target)
{
   bool isSuccessful = false;
   rootPtr = removeValue(rootPtr, target, isSuccessful);
   return isSuccessful; 
}  // end remove

// Override getEntry to use our improved findNode:
template<class T>
T BinarySearchTree<T>::getEntry(const T& anEntry) const throw(NotFoundException)
{
   BinaryNode<T>* nodeWithEntry = findNode(rootPtr, anEntry);
   if (nodeWithEntry == NULL)
      throw NotFoundException("Entry not found in tree.");
   else
      return nodeWithEntry->getItem();
}  // end getEntry

// Override contains to use our improved findNode:
template<class T>
bool BinarySearchTree<T>::contains(const T& anEntry) const
{

   return findNode(rootPtr, anEntry);  // NULL is same as false
}  // end contains



//////////////////////////////////////////////////////////////
//      Public Traversals Section
//////////////////////////////////////////////////////////////

template<class T>
void BinarySearchTree<T>::preorderTraverse(void visit(T&)) const
{
   this->preorder(visit, rootPtr); // Call inherited method
}  // end preorderTraverse

template<class T>
void BinarySearchTree<T>::inorderTraverse(void visit(T&)) const
{
   this->inorder(visit, rootPtr); // Call inherited method
}  // end inorderTraverse

template<class T>
void BinarySearchTree<T>::postorderTraverse(void visit(T&)) const
{
   this->postorder(visit, rootPtr); // Call inherited method
}  // end postorderTraverse



//////////////////////////////////////////////////////////////
//      Overloaded Operator 
//////////////////////////////////////////////////////////////

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& rightHandSide)
{
   if (!isEmpty())
      clear();
   this = copyTree(&rightHandSide); // Call inherited method
   
   return *this;
}  // end operator=




