//
//  AVL.h
//  HW5_v1
//
//  Created by Canol Tasgin on 5/18/20.
//  Copyright © 2020 Canol Tasgin. All rights reserved.
//

/*
A binary tree class with these available public operations:
.findMin()              -->  Finds and returns the minimum element
.findMax()              -->  Finds and returns the maximum element
.find(x)                -->  Finds and returns the element x
.isEmpty()              -->  Returns true if tree is empty
.printTree()            -->  Prints the contact names in tree
.makeEmpty()            -->  Clears all nodes
.insert(x)              -->  Inserts new element x into tree
.remove(x)              -->  Removes element x from tree
.balanceCheck()         -->  Checks the height difference of tree and prints related information
.searchAvl(x)              -->  Finds the elements that includes x at the beginning of their "contact name" part and prints the all information of those contacts
.InOrderPrintToFile()   -->  Prints tree In Order from to a text file named "phonebookInOrderBST.txt"
.PreOrderPrintToFile()  -->  Prints tree Pre Order from to a text file named "phonebookPreOrderBST.txt"
.DrawTreeToFile()       -->  Draws the file into a text file named "phonebookTreeBST.txt"
 */

#ifndef avl_h
#define avl_h
template <class Comparable>
class AvlTree;

template <class Comparable>
class AvlNode
{
    Comparable     element;
    AvlNode           *left;
    AvlNode           *right;
    int                height;        ///height of the node
    
    AvlNode( const Comparable & theElement,
            AvlNode *lt, AvlNode *rt, int h = 0 )
    : element( theElement ), left( lt ), right( rt ), height( h ) { }
    
    friend class AvlTree<Comparable>;
};

template <class Comparable>
class AvlTree
{
public:        // General information about public functions are given above
    
    explicit AvlTree( const Comparable & notFound );
    AvlTree( const AvlTree & rhs );
    ~AvlTree( );
    
    const Comparable & findMin( ) const;
    const Comparable & findMax( ) const;
    const Comparable & find( const Comparable & x ) const;
    bool isEmpty( ) const;
    void printTree( ) const;
    
    void balanceCheck() const;
    
    bool isBalanced()const;
    
    void makeEmpty( );
    void insert( const Comparable & x );
    void remove( const Comparable & x );
    
    const AvlTree & operator=( const AvlTree & rhs );
    
    void searchAvl( const Comparable & x ) const;
    
    void InOrderPrintToFile( ) const;
    void PreOrderPrintToFile() const;
    void DrawTreeToFile() const;
    
private:     //DETAILED INFORMATION ABOUT FUNCTIONS ARE MOSTLY THE SAME WITH "bst.h" FUNCTIONS. CHECK bst.h FOR FUNCTIONS WITH SAME NAMES
    
    void DrawTreeToFile(const std::string s,AvlNode<Comparable> *t,bool left ) const;
    void PreOrderPrintToFile(AvlNode<Comparable> *t ) const;
    void InOrderPrintToFile( AvlNode<Comparable> *t ) const;
    
    void searchAvl( const Comparable & x, AvlNode<Comparable> *t) const;
    
    AvlNode<Comparable> *root;
    const Comparable ITEM_NOT_FOUND;
    
    const Comparable & elementAt( AvlNode<Comparable> *t ) const;
    
    void insert( const Comparable & x, AvlNode<Comparable> * & t ) const;
    void remove(const Comparable & x, AvlNode<Comparable> * & t ) const;
    
    AvlNode<Comparable> * findMin( AvlNode<Comparable> *t ) const;
    AvlNode<Comparable> * findMax( AvlNode<Comparable> *t ) const;
    AvlNode<Comparable> * find( const Comparable & x, AvlNode<Comparable> *t )
    const;
    void makeEmpty( AvlNode<Comparable> * & t ) const;
    void printTree( AvlNode<Comparable> *t ) const;
    AvlNode<Comparable> * clone( AvlNode<Comparable> *t ) const;
    
    void balanceCheck( AvlNode<Comparable> *t ) const;
    
    bool isBalanced( AvlNode<Comparable> *t ) const;
    
    int height( AvlNode<Comparable> *t ) const;
    int max( int lhs, int rhs ) const;
    void rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const;
    void rotateWithRightChild( AvlNode<Comparable> * & k1 ) const;
    void doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const;
    void doubleWithRightChild( AvlNode<Comparable> * & k1 ) const;
};

#include <iostream>
#include <string>
#include "BinaryTree.h"
using namespace std;

ofstream fileAvl("phonebookInOrderAVL.txt.txt");
ofstream filePreAvl("phonebookPreOrderAVL.txt.txt");
ofstream fileTreeAvl("phonebookTreeAVL.txt");



template <class Comparable>
void AvlTree<Comparable>::DrawTreeToFile(const string s,AvlNode<Comparable> *t,bool left ) const
{
    if(t!= NULL)
    {
        fileTreeAvl<<s;
        if (left)
            fileTreeAvl<<"|--";
        else
            fileTreeAvl<<"|__";
        
        fileTreeAvl<<t->element.fullcontactName<<endl;
        
        DrawTreeToFile(s + (left ? "│   " : "    "),t->left,true);
        
        DrawTreeToFile(s + (left ? "│   " : "    "),t->right,false);
    }
    
}
template <class Comparable>
void AvlTree<Comparable>::DrawTreeToFile( ) const
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    
    else
        DrawTreeToFile("", root,false );
}



