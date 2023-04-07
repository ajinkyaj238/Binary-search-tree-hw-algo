//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file BinaryNodeTree.cpp */

#include "BinaryNodeTree.h" 
#include "BinaryNode.h"
#include "TreeExceptions.h"
#include <iostream>

//////////////////////////////////////////////////////////////
//      Protected Utility Methods Section
//////////////////////////////////////////////////////////////

template<class T>
int BinaryNodeTree<T>::getHeightHelper(BinaryNode<T>* subTreePtr) const
{
   if (subTreePtr == NULL)
      return 0;
   else
      return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), 
                     getHeightHelper(subTreePtr->getRightChildPtr()));
}  // end getHeightHelper

template<class T>
int BinaryNodeTree<T>::getNumberOfNodesHelper(BinaryNode<T>* subTreePtr) const
{
   if (subTreePtr == NULL)
      return 0;
   else
      return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) 
               + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
}  // end getNumberOfNodesHelper

template<class T>
BinaryNode<T>* BinaryNodeTree<T>::balancedAdd(BinaryNode<T>* subTreePtr,
                                                            BinaryNode<T>* newNodePtr)
{
   if (subTreePtr == NULL)
      return newNodePtr;
   else
   {
      BinaryNode<T>* leftPtr = subTreePtr->getLeftChildPtr();
      BinaryNode<T>* rightPtr = subTreePtr->getRightChildPtr();
      
      if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
      {
         rightPtr = balancedAdd(rightPtr , newNodePtr);
         subTreePtr->setRightChildPtr(rightPtr );
      }
      else
      {
         leftPtr = balancedAdd(leftPtr, newNodePtr);
         subTreePtr->setLeftChildPtr(leftPtr);
      }  // end if
      
      return subTreePtr;
   }  // end if
}  // end balancedAdd

template<class T>
BinaryNode<T>* BinaryNodeTree<T>::moveValuesUpTree(BinaryNode<T>* subTreePtr)
{
   BinaryNode<T>* leftPtr = subTreePtr->getLeftChildPtr();
   BinaryNode<T>* rightPtr = subTreePtr->getRightChildPtr();
   int leftHeight = getHeightHelper(leftPtr);
   int rightHeight = getHeightHelper(rightPtr);
   if (leftHeight > rightHeight)
   {
      subTreePtr->setItem(leftPtr->getItem());
      leftPtr = moveValuesUpTree(leftPtr);
      subTreePtr->setLeftChildPtr(leftPtr);
      return subTreePtr;
   }
   else 
   {
      if (rightPtr != NULL)
      {
         subTreePtr->setItem(rightPtr->getItem());
         rightPtr =moveValuesUpTree(rightPtr);         
         subTreePtr->setRightChildPtr(rightPtr);
         return subTreePtr;
      }
      else 
      {
         //this was a leaf!
         // value not important
         delete subTreePtr;
         return NULL;
      }  // end if
   }  // end if   
}  // end moveValuesUpTree

/** Depth-first search of tree for item.
 @param subTreePtr  tree to search.
 @param target  target item to find.
 @param success  communicate to client we found it. 
 @returns  A pointer to node containing the item. */
template<class T>
BinaryNode<T>* BinaryNodeTree<T>::removeValue(BinaryNode<T>* subTreePtr,
                                                            const T target,
                                                            bool& success)
{
   if(subTreePtr == NULL) // not found here
      return NULL;

   if (subTreePtr->getItem() == target) // found it
   {
      subTreePtr = moveValuesUpTree(subTreePtr);
      success = true;
      return subTreePtr;
   }
   else 
   {
      BinaryNode<T>* targetNodePtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
      subTreePtr->setLeftChildPtr(targetNodePtr);
      if (!success) // no need to search right subTree
      {
         targetNodePtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
         subTreePtr->setRightChildPtr(targetNodePtr);
      }  // end if
      
      return subTreePtr;
   }  // end if
}  // end removeValue

template<class T>
BinaryNode<T>* BinaryNodeTree<T>::findNode(BinaryNode<T>* treePtr, 
                                                         const T& target,
                                                         bool& success) const
{
   if (treePtr == NULL) // not found here
      return NULL;
   
   if (treePtr->getItem() == target) // found it
   {
      success = true;
      return treePtr;
   }
   else 
   {
      BinaryNode<T>* targetNodePtr = findNode(treePtr->getLeftChildPtr(), target, success);
      if (!success) // no need to search right subTree
      {
         targetNodePtr = findNode(treePtr->getRightChildPtr(), target, success);
      }  // end if
      
      return targetNodePtr;
   }  // end if 
}  // end findNode

template<class T>
BinaryNode<T>* BinaryNodeTree<T>::copyTree(const BinaryNode<T>* treePtr) const
{
   BinaryNode<T>* newTreePtr = NULL;
   
   // Copy tree nodes during a preorder traversal
   if (treePtr != NULL)
   {
      // Copy node
	   newTreePtr = new BinaryNode<T>(treePtr->getItem(), NULL, NULL);
	   newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
      newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
   }  // end if
   
   return newTreePtr;
}  // end copyTree

template<class T>
void BinaryNodeTree<T>::destroyTree(BinaryNode<T>* subTreePtr)
{
   if (subTreePtr != NULL)
   {
      destroyTree(subTreePtr->getLeftChildPtr());
      destroyTree(subTreePtr->getRightChildPtr());
      delete subTreePtr;
   }  // end if
}  // end destroyTree

//////////////////////////////////////////////////////////////
//      Protected Tree Traversal Sub-Section
//////////////////////////////////////////////////////////////

