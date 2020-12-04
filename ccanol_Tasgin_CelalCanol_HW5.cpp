//
//  main.cpp
//  HW5_v1
//
//  Created by Canol Tasgin on 5/18/20.
//  Copyright © 2020 Canol Tasgin. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include <chrono>
#include <cctype>
#include <vector>
#include "AVL.h"
#include "BinaryTree.h"
#include "Sorting.h"

using namespace std;

bool compare(long double a, long double b){ //Comparing times of operations
    if (a > b)
        return 1;
    else
        return 0;
}

void SearchAContact(BinarySearchTree<contactInfo>binaryTree,AvlTree<contactInfo>avlTree,vector<contactInfo>ins,vector<contactInfo>qck,vector<contactInfo>mrg,vector<contactInfo>heap){
    
    string contactName,temp,tempName;
    cout<<"Please enter the word to be queried :"<<endl;
    
    bool b=1;
    while(getline(cin,tempName)&&b){               //took 2 strings as input at the same time
        b=0;
    }
    contactName=tempName;
    
    string nameC,surnameC;
    stringstream s;
    s<<contactName;
    s>>nameC>>surnameC;                            //splitted the string
    
    //Name and surname letter size arrangements between "START" and "END" comments
    //          START
    
    if (nameC[0]<=122 && nameC[0]>=97)
        nameC[0]=nameC[0]-32;
    if (surnameC[0]<=122 && surnameC[0]>=97)
        surnameC[0]=surnameC[0]-32;
    
    for (int i=1;i<=nameC.length();i++){
        if (nameC[i]<=122 && nameC[i]>=97)
            nameC[i]=nameC[i]-32;
    }
    
    for (int j=1;j<=surnameC.length();j++){
        if (surnameC[j]<=122 && surnameC[j]>=97)
            surnameC[j]=surnameC[j]-32;
    }
    
    string spaceStr;
    
    if (!surnameC.empty())
        spaceStr=" ";
    
    temp=nameC+spaceStr+surnameC;
    
    for (int i=1;i<=nameC.length();i++){
        nameC[i]=nameC[i]+32;
    }
    
    for (int j=1;j<=surnameC.length();j++){
        surnameC[j]=surnameC[j]+32;
    }
    
    //           END
    
    contactName=nameC+spaceStr+surnameC;
    cout<<endl;
    
    //Sorting operations to vectors are below
    
    auto startInsert = std::chrono::steady_clock::now();
    insertionSort(ins);
    auto endInsert = std::chrono::steady_clock::now();
    
    auto startHeap = std::chrono::steady_clock::now();
    heapsort( heap );
    auto endHeap = std::chrono::steady_clock::now();
    
    auto startMerge = std::chrono::steady_clock::now();
    mergeSort( mrg );
    auto endMerge = std::chrono::steady_clock::now();
    
    auto startQuick = std::chrono::steady_clock::now();
    quicksort( qck );
    auto endQuick = std::chrono::steady_clock::now();
    
    
    string no,adress;
    contactInfo findContact = contactInfo(contactName,no,adress);         //a struct with Contact Name taken from user and 2 empty strings
    
    
    cout<<"Sorting the vector copies\n======================================"<<endl;
    cout<<"Quick Sort Time: "<< chrono::duration_cast<chrono::nanoseconds>(endQuick - startQuick).count() <<" Nanoseconds"<<endl;
    cout<<"Insertion Sort Time: "<< chrono::duration_cast<chrono::nanoseconds>(endInsert - startInsert).count() <<" Nanoseconds"<<endl;
    cout<<"Merge Sort Time: "<< chrono::duration_cast<chrono::nanoseconds>(endMerge - startMerge).count() <<" Nanoseconds"<<endl;
    cout<<"Heap Sort Time: "<< chrono::duration_cast<chrono::nanoseconds>(endHeap - startHeap).count() <<" Nanoseconds"<<endl;
    
    //created these in order to divide them and calculate Speedups
    long double durationQuick, durationInsert, durationMerge, durationHeap;
    durationQuick = chrono::duration_cast<chrono::nanoseconds>(endQuick - startQuick).count();
    durationInsert = chrono::duration_cast<chrono::nanoseconds>(endInsert - startInsert).count();
    durationMerge = chrono::duration_cast<chrono::nanoseconds>(endMerge - startMerge).count();
    durationHeap = chrono::duration_cast<chrono::nanoseconds>(endHeap - startHeap).count();
  
    auto startBST = std::chrono::steady_clock::now();
    binaryTree.search(findContact);
    auto endBST = std::chrono::steady_clock::now();
    
    auto startAVL = std::chrono::steady_clock::now();
    avlTree.searchAvl(findContact);
    auto endAVL = std::chrono::steady_clock::now();
    
    auto startBS = std::chrono::steady_clock::now();
    for (int i = 0; i<qck.size();i++){
        
        if(qck[i].fullcontactName.substr(0,findContact.fullcontactName.length()) == findContact.fullcontactName )
            break;
        else
            ;
        
    }
    auto endBS = std::chrono::steady_clock::now();
    
    long double durationBST = chrono::duration_cast<chrono::nanoseconds>(endBST - startBST).count();
    long double durationAVL = chrono::duration_cast<chrono::nanoseconds>(endAVL - startAVL).count();
    long double durationBS = chrono::duration_cast<chrono::nanoseconds>(endBS - startBS).count();
    
    
    
    cout<<endl;
       cout<<"Searching for "<< findContact.fullcontactName <<"\n======================================"<<endl;
       cout<<"The search in BST took "<< chrono::duration_cast<chrono::nanoseconds>(endBST - startBST).count() <<" Nanoseconds"<<endl;
       cout<<"The search in AVL took "<< chrono::duration_cast<chrono::nanoseconds>(endAVL - startAVL).count() <<" Nanoseconds"<<endl;
       cout<<"Binary Search Time: "<< chrono::duration_cast<chrono::nanoseconds>(endBS - startBS).count() <<" Nanoseconds"<<endl;
    
    
    cout<<endl;
    cout<<"SpeedUps in search\n======================================"<<endl;
    
    if(compare(durationAVL,durationBST)==1)
        cout<<"(BST / AVL) SpeedUp  = "<< durationAVL/durationBST << endl;
    else
        cout<<"(BST / AVL) SpeedUp  = "<< durationBST/durationAVL << endl;
    
    if(compare(durationBS,durationAVL)==1)
        cout<<"(Binary Search / AVL) SpeedUp  = "<<durationBS/durationAVL<<endl;
    else
        cout<<"(Binary Search / AVL) SpeedUp  = "<<durationAVL/durationBS<<endl;
    
    if(compare(durationBS,durationBST)==1)
        cout<<"(Binary Search / BST) SpeedUp  = "<<durationBS/durationBST<<endl;
    else
         cout<<"(Binary Search / BST) SpeedUp  = "<<durationBS/durationBST<<endl;
    
    
    cout<<endl;
    
    cout<<"SpeedUps between Sorting Algorithms\n======================================"<<endl;
    if(compare(durationInsert,durationQuick)==1)
        cout<<"(Insertion Sort/ Quick Sort) SpeedUp = "<< durationInsert/durationQuick << endl;
    else
        cout<<"(Insertion Sort/ Quick Sort) SpeedUp = "<< durationQuick/durationInsert << endl;
    
    if(compare(durationMerge,durationQuick)==1)
           cout<<"(Merge Sort / Quick Sort) SpeedUp = "<< durationMerge/durationQuick << endl;
       else
           cout<<"(Merge Sort / Quick Sort) SpeedUp = "<< durationQuick/durationMerge << endl;
    
    if(compare(durationHeap,durationQuick)==1)
           cout<<"(Heap Sort / Quick Sort) SpeedUp = "<< durationHeap/durationQuick << endl;
       else
           cout<<"(Heap Sort / Quick Sort) SpeedUp = "<< durationQuick/durationHeap << endl;
    
}