template <class Comparable>
void AvlTree<Comparable>::PreOrderPrintToFile(AvlNode<Comparable> *t ) const
{
    
    if( t != NULL )
    {
        
        string contact=t->element.fullcontactName+" "+t->element.phoneNo+" "+t->element.contactAdress;
        filePreAvl << contact << endl;
        contact="";
        PreOrderPrintToFile( t->left );
        PreOrderPrintToFile( t->right );
        
    }
    
}

template <class Comparable>
void AvlTree<Comparable>::PreOrderPrintToFile( ) const
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    
    else
        PreOrderPrintToFile( root );
}


template <class Comparable>
void AvlTree<Comparable>::InOrderPrintToFile(AvlNode<Comparable> *t ) const
{
    
    if( t != NULL )
    {
        
        InOrderPrintToFile( t->left );
        string contact=t->element.fullcontactName+" "+t->element.phoneNo+" "+t->element.contactAdress;
        fileAvl << contact << endl;
        contact="";
        InOrderPrintToFile( t->right );
        
    }
    
}

template <class Comparable>
void AvlTree<Comparable>::InOrderPrintToFile( ) const
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    
    else
        InOrderPrintToFile( root );
}



template <class Comparable>
void AvlTree<Comparable>::searchAvl( const Comparable & x, AvlNode<Comparable> *t ) const
{
    
    if( t == NULL )
        ;
    
    else if( t->element.fullcontactName.substr(0,x.fullcontactName.length()) < x.fullcontactName){
        if(t->right!=NULL)
            searchAvl( x, t->right);
        else
            ;
    }
    
    else if( x.fullcontactName < t->element.fullcontactName.substr(0,x.fullcontactName.length())){
        if(t->left!=NULL)
            searchAvl( x, t->left);
        else
            ;
    }
    
    else if( t->element.fullcontactName.substr(0,x.fullcontactName.length()).find(x.fullcontactName)==0){
        
        //cout<<t->element.fullcontactName+" "+t->element.phoneNo+" "+t->element.contactAdress<<endl;    //--> Since i dont need to print contact twice,                                                                                                                                 I've commented out contact information in this header.
        if(t->left!=NULL)
            searchAvl( x, t->left);
        else
            ;
        
    }
    
    else
        ;
    
}

template <class Comparable>
void AvlTree<Comparable>::searchAvl( const Comparable & x ) const
{
    searchAvl( x , root );
}

template <class Comparable>
AvlTree<Comparable>::AvlTree(const Comparable & notFound) :ITEM_NOT_FOUND(notFound), root(NULL){}

template <class Comparable>
const AvlTree<Comparable> &AvlTree<Comparable>::operator=( const AvlTree<Comparable> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );
        root = clone( rhs.root );
    }
    return *this;
}

template <class Comparable>
AvlNode<Comparable> *AvlTree<Comparable>::clone( AvlNode<Comparable> * t ) const
{
    if( t == NULL )
        return NULL;
    else
        return new AvlNode<Comparable>( t->element, clone( t->left ),
                                       clone( t->right ), t->height );
}

template <class Comparable>
bool AvlTree<Comparable>::isBalanced()const
{
    AvlNode<Comparable> * temp = nullptr;
    return isBalanced(temp);
}

template <class Comparable>
void AvlTree<Comparable>::balanceCheck() const{
    balanceCheck(root);
}

template <class Comparable>
void AvlTree<Comparable>::balanceCheck( AvlNode<Comparable> *t ) const{
    
    if(t==NULL){
        cout<<"The tree is balanced"<<endl;
        cout<<endl;
    }
    else if ((height(t->left)-height(t->right)) <= 1 && isBalanced(t->left) && isBalanced(t->right)){
        
        cout<<"The tree is balanced"<<endl;
        cout<<endl;
        cout<<"The heights of AVL are for left: "<< height(t->left) << " and right: "<< height(t->right) <<endl;
        cout<<endl;
    }
    else
        cout<<"The tree is not balanced";
}

template <class Comparable>
bool AvlTree<Comparable>::isBalanced( AvlNode<Comparable> *t ) const{
    if(t == NULL)
        return 1;
    int leftHeight,rightHeight;
    leftHeight = height(t->left);
    rightHeight = height(t->right);
    if ((leftHeight-rightHeight) <= 1 && isBalanced(t->left) && isBalanced(t->right))
        return 1;
    return 0;
}

template <class Comparable>
int AvlTree<Comparable>::height( AvlNode<Comparable> *t ) const
{
    if (t == NULL)
        return 0;
    
    return t->height;
}

template <class Comparable>
int AvlTree<Comparable>::max( int lhs, int rhs ) const
{
    if (lhs > rhs)
        return lhs;
    
    return rhs;
}

template <class Comparable>
const Comparable & AvlTree<Comparable>::elementAt( AvlNode<Comparable> *t)const
{
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}

