//
//  BinaryTree.h
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
 .search(x)              -->  Finds the elements that includes x at the beginning of their "contact name" part and prints the all information of those contacts
 .InOrderPrintToFile()   -->  Prints tree In Order from to a text file named "phonebookInOrderBST.txt"
 .PreOrderPrintToFile()  -->  Prints tree Pre Order from to a text file named "phonebookPreOrderBST.txt"
 .DrawTreeToFile()       -->  Draws the file into a text file named "phonebookTreeBST.txt"
 */

#ifndef bst_h
#define bst_h
template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;
    int height;                 ///height of the node
    
    BinaryNode( const Comparable & theElement,BinaryNode *lt, BinaryNode *rt,int h = 0 ): element( theElement ), left( lt ), right( rt ),height( h ) { }
    
    friend class BinarySearchTree<Comparable>;
};


template <class Comparable>
class BinarySearchTree
{
public:                     // General information about public functions are given above
    
    explicit BinarySearchTree( const Comparable & notFound );
    
    BinarySearchTree( const BinarySearchTree & rhs );
    
    ~BinarySearchTree( );
    
    const Comparable & findMin( ) const;
    
    const Comparable & findMax( ) const;
    
    const Comparable & find( const Comparable & x ) const;
    
    bool isEmpty( ) const;
    
    void printTree( ) const;
    
    void makeEmpty( );
    
    void insert( const Comparable & x );
    
    void remove( const Comparable & x );
    
    const BinarySearchTree & operator=( const BinarySearchTree & rhs );
    
    void balanceCheck() const;
    
    void search( const Comparable & x ) const;
    
    
    void InOrderPrintToFile( ) const;
    void PreOrderPrintToFile() const;
    
    void DrawTreeToFile() const;
    
private:      //DETAILED INFORMATION ABOUT FUNCTIONS ARE GIVEN BELOW
    
    void DrawTreeToFile(const std::string s,BinaryNode<Comparable> *t,bool left ) const;
    
    void PreOrderPrintToFile(BinaryNode<Comparable> *t ) const;
    void InOrderPrintToFile( BinaryNode<Comparable> *t ) const;
    
    
    void search( const Comparable & x, BinaryNode<Comparable> *t) const;
    
    BinaryNode<Comparable> *root;
    
    const Comparable ITEM_NOT_FOUND;
    
    const Comparable & elementAt( BinaryNode<Comparable> *t ) const;
    
    void insert( const Comparable & x, BinaryNode<Comparable> * & t ) const;
    
    void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
    
    BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
    
    BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
    
    BinaryNode<Comparable> * find( const Comparable & x, BinaryNode<Comparable> *t  ) const;
    
    void makeEmpty( BinaryNode<Comparable> * & t ) const;
    
    void printTree( BinaryNode<Comparable> *t ) const;
    
    BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;
    
    int height( BinaryNode<Comparable> *t ) const;
    
    bool isBalanced( BinaryNode<Comparable> *t ) const;
    
    void balanceCheck( BinaryNode<Comparable> *t ) const;
};

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>
using namespace std;
ofstream file("phonebookInOrderBST.txt");
ofstream filePre("phonebookPreOrderBST.txt");
ofstream fileTree("phonebookTreeBST.txt");            ///created necessary .txt files

struct contactInfo                                    ///struct for holding contact information
{
    string fullcontactName;
    string phoneNo;
    string contactAdress;
//                        -NECESSARY OPERATORS FOR USING THIS STRUCT-
    bool operator> (const contactInfo  &c) const {return fullcontactName > c.fullcontactName;}
    bool operator>=(const contactInfo  &c) const {return fullcontactName >= c.fullcontactName;}
    bool operator==(const contactInfo  &c) const {return fullcontactName == c.fullcontactName;}
    bool operator!=(const contactInfo  &c) const {return fullcontactName != c.fullcontactName;}
    bool operator<=(const contactInfo  &c) const {return fullcontactName <= c.fullcontactName;}
    bool operator< (const contactInfo  &c) const {return fullcontactName < c.fullcontactName;}
    
    contactInfo(string name, string no, string addr)    ///constructor of the struct
    {
        fullcontactName = name;
        phoneNo = no;
        contactAdress = addr;
    }
    
};

