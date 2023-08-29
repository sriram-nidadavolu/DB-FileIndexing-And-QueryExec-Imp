//===----------------------------------------------------------------------===//
//
//                         Rutgers CS539 - Database System
//                         ***DO NO SHARE PUBLICLY***
//
// Identification:   include/b_plus_tree.h
//
// Copyright (c) 2022, Rutgers University
//
//===----------------------------------------------------------------------===//
#pragma once
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "para.h"
#include <cmath>
#include <stack>

using namespace std;

// Value structure we insert into BPlusTree
struct RecordPointer {
  int page_id;
  int record_id;
  RecordPointer() : page_id(0), record_id(0){};
  RecordPointer(int page, int record) : page_id(page), record_id(record){};
};


// BPlusTree Node
class Node {
public:
  Node(bool leaf) : key_num(0), is_leaf(leaf) {};
  bool is_leaf;
  int key_num;
  KeyType keys[MAX_FANOUT - 1];
};

// internal b+ tree node
class InternalNode : public Node {
public:
  InternalNode() : Node(false) {};
  Node * children[MAX_FANOUT];
};

class LeafNode : public Node {
public:
  LeafNode() : Node(true) {};
  RecordPointer pointers[MAX_FANOUT - 1];
  // pointer to the next/prev leaf node
  LeafNode *next_leaf = NULL;
  LeafNode *prev_leaf = NULL;
};

struct SubNode{
    KeyType key;
    Node * leftChild;
    Node * rightChild;
    SubNode() : key(0), leftChild(NULL), rightChild(NULL){};
    SubNode(int key, Node * leftChild, Node * rightChild): key(key), leftChild(leftChild), rightChild(rightChild){};
};

struct ParPosHolder{
    int childPos;
    Node * ParentNode;
    ParPosHolder() : childPos(0), ParentNode(NULL){};
    ParPosHolder(int childPos, Node * ParentNode): childPos(childPos), ParentNode(ParentNode){};
};

/**
 * Main class providing the API for the Interactive B+ Tree.
 *
 * Implementation of simple b+ tree data structure where internal pages direct
 * the search and leaf pages contain record pointers
 * (1) We only support (and test) UNIQUE key
 * (2) Support insert & remove
 * (3) Support range scan, return multiple values.
 * (4) The structure should shrink and grow dynamically
 */

class BPlusTree {
 public:
  BPlusTree(){
      maxChild = MAX_FANOUT;
      minChild = ((MAX_FANOUT/2)+(MAX_FANOUT%2));
      maxKeys = MAX_FANOUT-1;
      minKeys = (MAX_FANOUT/2+(MAX_FANOUT%2))-1;
      leafMinKeys = ((MAX_FANOUT-1)/2+((MAX_FANOUT-1)%2));
      root = NULL;
      
  };
    
    
    
    
//Helper functions for insertion
    int find_index(int arr[], int n, int K);
    Node * findLeafNodeInsert(const KeyType &key, stack<Node *> &st);
    SubNode * nonSplitInsertLeaf(const KeyType &key,const RecordPointer &value, Node * curr);
    SubNode * SplitInsertLeaf(const KeyType &key,const RecordPointer &value, Node * curr);
    SubNode * nonSplitInsertIn(SubNode * subNode, Node * curr);
    SubNode * SplitInsertIn(SubNode * subNode, Node * curr);
    
    
    
    
//Helper funcions for delete
    void update_index(const KeyType &key);
    Node * findLeafNodeTD(const KeyType &key, stack<ParPosHolder *> &st);
    int findElementPos(int arr[], int n, int K);
    bool delKeyLeafNode(Node * curr, const KeyType &key);
    bool borrowLeafNode(Node * curr, stack<ParPosHolder *> &st);
    bool mergeLeafNode(Node * curr, stack<ParPosHolder *> &st);
    
    
    bool borrowIntNode(Node * curr, stack<ParPosHolder *> &st);
    bool mergeIntNode(Node * curr, stack<ParPosHolder *> &st);
    
    
    
    
    
  // Returns true if this B+ tree has no keys and values
  bool IsEmpty() const;

  // Insert a key-value pair into this B+ tree.
  bool Insert(const KeyType &key, const RecordPointer &value);

  // Remove a key and its value from this B+ tree.
  void Remove(const KeyType &key);

  // return the value associated with a given key
  bool GetValue(const KeyType &key, RecordPointer &result);

  // return the values within a key range [key_start, key_end) not included key_end
  void RangeScan(const KeyType &key_start, const KeyType &key_end,
                 std::vector<RecordPointer> &result);

 private:
  // pointer to the root node.
  Node *root;
    int maxChild;
    int minChild;
    int maxKeys;
    int minKeys;
    int leafMinKeys;
//    RecordPointer zero_record();
};