template <class Comparable>
const Comparable & AvlTree<Comparable>::find( const Comparable & x ) const
{
    return elementAt( find( x, root ) );
}


template <class Comparable>
AvlNode<Comparable> *
AvlTree<Comparable>::find( const Comparable & x, AvlNode<Comparable> *t ) const
{
    while( t != NULL )
        if( x < t->element )
            t = t->left;
        else if( t->element < x )
            t = t->right;
        else
            return t;    // Match
    
    return NULL;   // No match
}


template <class Comparable>
const Comparable & AvlTree<Comparable>::findMin( ) const
{
    return elementAt( findMin( root ) );
}

template <class Comparable>
const Comparable & AvlTree<Comparable>::findMax( ) const
{
    return elementAt( findMax( root ) );
}

template <class Comparable>
bool AvlTree<Comparable>::isEmpty( ) const
{
    return root == NULL;
}


template <class Comparable>
AvlNode<Comparable> *
AvlTree<Comparable>::findMin( AvlNode<Comparable> *t )const
{
    if( t == NULL )
        return NULL;
    
    if( t->left == NULL )
        return t;
    
    return findMin( t->left );
}

template <class Comparable>
AvlNode<Comparable> *AvlTree<Comparable>::findMax( AvlNode<Comparable> *t )const
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    
    return t;
    
}


template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild( AvlNode<Comparable> * & k1 ) const
{
    AvlNode<Comparable> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
}

template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const
{
    rotateWithRightChild( k3->left );
    rotateWithLeftChild( k3 );
}

template <class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const
{
    AvlNode<Comparable> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    k2 = k1;
}

template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild( AvlNode<Comparable> * & k1 ) const
{
    rotateWithLeftChild( k1->right );
    rotateWithRightChild( k1 );
}


template <class Comparable>
void AvlTree<Comparable>::remove( const Comparable & x )
{
    remove( x, root );
}

template <class Comparable>
void AvlTree<Comparable>::remove(const Comparable & x, AvlNode<Comparable> * & t) const
{
    if( t == NULL )
        return;
    else
        if( x < t->element )
            remove( x, t->left);
        else
            if( t->element < x )
                remove( x, t->right);
            else /// found x
            {
                if(t->right != NULL && t->left != NULL) /// if two children
                {
                    t->element = findMin(t->right)->element;  /// set this node to minimum of right subtree
                    remove(t->element, t->right);  /// remove the duplicated element
                }
                else
                {
                    AvlNode<Comparable> * temp = NULL;
                    if(t->left)
                        temp = t->left;
                    else
                        if(t->right)
                            temp = t->right;
    
                    delete t;
                    t = temp;
                }
            }
   /// Fixing the heights of AVL tree
    if(t)
    {
        if( height( t->left ) - height( t->right ) == 2 )  /// if left side is heavy
        {
            if( height(t->left->left) >  height(t->left->right))
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        }
        else
            if( height( t->left ) - height( t->right ) == -2 ) ///  if right side is heavy
            {
                if( height(t->right->right) > height(t->right->left))
                    rotateWithRightChild( t );
                else
                    doubleWithRightChild( t );
            }
    }
    if(t)
        t->height = max(height(t->left), height( t->right)) + 1;
}



template <class Comparable>
void AvlTree<Comparable>::makeEmpty( )
{
    makeEmpty( root );
}

template <class Comparable>
void AvlTree<Comparable>::makeEmpty( AvlNode<Comparable> * & t ) const
{
    if( t != NULL )
    {
        
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
        
    }
    
    t = NULL;
    
}

template <class Comparable>

void AvlTree<Comparable>::printTree( ) const
{
    
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    
    else
        printTree( root );
    
}

template <class Comparable>
void AvlTree<Comparable>::printTree( AvlNode<Comparable> *t ) const
{
    if( t != NULL )
    {
        printTree( t->left );
        cout << t->element << endl;
        printTree( t->right );
    }
}

template <class Comparable>
AvlTree<Comparable>::~AvlTree( )
{
    makeEmpty( );
}

template <class Comparable>
AvlTree<Comparable>::
AvlTree( const AvlTree<Comparable> & rhs ) :root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{
    
    *this = rhs;
    
}

template <class Comparable>
void AvlTree<Comparable>::insert( const Comparable & x )
{
    insert( x, root );
}

template <class Comparable>
void AvlTree<Comparable>::insert( const Comparable & x, AvlNode<Comparable> * & t ) const  ///Inserts elements the tree with height arrangements necessary for making an AVL tree
{
    if(t == NULL)
    {
        t = new AvlNode<Comparable>(x, NULL, NULL);
        t->height = 0;
    }
    
    else if(x < t->element)
    {
        insert(x, t->left);
        if(height(t->left) - height(t->right) == 2)
        {
            if(x < t->left->element)
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
    }
    else if(x > t->element)
    {
        insert(x, t->right);
        if(height(t->right) - height(t->left) == 2)
        {
            if(x > t->right->element)
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
    }
    
    t->height = max(height(t->left), height(t->right))+1;
    
}

#endif /* avl_h */