template <class Comparable>
void BinarySearchTree<Comparable>::DrawTreeToFile(const string s,BinaryNode<Comparable> *t,bool left ) const   /// Drawing the tree (private)
{
    if(t!= NULL)
    {
        fileTree<<s;                                     ///prints the string s
        if (left)                                        ///if bool left is true which means if left child print first, else print second
            fileTree<<"|--";
        else
            fileTree<<"|__";
        
        fileTree<<t->element.fullcontactName<<endl;      ///print the name of contact
        
        DrawTreeToFile(s + (left ? "│   " : "    "),t->left,true);   ///if left is true send the first string + current s, else the second one + s (For arranging spaces and lines)
        
        DrawTreeToFile(s + (left ? "│   " : "    "),t->right,false);
    }
    
}

template <class Comparable>
void BinarySearchTree<Comparable>::DrawTreeToFile( ) const    /// Drawing the tree (public)
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    
    else
        DrawTreeToFile("", root,false );                      /// Sends necessary elements to private version
}

template <class Comparable>
void BinarySearchTree<Comparable>::PreOrderPrintToFile(BinaryNode<Comparable> *t ) const     ///Prints tree Pre Order form to a .txt file (private) - Traversing the tree
{
    
    if( t != NULL )
    {
        
        string contact=t->element.fullcontactName+" "+t->element.phoneNo+" "+t->element.contactAdress;
        filePre << contact << endl;            ///prints out the contact
        contact="";
        PreOrderPrintToFile( t->left );        ///goes to left child
        PreOrderPrintToFile( t->right );       ///goes to right child
        
    }
    
}

template <class Comparable>
void BinarySearchTree<Comparable>::PreOrderPrintToFile( ) const  ///Prints tree Pre Order form to a .txt file (public)
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    
    else
        PreOrderPrintToFile( root );                            /// Sends necessary elements to private version
}


template <class Comparable>
void BinarySearchTree<Comparable>::InOrderPrintToFile(BinaryNode<Comparable> *t ) const    ///Prints tree In Order form to a .txt file (private) - Traversing the tree
{
    
    if( t != NULL )
    {
        
        InOrderPrintToFile( t->left );      ///goes to left child
        string contact=t->element.fullcontactName+" "+t->element.phoneNo+" "+t->element.contactAdress;
        file << contact << endl;            ///prints out the contact
        contact="";
        InOrderPrintToFile( t->right );     ///goes to right child
        
    }
    
}

template <class Comparable>
void BinarySearchTree<Comparable>::InOrderPrintToFile( ) const   ///Prints tree In Order form to a .txt file (public)
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    
    else
        InOrderPrintToFile( root );                              /// Sends necessary elements to private version
}

template <class Comparable>
void BinarySearchTree<Comparable>::search( const Comparable & x, BinaryNode<Comparable> *t ) const  /// Searchs for contacts that includes x in the beginning their names (private)
{
    
    if( t == NULL )
        ;
    
    else if( t->element.fullcontactName.substr(0,x.fullcontactName.length()) < x.fullcontactName){   /// if current nodes contact name is smaller than x, go to right child
        if(t->right!=NULL)
            search( x, t->right);
        else
            ;
    }
    
    else if( x.fullcontactName < t->element.fullcontactName.substr(0,x.fullcontactName.length())){   /// if current nodes contact name is larger than x, go to left child
        if(t->left!=NULL)
            search( x, t->left);
        else
            ;
    }
    
    else if( t->element.fullcontactName.substr(0,x.fullcontactName.length()).find(x.fullcontactName)==0){  /// if current nodes contact name includes x in its beginning, print it and check other childs
        //cout<<t->element.fullcontactName+" "+t->element.phoneNo+" "+t->element.contactAdress<<endl;
        if(t->left!=NULL)
            search( x, t->left);
        else if(t->right!=NULL)
            search( x, t->right);
        else
            ;
        
    }
    
    else
        ;
    
}

template <class Comparable>
void BinarySearchTree<Comparable>::search( const Comparable & x ) const   /// Searchs for contacts that includes x in the beginning their names (private)
{
    search( x, root );
}


template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable & notFound) :ITEM_NOT_FOUND(notFound), root(NULL){}


/**
 * Deep copy.
 */
template <class Comparable>
const BinarySearchTree<Comparable> &
BinarySearchTree<Comparable>::
operator=( const BinarySearchTree<Comparable> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );
        root = clone( rhs.root );
    }
    return *this;
}


template <class Comparable>
void BinarySearchTree<Comparable>::balanceCheck() const{          ///Balance Check for tree (public)
    balanceCheck(root);
}