int main() {
    
    string fileName, line, qWord;
    cout<<"Please enter the contact file name: "<<endl;
    cin>>fileName;
    
    contactInfo notFoundItem = contactInfo("","","");            //empty struct
    BinarySearchTree<contactInfo> binaryTree(notFoundItem);      //constructor for BST
    AvlTree <contactInfo> avlTree(notFoundItem);                 //constructor for AVL Tree
    
    ifstream input(fileName);
    
    while(getline(input,line)){                                  //BST creation from the file
        string name,surname,number,adress;
        stringstream ss;
        ss<<line;
        ss>>name>>surname>>number>>adress;                       //split the line into strings
        string space=" ";
        contactInfo temp(name+space+surname,number,adress);      //created a struct from the line
        binaryTree.insert(temp);
    }
    
    ifstream input2(fileName);
    
    while(getline(input2,line)){                                    //same operations for AVL tree
        
        string name,surname,number,adress;
        stringstream ss;
        ss<<line;
        ss>>name>>surname>>number>>adress;
        string space=" ";
        
        contactInfo temp(name+space+surname,number,adress);
        avlTree.insert(temp);
    }
    
    ifstream input3(fileName);
    vector<contactInfo>vInsertion;
    vector<contactInfo>vQuick;
    vector<contactInfo>vMerge;
    vector<contactInfo>vHeap;
    
    while(getline(input3,line)){                                    //same operations for AVL tree
        
        string name,surname,number,adress;
        stringstream ss;
        ss<<line;
        ss>>name>>surname>>number>>adress;
        string space=" ";
        
        contactInfo temp(name+space+surname,number,adress);
        vInsertion.push_back(temp);
        vQuick.push_back(temp);
        vMerge.push_back(temp);
        vHeap.push_back(temp);
    }
    
    SearchAContact(binaryTree, avlTree,vInsertion,vQuick,vMerge,vHeap);
    
    return 0;
}