template<class T>
void BinaryNodeTree<T>::preorder(void visit(T&), BinaryNode<T>* treePtr) const
{
   if (treePtr != NULL)
   {
      T theItem = treePtr->getItem();
      visit(theItem);
      preorder(visit, treePtr->getLeftChildPtr());
      preorder(visit, treePtr->getRightChildPtr());
   }  // end if
}  // end preorder

template<class T>
void BinaryNodeTree<T>::inorder(void visit(T&), BinaryNode<T>* treePtr) const
{
   if (treePtr != NULL)
   {
      inorder(visit, treePtr->getLeftChildPtr());
      T theItem = treePtr->getItem();
      visit(theItem);
      inorder(visit, treePtr->getRightChildPtr());
   }  // end if
}  // end inorder

template<class T>
void BinaryNodeTree<T>::postorder(void visit(T&), BinaryNode<T>* treePtr) const
{
   if (treePtr != NULL)
   {
      postorder(visit, treePtr->getLeftChildPtr());
      postorder(visit, treePtr->getRightChildPtr());
      T theItem = treePtr->getItem();
      visit(theItem);
   } // end if
}  // end postorder

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

template<class T>
BinaryNodeTree<T>::BinaryNodeTree() : rootPtr(NULL)
{
}  // end default constructor

template<class T>
BinaryNodeTree<T>::BinaryNodeTree(const T& rootItem)
{
   rootPtr = new BinaryNode<T>(rootItem, NULL, NULL);
}  // end constructor

template<class T>
BinaryNodeTree<T>::BinaryNodeTree(const T& rootItem,
                                         const BinaryNodeTree<T>* leftTreePtr,
                                         const BinaryNodeTree<T>* rightTreePtr)
{
    rootPtr = new BinaryNode<T>(rootItem, copyTree(leftTreePtr->rootPtr), 
                                                 copyTree(rightTreePtr->rootPtr));
}  // end constructor

template<class T>
BinaryNodeTree<T>::BinaryNodeTree(const BinaryNodeTree<T>& treePtr)
{
   rootPtr = copyTree(treePtr.rootPtr);
}  // end copy constructor

template<class T>
BinaryNodeTree<T>::~BinaryNodeTree()
{
   destroyTree(rootPtr);
}  // end destructor

//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section
//////////////////////////////////////////////////////////////


template<class T>
bool BinaryNodeTree<T>::isEmpty() const
{
   return rootPtr == NULL;
}  // end isEmpty

template<class T>
int BinaryNodeTree<T>::getHeight() const
{
   return getHeightHelper(rootPtr);
}  // end getHeight

template<class T>
int BinaryNodeTree<T>::getNumberOfNodes() const
{
   return getNumberOfNodesHelper(rootPtr);
}  // end getNumberOfNodes

template<class T>
void BinaryNodeTree<T>::clear()
{
   destroyTree(rootPtr);
   rootPtr = NULL;
}  // end clear

template<class T>
T BinaryNodeTree<T>::getRootData() const throw(PrecondViolatedExcep)
{
   if (isEmpty())
      throw PrecondViolatedExcep("getRootData() called with empty tree."); 
      
   return rootPtr->getItem();
}  // end getRootData

template<class T>
void BinaryNodeTree<T>::setRootData(const T& newItem)
{
   if (isEmpty())
      rootPtr = new BinaryNode<T>(newItem, NULL, NULL);
   else
      rootPtr->setItem(newItem);
}  // end setRootData

template<class T>
bool BinaryNodeTree<T>::add(const T& newData)
{
   BinaryNode<T>* newNodePtr = new BinaryNode<T>(newData);
   rootPtr = balancedAdd(rootPtr, newNodePtr);
   return true;
}  // end add

template<class T>
bool BinaryNodeTree<T>::remove(const T& target)
{
   bool isSuccessful = false;
   rootPtr = removeValue(rootPtr, target, isSuccessful);
   return isSuccessful; 
}  // end remove

template<class T>
T BinaryNodeTree<T>::getEntry(const T& anEntry) const throw(NotFoundException)
{
   bool isSuccessful = false;
   BinaryNode<T>* binaryNodePtr = findNode(rootPtr, anEntry, isSuccessful);
   
   if (isSuccessful)
      return binaryNodePtr->getItem(); 
   else 
      throw NotFoundException("Entry not found in tree!");
}  // end getEntry

template<class T>
bool BinaryNodeTree<T>:: contains(const T& anEntry) const
{
   bool isSuccessful = false;
   findNode(rootPtr, anEntry, isSuccessful);
   return isSuccessful;   
}  // end contains

//////////////////////////////////////////////////////////////
//      Public Traversals Section
//////////////////////////////////////////////////////////////

template<class T>
void BinaryNodeTree<T>::preorderTraverse(void visit(T&)) const
{
   preorder(visit, rootPtr);
}  // end preorderTraverse

template<class T>
void BinaryNodeTree<T>::inorderTraverse(void visit(T&)) const
{
   inorder(visit, rootPtr);
}  // end inorderTraverse

template<class T>
void BinaryNodeTree<T>::postorderTraverse(void visit(T&)) const
{
   postorder(visit, rootPtr);
}  // end postorderTraverse

//////////////////////////////////////////////////////////////
//      Overloaded Operator 
//////////////////////////////////////////////////////////////

template<class T>
BinaryNodeTree<T>& BinaryNodeTree<T>::operator=(
                                                const BinaryNodeTree<T>& rightHandSide)
{
   if (!isEmpty())
      clear();
   this = copyTree(&rightHandSide);
   return *this;
}  // end operator=