template <class Comparable>
void BinarySearchTree<Comparable>::balanceCheck( BinaryNode<Comparable> *t ) const{   ///Balance Check for tree (private)
    
    if(t==NULL){
        cout<<"The tree is balanced"<<endl;
        cout<<endl;
        cout<<"The heights of BST are for left: 0 and right: 0"<<endl;
    }
    else if ((height(t->left)-height(t->right)) <= 1 && isBalanced(t->left) && isBalanced(t->right)){     ///if height difference is smaller or equals to 1 and both sides are balanced
        
        cout<<"The tree is balanced"<<endl;
        cout<<endl;
        cout<<"The heights of BST are for left: "<< height(t->left) << " and right: "<< height(t->right) <<endl;
    }
    else
    {
        cout<<"The tree is not balanced"<<endl;
        cout<<endl;
        cout<<"The heights of BST are for left: "<< height(t->left) << " and right: "<< height(t->right) <<endl;
    }
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isBalanced( BinaryNode<Comparable> *t ) const{       ///checks if the node is balanced by checking the height difference between left and right
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
int BinarySearchTree<Comparable>::height( BinaryNode<Comparable> *t ) const      ///height information
{
    if (t == NULL)
        return 0;
    
    return t->height;
}


template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::elementAt( BinaryNode<Comparable> *t)const       ///returns the element at the current node
{
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}



template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin( ) const    ///finds the minimum element (public)
{
    return elementAt( findMin( root ) );
}


template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t )const  ///finds the minimum element (private)
{
    if( t == NULL )
        return NULL;
    
    if( t->left == NULL )
        return t;
    
    return findMin( t->left );
}

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax( ) const ///finds the maximum element (public)
{
    return elementAt( findMax( root ) );
}

template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t )const   ///finds the maximum element (private)
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    
    return t;
    
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const {           ///checks if node is empty, returns true if empty
    BinaryNode<Comparable> * temp = root;
    if (temp->element == ITEM_NOT_FOUND) {
        return true;
    }
    else
        return false;
}

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::find( const Comparable & x ) const       ///finds and returns the element x (public)
{
    return elementAt( find( x, root ) );
}

template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::find( const Comparable & x, BinaryNode<Comparable> *t ) const     ///finds and returns the element x (private)
{
    if( t == NULL )
        return NULL;
    else if( x < t->element )     ///compare with the node with x, if bigger than x, go to left child
        return find( x, t->left );
    else if( t->element < x )     ///compare with the node with x, if smaller than x, go to right child
        return find( x, t->right );
    else
        return t;                 /// Match
}

template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x ) ///inserts the element x (public)
{
    insert( x, root );
}

template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x, BinaryNode<Comparable> * & t ) const  ///inserts the element x (private)
{
    if( t == NULL ){                   /// create a new node at the right place
        t = new BinaryNode<Comparable>( x, NULL, NULL );
        t->height = 0;
    }
    else if( x < t->element )
        insert( x, t->left );          /// insert at the left or
    else if( t->element < x )
        insert( x, t->right );         /// right subtree
    else
        ;                              /// Duplicate; do nothing
    t->height = max(height(t->left), height(t->right))+1;
}

template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x ) ///removes the element x (public)
{
    remove( x, root );
}

template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x, BinaryNode<Comparable> * & t )const ///removes the element x (private)
{
    if( t == NULL )
        return;                   /// Item not found; do nothing
    
    if( x < t->element )
        remove( x, t->left );
    
    else if( t->element < x )
        remove( x, t->right );
    
    else if( t->left != NULL && t->right != NULL ) /// Two children
    {
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    }
    
    else /// one or no children
    {
        BinaryNode<Comparable> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
    
}

template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( )  ///clears the tree (public)
{
    makeEmpty( root );
}

template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( BinaryNode<Comparable> * & t ) const  ///clears the tree (private)
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
void BinarySearchTree<Comparable>::printTree(BinaryNode<Comparable> *t ) const  ///prints the contact names in the tree (private)
{
    
    if( t != NULL )
    {
        printTree( t->left );
        cout << t->element.fullcontactName << endl;
        printTree( t->right );
    }
    
}

template <class Comparable>
void BinarySearchTree<Comparable>::printTree( ) const      ///prints the contact names in the tree (public)
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    
    else
        printTree( root );
}



template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( )
{
    makeEmpty( );
}

template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) :root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{
    
    *this = rhs;
    
}


template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::clone( BinaryNode<Comparable> * t ) const
{
    if( t == NULL )
        return NULL;
    else
        return new
        BinaryNode<Comparable>( t->element, clone( t->left ), clone( t->right ) );
}

#endif /* bst_h */

