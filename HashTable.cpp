#ifndef HASHTABLE_CPP
#define HASHTABLE_CPP

#include <iostream>
#include "HashTable.h"
#include <vector>

using namespace std;


/**
* Internal method to return a prime number
* at least as large as n. Assumes n > 0.
*/



/**
* Construct the hash table.
*/
template <class k,class HashedObj>
HashTable<k,HashedObj>::HashTable( const k & key,const HashedObj & notFound,int size )
	: ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) )
{
	makeEmpty( );
}



int hash (const string & key, int tableSize)
{ 
	int hashVal = 0;

	for (int i = 0; i < key.length();i++) 
		hashVal = 37 * hashVal + key[ i ];

	hashVal = hashVal % tableSize;

	if (hashVal < 0) 
		hashVal = hashVal + tableSize;

	return(hashVal);
}



template<class k,class HashedObj>
int HashTable<k,HashedObj>::findPos(const k & x )
{
	int collisionNum = 0;
	//int currentPos = hash(x);
	int currentPos = hash(x, array.size());
	while ( array[ currentPos ].info != EMPTY && array[ currentPos ].key != x )
	{
		currentPos += 2 * ++collisionNum - 1; // add the difference
		if ( currentPos >= array.size( ) ) // perform the mod
			currentPos = currentPos - array.size( ); // if necessary
	}

	return currentPos;
}




template <class k,class HashedObj>
bool HashTable<k,HashedObj>::isActive( int currentPos ) const
{
	return array[ currentPos ].info == ACTIVE;
}


/**
* Find item x in the hash table.
* Return the matching item, or ITEM_NOT_FOUND, if not found.
*/

template <class k,class HashedObj>
k & HashTable<k,HashedObj>::find(const k & x )
{

	int currentPos = findPos( x );
	if (isActive( currentPos ))
		return array[ currentPos].key;
	return notAkey ; // might have deal with it later
}

//template <class k, class HashedObj>
//const HashedObj & HashTable<k, HashedObj>::find( const HashedObj & x ) 
//	const
//{
//	int currentPos = findPos( x );
//	if (isActive( currentPos )) 
//		return array[ currentPos ].element; 
//
//	return   ITEM_NOT_FOUND;
//}

/**
* Insert item x into the hash table. If the item is
* already present, then do nothing.
*/

template <class k,class HashedObj>
void HashTable<k,HashedObj>::insert( const k & key,const HashedObj & x )
{
	// Insert x as active
	int currentPos = findPos( key);
	if ( isActive( currentPos ) )
		return;

	array[ currentPos ] = HashEntry( x, ACTIVE );
	// enlarge the hash table if necessary

	if ( ++currentSize >= array.size()*1.0 / 2 )
		rehash( );
}


/**
* Expand the hash table.
*/

template <class k,class HashedObj>
void HashTable<k,HashedObj>::rehash( )
{
	vector<HashEntry> oldArray = array;
	// Create new double-sized, empty table
	array.resize( nextPrime( 2 * oldArray.size( ) ) );

	for ( int j = 0; j < array.size( ); j++ )
	{
		array[ j ].info = EMPTY;
	}

	// Copy table over
	currentSize = 0;

	for ( int i = 0; i < oldArray.size( ); i++ )
	{
		if ( oldArray[ i ].info == ACTIVE )
			insert( oldArray[i].key,oldArray[ i ].element );
	}
}

/**
* Remove item x from the hash table.
*  x has to be in the table
*/
template <class k,class HashedObj>
void HashTable<k, HashedObj>::remove( const HashedObj & x )
{
	int currentPos = findPos( x );
	if ( isActive( currentPos ) )
		array[ currentPos ].info = DELETED;
}

template <class k,class HashedObj>
HashedObj* HashTable<k, HashedObj>::FindDetTable (k & element )
{
	int i=findPos(element);
	return (&array[i].element);

}

#endif