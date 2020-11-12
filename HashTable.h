#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>


using namespace std;

template <class k,class HashedObj>
class HashTable
{
	
public:

	explicit HashTable(const k & key ,const HashedObj & notFound, int size = 101 );

	HashTable( const HashTable & rhs )
		: ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
		array( rhs.array ), currentSize( rhs.currentSize ) { }

	const HashedObj & find( const k & x ) ; 
	//k & find(const k & x );

	void makeEmpty( );
	void insert(const k & key ,const HashedObj & x );
	void remove( const HashedObj & x );
	int hash (const string & key, int tableSize);
	void AfterPreporcessing();
	HashedObj* FindDetTable (k & element );

	const HashTable & operator=( const HashTable & rhs );

	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry
	{
		k key;
		HashedObj element;
		EntryType info;

		HashEntry( const HashedObj & e ,const k &k, EntryType i = EMPTY )
			: element( e ), key(k), info( i ) { }
		HashEntry(){}
	};

	vector<HashEntry> array;
	int currentSize;
	const HashedObj ITEM_NOT_FOUND;

	bool isActive( int currentPos ) const;
	int findPos( const k & x ) ;
	void rehash( );
	k notAkey;
};

/**
* Construct the hash table.
*/
template <class k,class HashedObj>
HashTable<k,HashedObj>::HashTable( const k & key,const HashedObj & notFound,int size )
	: ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) )
{
	makeEmpty( );
}



int myHash (const string & key, int tableSize)
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
void HashTable<k,HashedObj>::AfterPreporcessing()
{
	double i = currentSize+0.0;
	cout << endl;
	cout << "After preprocessing, the unique word count is " << currentSize << ". Current load ratio is " << i/array.size() << endl;
}


template<class k,class HashedObj>
int HashTable<k,HashedObj>::findPos(const k & x )
{
	int collisionNum = 0;
	//int currentPos = hash(x);
	int currentPos = myHash(x, array.size());
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

//template <class k,class HashedObj>
//k & HashTable<k,HashedObj>::find(const k & x )
//{
//
//	int currentPos = findPos( x );
//	if (isActive( currentPos ))
//		return array[ currentPos].key;
//	return notAkey ; // might have deal with it later
//}

template <class k, class HashedObj>
const HashedObj & HashTable<k, HashedObj>::find( const k & x ) 
{
	int currentPos = findPos( x );
	if (isActive( currentPos )) 
		return array[ currentPos ].element; 

	return   ITEM_NOT_FOUND;
}

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

	array[ currentPos ] = HashEntry( x,key, ACTIVE );
	// enlarge the hash table if necessary

	if ( ++currentSize >= array.size()*0.5 )
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

	double i = currentSize+0.0;
	cout<< "rehashed..."<< endl;
	cout << "previous table size: " << oldArray.size() << ", new table size " << array.size() << ", current unique word count " << currentSize 
		<< ", current load factor: " << i/array.size() << endl;
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
	return &(array[i].element);


}

template <class k, class HashedObj>
void HashTable<k, HashedObj>::makeEmpty( )
{
	for( int i = 0; i < array.size( ); i++ )
		array[i].info = EMPTY ;
	currentSize= 0;

}

#endif