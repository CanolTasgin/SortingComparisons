#ifndef SORT_H_
#define SORT_H_

#define merge Merge
#define swap Swap

#include <vector>
#include "BinaryTree.h"


template <class Comparable>
void insertionSort( vector<Comparable> & a )
{
    for( int p = 1; p < a.size( ); p++ )
    {
        Comparable tmp = a[ p ];
        
        int j;
        for( j = p; j > 0 && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}


template <class Comparable>
void heapsort( vector<Comparable> & a )
{
    for( int i = a.size() / 2; i >= 0; i-- )  /* buildHeap */
        percDown( a, i, a.size( ) );
    for( int j = a.size() - 1; j > 0; j-- )
    {
        swap( a[ 0 ], a[ j ] );                  /* deleteMax */
        percDown( a, 0, j );
    }
}


inline int leftChild( int i )
{
    return 2 * i + 1;
}


template <class Comparable>
void percDown( vector<Comparable> & a, int i, int n )
{
    int child;
    contactInfo tmp = contactInfo("","","");
    
    for( tmp = a[ i ]; leftChild( i ) < n; i = child )
    {
        child = leftChild( i );
        if( child != n - 1 && a[ child ] < a[ child + 1 ] )
            child++;
        if( tmp < a[ child ] )
            a[ i ] = a[ child ];
        else
            break;
    }
    a[ i ] = tmp;
}

template <class Comparable>
void mergeSort( vector<Comparable> & a )
{
    vector<Comparable> tmpArray;
    
    mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}

template <class Comparable>
void mergeSort( vector<Comparable> & a,
               vector<Comparable> & tmpArray, int left, int right )
{
    if( left < right )
    {
        int center = ( left + right ) / 2;
        mergeSort( a, tmpArray, left, center );
        mergeSort( a, tmpArray, center + 1, right );
        merge( a, tmpArray, left, center + 1, right );
    }
}


template <class Comparable>
void merge( vector<Comparable> & a, vector<Comparable> & tmpArray,
           int leftPos, int rightPos, int rightEnd )
{
    int leftEnd = rightPos - 1;
    //int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;
    
    // Main loop
    while( leftPos <= leftEnd && rightPos <= rightEnd )
        if( a[ leftPos ] <= a[ rightPos ])
            tmpArray.push_back(a[ leftPos++ ]);
        else
            tmpArray.push_back(a[ rightPos++ ]);
    
    while( leftPos <= leftEnd )    // Copy rest of first half
        tmpArray.push_back(a[ leftPos++ ]);
    
    while( rightPos <= rightEnd )  // Copy rest of right half
        tmpArray.push_back(a[ rightPos++ ]);
    
    // Copy tmpArray back
    for( int i = 0; i < numElements; i++, rightEnd-- )
        a[ rightEnd ] = tmpArray[ rightEnd ];
}


template <class Comparable>
void quicksort( vector<Comparable> & a )
{
    quicksort( a, 0, a.size( ) - 1 );
}


template <class Comparable>
inline void swap( Comparable & obj1, Comparable & obj2 )
{
    Comparable tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}


template <class Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right )
{
    int center = ( left + right ) / 2;
    if( a[ center ] < a[ left ] )
        swap( a[ left ], a[ center ] );
    if( a[ right ] < a[ left ] )
        swap( a[ left ], a[ right ] );
    if( a[ right ] < a[ center ] )
        swap( a[ center ], a[ right ] );
    
    // Place pivot at position right - 1
    swap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}


template <class Comparable>
void quicksort( vector<Comparable> & a, int left, int right )
{
    if( left + 10 <= right )
    {
        Comparable pivot = median3( a, left, right );
        
        // Begin partitioning
        int i = left, j = right - 1;
        for( ; ; )
        {
            while( a[ ++i ] < pivot ) { }
            while( pivot < a[ --j ] ) { }
            if( i < j )
                swap( a[ i ], a[ j ] );
            else
                break;
        }
        
        swap( a[ i ], a[ right - 1 ] );  // Restore pivot
        
        quicksort( a, left, i - 1 );     // Sort small elements
        quicksort( a, i + 1, right );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}

template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
    for( int p = left + 1; p <= right; p++ )
    {
        Comparable tmp = a[ p ];
        int j;
        
        for( j = p; j > left && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}

template <class Comparable>
class Pointer
{
public:
    Pointer( Comparable *rhs = NULL ) : pointee( rhs ) { }
    
    bool operator<( const Pointer & rhs ) const
    { return *pointee < *rhs.pointee; }
    operator Comparable * ( ) const
    { return pointee; }
private:
    Comparable *pointee;
};


#endif
