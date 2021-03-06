﻿#ifndef BST_CPP
#define BST_CPP

#include <iostream>
#include "BST.h"
using namespace std;

//PUBLIC FUNCTIONS OF AVL TREE
template <class key,class value>  //constructor
BinarySearchTree<key,value>::
	BinarySearchTree(const key & notFound,const value & Val ) :
	ITEM_NOT_FOUND( notFound ), root( NULL )
{}


template <class key, class value>
const key & BinarySearchTree<key, value>::find( const key & x ) const // public find
{
	return elementAt( find( x, root ) );
}

template<class key,class value>
value* BinarySearchTree<key,value>::FindDet(key & a)
{
	return &find(a,root)->details;
}

template <class key, class value> //public insert
void BinarySearchTree<key, value>::insert( const key & x, const value &t )
{
	insert( x,t, root );
}


//PRIVATE FUNCTIONS OF AVL TREE
template <class key, class value>
const key & BinarySearchTree<key, value>::elementAt( BinaryNode<key, value> *t ) const //element at
{
	return t == NULL ? ITEM_NOT_FOUND : t->element;
}


template <class key, class value>			//private insert
void BinarySearchTree<key, value>::insert( const key & x, const value &p, BinaryNode<key, value> * & t) const
{
	if( t == NULL ) //  create a new node at the right place
		t = new BinaryNode<key, value>( x, p,NULL, NULL );
	else if( x < t->element )
		insert( x,p, t->left );  // insert at the left or 
	else if( t->element < x )
		insert( x,p, t->right );  // right subtree
	else
		;  // Duplicate; do nothing
}



template <class key, class value>
BinaryNode<key, value> *
	BinarySearchTree<key, value>::find( const key & x, BinaryNode<key, value> * t ) const //private find
{
	if ( t == NULL )
		return NULL;
	else if( x < t->element )
		return find( x, t->left );
	else if( t->element < x )
		return find( x, t->right );
	else
		return t;    // Match
}

template <class key, class value>
BinaryNode<key, value> *BinarySearchTree<key, value>::clone( BinaryNode<key, value> * t ) const //clone
{
	if ( t == NULL )
		return NULL;
	else
		return new BinaryNode<value> 
		( t->element, 
		clone( t->left ), 
		clone( t->right ) );
}



//AVL MANIPULATIONS
template <class key, class value>
int BinarySearchTree<key, value>::max( int lhs, int rhs ) const //max
{
	if (lhs > rhs)
		return lhs;

	return rhs;            
}
template <class key, class value>
int BinarySearchTree<key, value>::height( BinaryNode<key, value> *t ) const //height
{
	if (t == NULL)
		return -1;

	return t->height;
}



#endif

