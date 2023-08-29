#include "include/b_plus_tree.h"


// My helper functions

//Insert helpers

Node * BPlusTree::findLeafNodeInsert(const int &key, stack<Node *> &st){
   Node * curr = root;
//    InternalNode * nd = (InternalNode *)(curr);
    while (!curr->is_leaf) {
        InternalNode * nd = static_cast<InternalNode *>(curr);
        int arrSize = curr->key_num;
        bool found = false;
        int i = 0;
        for( i = 0; i<arrSize;i++){
            if(key < curr->keys[i]){
                st.push(curr);
                curr = nd -> children[i];
                found = true;
                break;
            }
        }
        if(!found){
            st.push(curr);
            curr = nd -> children[i];
        }
    }
    return curr;
}

int BPlusTree::find_index(int arr[], int n, int K)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == K)
            return i;
        else if (arr[i] > K)
            return i;
    return n;
}

SubNode * BPlusTree::nonSplitInsertLeaf(const KeyType &key,const RecordPointer &value, Node * curr){
    LeafNode * curre = static_cast<LeafNode *>(curr);
    int index = find_index(curre->keys, curre->key_num, key);
    vector<KeyType> keyss;
    vector<RecordPointer> pointerss;
    for(int i=0;i<curre->key_num;i++){
        keyss.push_back(curre->keys[i]);
        pointerss.push_back(curre->pointers[i]);
    }
    keyss.insert(keyss.begin()+index, key);
    pointerss.insert(pointerss.begin()+index, value);
    curre->key_num++;
    for(int i=0;i<curre->key_num;i++){
        curre->keys[i] = keyss.at(i);
        curre->pointers[i] = pointerss.at(i);
    }
    return NULL;
}
SubNode * BPlusTree::SplitInsertLeaf(const KeyType &key,const RecordPointer &value, Node * curr){
    LeafNode * rightCh = new LeafNode();
    LeafNode * leftCh = static_cast<LeafNode *>(curr);
    int ind = find_index(leftCh->keys, leftCh->key_num, key);
    vector<KeyType> keyss;
    vector<RecordPointer> pointerss;
    for(int i=0;i<leftCh->key_num;i++){
        keyss.push_back(leftCh->keys[i]);
        pointerss.push_back(leftCh->pointers[i]);
    }
    keyss.insert(keyss.begin()+ind, key);
    pointerss.insert(pointerss.begin()+ind, value);
    int breakInd = keyss.size()/2;
//    leftCh->key_num = breakInd;
    for(int i=0;i<breakInd;i++){
        leftCh->keys[i] = keyss.at(i);
        leftCh->pointers[i] = pointerss.at(i);
    }
    for(int i=breakInd;i<leftCh->key_num;i++){
        leftCh->keys[i] = 0;
        RecordPointer zero_record(0,0);
        leftCh->pointers[i] = zero_record;
    }
    leftCh->key_num = breakInd;
    for(int i=0;i<keyss.size()-breakInd;i++){
        rightCh->keys[i] = keyss.at(i+breakInd);
        rightCh->pointers[i] = pointerss.at(i+breakInd);
        rightCh->key_num++;
    }
    
    leftCh->next_leaf = rightCh;
    rightCh->prev_leaf = leftCh;
    return new SubNode(keyss.at(breakInd),leftCh,rightCh);
}

SubNode * BPlusTree::nonSplitInsertIn(SubNode * subNode, Node * curr){
    InternalNode * curre = static_cast<InternalNode *>(curr);
    int index = find_index(curre->keys, curre->key_num, subNode->key);
    vector<SubNode *> subn;
    for(int i=0;i<curre->key_num;i++){
        subn.push_back(new SubNode(curre->keys[i],curre->children[i],curre->children[i+1]));
    }
    subn.insert(subn.begin()+index, subNode);
    curre->key_num++;
    for(int i=0;i<curre->key_num;i++){
        if(i == 0){
            curre->keys[i] = subn.at(i)->key;
            curre->children[i] = subn.at(i)->leftChild;
            curre->children[i+1] = subn.at(i)->rightChild;
        }else{
            curre->keys[i] = subn.at(i)->key;
            curre->children[i+1] = subn.at(i)->rightChild;
        }
    }
    return NULL;
}
SubNode * BPlusTree::SplitInsertIn(SubNode * subNode, Node * curr){
    InternalNode * rightCh = new InternalNode();
    InternalNode * leftCh = static_cast<InternalNode *>(curr);
    int ind =  find_index(leftCh->keys, leftCh->key_num, subNode->key);
    vector<SubNode *> subn;
    for(int i=0;i<leftCh->key_num;i++){
        subn.push_back(new SubNode(leftCh->keys[i], leftCh->children[i],leftCh->children[i+1]));
    }
    subn.insert(subn.begin()+ind, subNode);
    int breakInd = subn.size()/2;
    
//    leftCh->key_num = breakInd;
    for(int i=0;i<breakInd;i++){
        if(i == 0){
            leftCh->keys[i] = subn.at(i)->key;
            leftCh->children[i] = subn.at(i)->leftChild;
            leftCh->children[i+1] = subn.at(i)->rightChild;
        }else{
            leftCh->keys[i] = subn.at(i)->key;
            leftCh->children[i+1] = subn.at(i)->rightChild;
        }
    }
    for(int i=breakInd;i<leftCh->key_num;i++){
        leftCh->keys[i] = 0;
        leftCh->children[i+1] = NULL;
    }
    leftCh->key_num = breakInd;
    for(int i=0;i<subn.size()-(breakInd+1);i++){
        if(i == 0){
            rightCh->keys[i] = subn.at(i+breakInd+1)->key;
            rightCh->children[i] = subn.at(i+breakInd+1)->leftChild;
            rightCh->children[i+1] = subn.at(i+breakInd+1)->rightChild;
        }else{
            rightCh->keys[i] = subn.at(i+breakInd+1)->key;
            rightCh->children[i+1] = subn.at(i+breakInd+1)->rightChild;
        }
        rightCh->key_num++;
    }
    
    return new SubNode(subn.at(breakInd)->key,leftCh,rightCh);
}




//remover Helper
void BPlusTree::update_index(const int &key){
   Node * curr = root;
//    InternalNode * nd = (InternalNode *)(curr);
    while (!curr->is_leaf) {
        InternalNode * nd = static_cast<InternalNode *>(curr);
        int arrSize = curr->key_num;
        bool found = false;
        int i = 0;
        for( i = 0; i<arrSize;i++){
            if(key==curr->keys[i]){
                Node * rightLN = nd->children[i+1];
                while (!rightLN->is_leaf) {
                    InternalNode * lnd = static_cast<InternalNode *>(rightLN);
                    rightLN = lnd->children[0];
                }
                LeafNode * lnod = static_cast<LeafNode *>(rightLN);
                curr->keys[i] = lnod->keys[0];
                return;
            }else if(key < curr->keys[i]){
                curr = nd -> children[i];
                found = true;
                break;
            }
        }
        if(!found){
            curr = nd -> children[i];
        }
    }
}

Node * BPlusTree::findLeafNodeTD(const KeyType &key, stack<ParPosHolder *> &st){
    Node * curr = root;
 //    InternalNode * nd = (InternalNode *)(curr);
     while (!curr->is_leaf) {
         InternalNode * nd = static_cast<InternalNode *>(curr);
         int arrSize = curr->key_num;
         bool found = false;
         int i = 0;
         for( i = 0; i<arrSize;i++){
             if(key < curr->keys[i]){
                 ParPosHolder * ph = new ParPosHolder(i,curr);
                 st.push(ph);
                 curr = nd -> children[i];
                 found = true;
                 break;
             }
         }
         if(!found){
             ParPosHolder * ph = new ParPosHolder(i,curr);
             st.push(ph);
             curr = nd -> children[i];
         }
     }
     return curr;
}


int BPlusTree::findElementPos(int arr[], int n, int K)
{
    for (int i = 0; i < n; i++){
        if (arr[i] == K)
            return i;
    }
    return -1;
}

bool BPlusTree::delKeyLeafNode(Node * curr, const KeyType &key){
    LeafNode * curre = static_cast<LeafNode *>(curr);
    int index = findElementPos(curre->keys, curre->key_num, key);
    if(index!= -1){
        vector<KeyType> keyss;
        vector<RecordPointer> pointerss;
        for(int i=0;i<curre->key_num;i++){
            keyss.push_back(curre->keys[i]);
            pointerss.push_back(curre->pointers[i]);
        }
        keyss.erase(keyss.begin()+index);
        pointerss.erase(pointerss.begin()+index);
        curre->key_num--;
        for(int i=0;i<curre->key_num;i++){
            curre->keys[i] = keyss.at(i);
            curre->pointers[i] = pointerss.at(i);
        }
        
        // making last key null
        curre->keys[curre->key_num] = 0;
        RecordPointer zero_record(0,0);
        curre->pointers[curre->key_num] = zero_record;
        
        return true;
    }
    return false;
}


bool BPlusTree::borrowLeafNode(Node * curr, stack<ParPosHolder *> &st){
    ParPosHolder * ph = st.top();
    Node * parent = ph->ParentNode;
    InternalNode * nd = static_cast<InternalNode *>(parent);
    int currPos = ph->childPos;
    //&&(currPos+1<parent->key_num)
    if(currPos == 0){
        if (nd->children[currPos+1]->key_num > leafMinKeys){
            Node * nc = nd->children[currPos+1];
            LeafNode * rightChild = static_cast<LeafNode *>(nc);
            LeafNode * curre = static_cast<LeafNode *>(curr);
            curre->keys[(curre->key_num)] = rightChild->keys[0];
            curre->pointers[(curre->key_num)] = rightChild->pointers[0];
            curre->key_num++;
            
            vector<KeyType> keyss;
            vector<RecordPointer> pointerss;
            for(int i=0;i<rightChild->key_num;i++){
                keyss.push_back(rightChild->keys[i]);
                pointerss.push_back(rightChild->pointers[i]);
            }
            keyss.erase(keyss.begin());
            pointerss.erase(pointerss.begin());
            rightChild->key_num--;
            for(int i=0;i<rightChild->key_num;i++){
                rightChild->keys[i] = keyss.at(i);
                rightChild->pointers[i] = pointerss.at(i);
            }

            //making removed indexes to null
            rightChild->keys[rightChild->key_num] = 0;
            RecordPointer zero_record(0,0);
            rightChild->pointers[rightChild->key_num] = zero_record;
            
            parent->keys[currPos] = rightChild->keys[0];
            return true;
        }
    }else if(currPos == (parent->key_num)){
        if(nd->children[currPos-1]->key_num > leafMinKeys){
            Node * nc = nd->children[currPos-1];
            LeafNode * leftChild = static_cast<LeafNode *>(nc);
            LeafNode * curre = static_cast<LeafNode *>(curr);
            
            vector<KeyType> keyss;
            vector<RecordPointer> pointerss;
            for(int i=0;i<curre->key_num;i++){
                keyss.push_back(curre->keys[i]);
                pointerss.push_back(curre->pointers[i]);
            }
            keyss.insert(keyss.begin(), leftChild->keys[(leftChild->key_num)-1]);
            pointerss.insert(pointerss.begin(), leftChild->pointers[(leftChild->key_num)-1]);
            curre->key_num++;
            for(int i=0;i<curre->key_num;i++){
                curre->keys[i] = keyss.at(i);
                curre->pointers[i] = pointerss.at(i);
            }
            leftChild->key_num--;
            
            //making removed indexes to null
            leftChild->keys[leftChild->key_num] = 0;
            RecordPointer zero_record(0,0);
            leftChild->pointers[leftChild->key_num] = zero_record;
            
            
            parent->keys[currPos-1] = curre->keys[0];
            return true;
        }
    }else if (currPos>0 && currPos<(parent->key_num)){
        if(nd->children[currPos-1]->key_num > leafMinKeys){
            Node * nc = nd->children[currPos-1];
            LeafNode * leftChild = static_cast<LeafNode *>(nc);
            LeafNode * curre = static_cast<LeafNode *>(curr);
            
            vector<KeyType> keyss;
            vector<RecordPointer> pointerss;
            for(int i=0;i<curre->key_num;i++){
                keyss.push_back(curre->keys[i]);
                pointerss.push_back(curre->pointers[i]);
            }
            keyss.insert(keyss.begin(), leftChild->keys[(leftChild->key_num)-1]);
            pointerss.insert(pointerss.begin(), leftChild->pointers[(leftChild->key_num)-1]);
            curre->key_num++;
            for(int i=0;i<curre->key_num;i++){
                curre->keys[i] = keyss.at(i);
                curre->pointers[i] = pointerss.at(i);
            }
            leftChild->key_num--;
            
            
            //making removed indexes to null
            leftChild->keys[leftChild->key_num] = 0;
            RecordPointer zero_record(0,0);
            leftChild->pointers[leftChild->key_num] = zero_record;
            
            
            parent->keys[currPos-1] = curre->keys[0];
            return true;
        }else if (nd->children[currPos+1]->key_num > leafMinKeys){
            Node * nc = nd->children[currPos+1];
            LeafNode * rightChild = static_cast<LeafNode *>(nc);
            LeafNode * curre = static_cast<LeafNode *>(curr);
            curre->keys[(curre->key_num)+1] = rightChild->keys[0];
            curre->pointers[(curre->key_num)+1] = rightChild->pointers[0];
            curre->key_num++;
            
            vector<KeyType> keyss;
            vector<RecordPointer> pointerss;
            for(int i=0;i<rightChild->key_num;i++){
                keyss.push_back(rightChild->keys[i]);
                pointerss.push_back(rightChild->pointers[i]);
            }
            keyss.erase(keyss.begin());
            pointerss.erase(pointerss.begin());
            rightChild->key_num--;
            for(int i=0;i<rightChild->key_num;i++){
                rightChild->keys[i] = keyss.at(i);
                rightChild->pointers[i] = pointerss.at(i);
            }
            
            //making removed indexes to null
            rightChild->keys[rightChild->key_num] = 0;
            RecordPointer zero_record(0,0);
            rightChild->pointers[rightChild->key_num] = zero_record;
            
            parent->keys[currPos] = rightChild->keys[0];
            return true;
        }
    }
    return false;
}

bool BPlusTree::borrowIntNode(Node * curr, stack<ParPosHolder *> &st){
    ParPosHolder * ph = st.top();
    Node * parent = ph->ParentNode;
    InternalNode * nd = static_cast<InternalNode *>(parent);
    int currPos = ph->childPos;
    if(currPos == 0&&(currPos+1<=parent->key_num)){
        if (nd->children[currPos+1]->key_num > minKeys){
            Node * nc = nd->children[currPos+1];
            InternalNode * rightChild = static_cast<InternalNode *>(nc);
            InternalNode * curre = static_cast<InternalNode *>(curr);
            
            
            
            curre->keys[(curre->key_num)] = nd->keys[currPos];
            curre->children[(curre->key_num)+1] = rightChild->children[0];
            curre->key_num++;
            
            nd->keys[currPos] = rightChild->keys[0];
            
            vector<KeyType> keyss;
            vector<Node *> pointerss;
            for(int i=0;i<rightChild->key_num;i++){
                keyss.push_back(rightChild->keys[i]);
                pointerss.push_back(rightChild->children[i]);
            }
            pointerss.push_back(rightChild->children[rightChild->key_num]);
            keyss.erase(keyss.begin());
            pointerss.erase(pointerss.begin());
            rightChild->key_num--;
            for(int i=0;i<rightChild->key_num;i++){
                rightChild->keys[i] = keyss.at(i);
                rightChild->children[i] = pointerss.at(i);
            }
            rightChild->children[rightChild->key_num] = pointerss.at(rightChild->key_num);
            
            //making removed indexes null
            rightChild->keys[rightChild->key_num] = 0;
            rightChild->children[(rightChild->key_num)+1] = NULL;
            
            return true;
        }
    }else if(currPos == (parent->key_num)){
        if(nd->children[currPos-1]->key_num > minKeys){
            Node * nc = nd->children[currPos-1];
            InternalNode * leftChild = static_cast<InternalNode *>(nc);
            InternalNode * curre = static_cast<InternalNode *>(curr);
            
            vector<KeyType> keyss;
            vector<Node *> pointerss;
            for(int i=0;i<curre->key_num;i++){
                keyss.push_back(curre->keys[i]);
                pointerss.push_back(curre->children[i]);
            }
            pointerss.push_back(curre->children[curre->key_num]);
            keyss.insert(keyss.begin(), nd->keys[currPos-1]);
            pointerss.insert(pointerss.begin(), leftChild->children[(leftChild->key_num)]);
            curre->key_num++;
            for(int i=0;i<curre->key_num;i++){
                curre->keys[i] = keyss.at(i);
                curre->children[i] = pointerss.at(i);
            }
            curre->children[curre->key_num] = pointerss.at(curre->key_num);
            nd->keys[currPos-1] = leftChild->keys[leftChild->key_num-1];
            leftChild->key_num--;
            
            //making removed indexes null
            leftChild->keys[leftChild->key_num] = 0;
            leftChild->children[(leftChild->key_num)+1] =NULL;
            return true;
        }
    }else if (currPos>0 && currPos<(parent->key_num)){
        //Boorrowing from left child
        if(nd->children[currPos-1]->key_num > minKeys){
            Node * nc = nd->children[currPos-1];
            InternalNode * leftChild = static_cast<InternalNode *>(nc);
            InternalNode * curre = static_cast<InternalNode *>(curr);
            
            vector<KeyType> keyss;
            vector<Node *> pointerss;
            for(int i=0;i<curre->key_num;i++){
                keyss.push_back(curre->keys[i]);
                pointerss.push_back(curre->children[i]);
            }
            pointerss.push_back(curre->children[curre->key_num]);
            keyss.insert(keyss.begin(), nd->keys[currPos-1]);
            pointerss.insert(pointerss.begin(), leftChild->children[(leftChild->key_num)]);
            curre->key_num++;
            for(int i=0;i<curre->key_num;i++){
                curre->keys[i] = keyss.at(i);
                curre->children[i] = pointerss.at(i);
            }
            curre->children[curre->key_num] = pointerss.at(curre->key_num);
            nd->keys[currPos-1] = leftChild->keys[leftChild->key_num-1];
            leftChild->key_num--;
            
            //making removed indexes null
            leftChild->keys[leftChild->key_num] = 0;
            leftChild->children[(leftChild->key_num)+1] =NULL;
            return true;
            
        }else if (nd->children[currPos+1]->key_num > minKeys){
            //Boorrowing from right child
            Node * nc = nd->children[currPos+1];
            InternalNode * rightChild = static_cast<InternalNode *>(nc);
            InternalNode * curre = static_cast<InternalNode *>(curr);
            
            
            
            curre->keys[(curre->key_num)] = nd->keys[currPos];
            curre->children[(curre->key_num)+1] = rightChild->children[0];
            curre->key_num++;
            
            nd->keys[currPos] = rightChild->keys[0];
            
            vector<KeyType> keyss;
            vector<Node *> pointerss;
            for(int i=0;i<rightChild->key_num;i++){
                keyss.push_back(rightChild->keys[i]);
                pointerss.push_back(rightChild->children[i]);
            }
            pointerss.push_back(rightChild->children[rightChild->key_num]);
            keyss.erase(keyss.begin());
            pointerss.erase(pointerss.begin());
            rightChild->key_num--;
            for(int i=0;i<rightChild->key_num;i++){
                rightChild->keys[i] = keyss.at(i);
                rightChild->children[i] = pointerss.at(i);
            }
            rightChild->children[rightChild->key_num] = pointerss.at(rightChild->key_num);
            
            //making removed indexes null
            rightChild->keys[rightChild->key_num] = 0;
            rightChild->children[(rightChild->key_num)+1] = NULL;
            
            return true;
        }
    }
    return false;
}

bool BPlusTree::mergeLeafNode(Node * curr, stack<ParPosHolder *> &st){
    ParPosHolder * ph = st.top();
    Node * parent = ph->ParentNode;
    InternalNode * nd = static_cast<InternalNode *>(parent);
    int currPos = ph->childPos;
    if(currPos == 0 && (currPos+1<=parent->key_num)){
            Node * nc = nd->children[currPos+1];
            LeafNode * rightChild = static_cast<LeafNode *>(nc);
            LeafNode * curre = static_cast<LeafNode *>(curr);
            
            vector<KeyType> keyss;
            vector<RecordPointer> pointerss;
            for(int i=0;i<rightChild->key_num;i++){
                keyss.push_back(rightChild->keys[i]);
                pointerss.push_back(rightChild->pointers[i]);
            }
        for (int i=0; i<curre->key_num; i++) {
            keyss.insert(keyss.begin()+i, curre->keys[i]);
            pointerss.insert(pointerss.begin()+i, curre->pointers[i]);
        }
            rightChild->key_num = keyss.size();
            for(int i=0;i<rightChild->key_num;i++){
                rightChild->keys[i] = keyss.at(i);
                rightChild->pointers[i] = pointerss.at(i);
            }
        rightChild->prev_leaf = curre->prev_leaf;
        if(curre->prev_leaf!=NULL){
        curre->prev_leaf->next_leaf = rightChild;
        }
        //Updating(Deleting) the key from parent node
        vector<KeyType> pkeyss;
        vector<Node *> ppointerss;
        for(int i=0;i<nd->key_num;i++){
            pkeyss.push_back(nd->keys[i]);
            ppointerss.push_back(nd->children[i]);
        }
        ppointerss.push_back(nd->children[nd->key_num]);
        pkeyss.erase(pkeyss.begin()+currPos);
        ppointerss.erase(ppointerss.begin()+currPos);
        nd->key_num--;
        for(int i=0;i<nd->key_num;i++){
            nd->keys[i] = pkeyss.at(i);
            nd->children[i] = ppointerss.at(i);
        }
        nd->children[nd->key_num] = ppointerss.at(nd->key_num);
        
        //making removed indexes null
        nd->keys[nd->key_num] = 0;
        nd->children[(nd->key_num)+1] = NULL;
        
            return (nd->key_num < minKeys)?true:false;
        
        
    }else if(currPos == (parent->key_num)){
        
            Node * nc = nd->children[currPos-1];
            LeafNode * leftChild = static_cast<LeafNode *>(nc);
            LeafNode * curre = static_cast<LeafNode *>(curr);
            
            vector<KeyType> keyss;
            vector<RecordPointer> pointerss;
            for(int i=0;i<leftChild->key_num;i++){
                keyss.push_back(leftChild->keys[i]);
                pointerss.push_back(leftChild->pointers[i]);
            }
        for(int i=0; i<curre->key_num;i++){
            keyss.push_back(curre->keys[i]);;
            pointerss.push_back(curre->pointers[i]);
        }
            leftChild->key_num = keyss.size();
            for(int i=0;i<leftChild->key_num;i++){
                leftChild->keys[i] = keyss.at(i);
                leftChild->pointers[i] = pointerss.at(i);
            }
            
        leftChild->next_leaf = curre->next_leaf;
        if(curre->next_leaf!=NULL){
            curre->next_leaf->prev_leaf = leftChild;
        }
        
        //Updating(Deleting) the key from parent node
        vector<KeyType> pkeyss;
        vector<Node *> ppointerss;
        for(int i=0;i<nd->key_num;i++){
            pkeyss.push_back(nd->keys[i]);
            ppointerss.push_back(nd->children[i]);
        }
        ppointerss.push_back(nd->children[nd->key_num]);
        pkeyss.erase(pkeyss.begin()+(currPos-1));
        ppointerss.erase(ppointerss.begin()+currPos);
        nd->key_num--;
        for(int i=0;i<nd->key_num;i++){
            nd->keys[i] = pkeyss.at(i);
            nd->children[i] = ppointerss.at(i);
        }
        nd->children[nd->key_num] = ppointerss.at(nd->key_num);
        
        //making removed indexes null
        nd->keys[nd->key_num] = 0;
        nd->children[(nd->key_num)+1] = NULL;
        
            return (nd->key_num < minKeys)?true:false;
        
    }else if (currPos>0 && currPos<(parent->key_num)){
        Node * nc = nd->children[currPos+1];
        LeafNode * rightChild = static_cast<LeafNode *>(nc);
        LeafNode * curre = static_cast<LeafNode *>(curr);
        
        vector<KeyType> keyss;
        vector<RecordPointer> pointerss;
        for(int i=0;i<rightChild->key_num;i++){
            keyss.push_back(rightChild->keys[i]);
            pointerss.push_back(rightChild->pointers[i]);
        }
    for (int i=0; i<curre->key_num; i++) {
        keyss.insert(keyss.begin()+i, curre->keys[i]);
        pointerss.insert(pointerss.begin()+i, curre->pointers[i]);
    }
        rightChild->key_num = keyss.size();
        for(int i=0;i<rightChild->key_num;i++){
            rightChild->keys[i] = keyss.at(i);
            rightChild->pointers[i] = pointerss.at(i);
        }
        rightChild->prev_leaf = curre->prev_leaf;
        if(curre->prev_leaf!=NULL){
        curre->prev_leaf->next_leaf = rightChild;
        }
    //Updating(Deleting) the key from parent node
    vector<KeyType> pkeyss;
    vector<Node *> ppointerss;
    for(int i=0;i<nd->key_num;i++){
        pkeyss.push_back(nd->keys[i]);
        ppointerss.push_back(nd->children[i]);
    }
    ppointerss.push_back(nd->children[nd->key_num]);
    pkeyss.erase(pkeyss.begin()+currPos);
    ppointerss.erase(ppointerss.begin()+currPos);
    nd->key_num--;
    for(int i=0;i<nd->key_num;i++){
        nd->keys[i] = pkeyss.at(i);
        nd->children[i] = ppointerss.at(i);
    }
    nd->children[nd->key_num] = ppointerss.at(nd->key_num);
        
        //making removed indexes null
        nd->keys[nd->key_num] = 0;
        nd->children[(nd->key_num)+1] = NULL;
        
        return (nd->key_num < minKeys)?true:false;
    }
    return false;
}


bool BPlusTree::mergeIntNode(Node * curr, stack<ParPosHolder *> &st){
    ParPosHolder * ph = st.top();
    Node * parent = ph->ParentNode;
    InternalNode * nd = static_cast<InternalNode *>(parent);
    int currPos = ph->childPos;
    if(currPos == 0){
            Node * nc = nd->children[currPos+1];
            InternalNode * rightChild = static_cast<InternalNode *>(nc);
            InternalNode * curre = static_cast<InternalNode *>(curr);
            
            vector<KeyType> keyss;
            vector<Node *> pointerss;
            for(int i=0;i<curre->key_num;i++){
                keyss.push_back(curre->keys[i]);
                pointerss.push_back(curre->children[i]);
            }
        pointerss.push_back(curre->children[curre->key_num]);
        keyss.push_back(nd->keys[currPos]);
        for (int i=0; i<rightChild->key_num; i++) {
            keyss.push_back(rightChild->keys[i]);
            pointerss.push_back(rightChild->children[i]);
        }
        pointerss.push_back(rightChild->children[rightChild->key_num]);
            rightChild->key_num = keyss.size();
            for(int i=0;i<rightChild->key_num;i++){
                rightChild->keys[i] = keyss.at(i);
                rightChild->children[i] = pointerss.at(i);
            }
        rightChild->children[rightChild->key_num] = pointerss.at(rightChild->key_num);
        
        //Updating(Deleting) the key from parent node
        vector<KeyType> pkeyss;
        vector<Node *> ppointerss;
        for(int i=0;i<nd->key_num;i++){
            pkeyss.push_back(nd->keys[i]);
            ppointerss.push_back(nd->children[i]);
        }
        ppointerss.push_back(nd->children[nd->key_num]);
        pkeyss.erase(pkeyss.begin()+currPos);
        ppointerss.erase(ppointerss.begin()+currPos);
        nd->key_num--;
        for(int i=0;i<nd->key_num;i++){
            nd->keys[i] = pkeyss.at(i);
            nd->children[i] = ppointerss.at(i);
        }
        nd->children[nd->key_num] = ppointerss.at(nd->key_num);
        //making removed indexes null
        nd->keys[nd->key_num] = 0;
        nd->children[(nd->key_num)+1] = NULL;
        
            return (nd->key_num < minKeys)?true:false;
        
        
        
    }else if(currPos == (parent->key_num)){
        
            Node * nc = nd->children[currPos-1];
            InternalNode * leftChild = static_cast<InternalNode *>(nc);
            InternalNode * curre = static_cast<InternalNode *>(curr);
            
            vector<KeyType> keyss;
            vector<Node *> pointerss;
            for(int i=0;i<leftChild->key_num;i++){
                keyss.push_back(leftChild->keys[i]);
                pointerss.push_back(leftChild->children[i]);
            }
        pointerss.push_back(leftChild->children[leftChild->key_num]);
        keyss.push_back(nd->keys[currPos-1]);
        for(int i=0; i<curre->key_num;i++){
            keyss.push_back(curre->keys[i]);;
            pointerss.push_back(curre->children[i]);
        }
        pointerss.push_back(curre->children[curre->key_num]);
            leftChild->key_num = keyss.size();
            for(int i=0;i<leftChild->key_num;i++){
                leftChild->keys[i] = keyss.at(i);
                leftChild->children[i] = pointerss.at(i);
            }
        leftChild->children[leftChild->key_num] = pointerss.at(leftChild->key_num);
        
        
        //Updating(Deleting) the key from parent node
        vector<KeyType> pkeyss;
        vector<Node *> ppointerss;
        for(int i=0;i<nd->key_num;i++){
            pkeyss.push_back(nd->keys[i]);
            ppointerss.push_back(nd->children[i]);
        }
        ppointerss.push_back(nd->children[nd->key_num]);
        pkeyss.erase(pkeyss.begin()+(currPos-1));
        ppointerss.erase(ppointerss.begin()+currPos);
        nd->key_num--;
        for(int i=0;i<nd->key_num;i++){
            nd->keys[i] = pkeyss.at(i);
            nd->children[i] = ppointerss.at(i);
        }
        nd->children[nd->key_num] = ppointerss.at(nd->key_num);
        //making removed indexes null
        nd->keys[nd->key_num] = 0;
        nd->children[(nd->key_num)+1] = NULL;
            return (nd->key_num < minKeys)?true:false;
        
    }else if (currPos>0 && currPos<(parent->key_num)){
        Node * nc = nd->children[currPos+1];
        InternalNode * rightChild = static_cast<InternalNode *>(nc);
        InternalNode * curre = static_cast<InternalNode *>(curr);
        
        vector<KeyType> keyss;
        vector<Node *> pointerss;
        for(int i=0;i<curre->key_num;i++){
            keyss.push_back(curre->keys[i]);
            pointerss.push_back(curre->children[i]);
        }
    pointerss.push_back(curre->children[curre->key_num]);
    keyss.push_back(nd->keys[currPos]);
    for (int i=0; i<rightChild->key_num; i++) {
        keyss.push_back(rightChild->keys[i]);
        pointerss.push_back(rightChild->children[i]);
    }
    pointerss.push_back(rightChild->children[rightChild->key_num]);
        rightChild->key_num = keyss.size();
        for(int i=0;i<rightChild->key_num;i++){
            rightChild->keys[i] = keyss.at(i);
            rightChild->children[i] = pointerss.at(i);
        }
    rightChild->children[rightChild->key_num] = pointerss.at(rightChild->key_num);
    
    //Updating(Deleting) the key from parent node
    vector<KeyType> pkeyss;
    vector<Node *> ppointerss;
    for(int i=0;i<nd->key_num;i++){
        pkeyss.push_back(nd->keys[i]);
        ppointerss.push_back(nd->children[i]);
    }
    ppointerss.push_back(nd->children[nd->key_num]);
    pkeyss.erase(pkeyss.begin()+currPos);
    ppointerss.erase(ppointerss.begin()+currPos);
    nd->key_num--;
    for(int i=0;i<nd->key_num;i++){
        nd->keys[i] = pkeyss.at(i);
        nd->children[i] = ppointerss.at(i);
    }
    nd->children[nd->key_num] = ppointerss.at(nd->key_num);
    //making removed indexes null
    nd->keys[nd->key_num] = 0;
    nd->children[(nd->key_num)+1] = NULL;
    
        return (nd->key_num < minKeys)?true:false;
    
    
    }
    return false;
}



/*
 * Helper function to decide whether current b+tree is empty
 */
bool BPlusTree::IsEmpty() const {
    //cout << maxChild << " " << minChild << " " << maxKeys << " " << minKeys << endl;
    if(root!=NULL){
        return false;
    }
    return true;

}

/*****************************************************************************
 * SEARCH
 *****************************************************************************/
/*
 * Return the only value that associated with input key
 * This method is used for point query
 * @return : true means key exists
 */
bool BPlusTree::GetValue(const KeyType &key, RecordPointer &result) {
    if(root!=NULL){
    Node * curr = NULL;
    stack<ParPosHolder *> sta;
    curr = findLeafNodeTD(key, sta);
    LeafNode * curre = static_cast<LeafNode *>(curr);
    int index = findElementPos(curre->keys, curre->key_num, key);
    if(index!=-1){
        result = curre->pointers[index];
        return true;
    }
    }
    return false; }

/*****************************************************************************
 * INSERTION
 *****************************************************************************/
/*
 * Insert constant key & value pair into b+ tree
 * If current tree is empty, start new tree, otherwise insert into leaf Node.
 * @return: since we only support unique key, if user try to insert duplicate
 * keys return false, otherwise return true.
 */
bool BPlusTree::Insert(const KeyType &key, const RecordPointer &value) {
    Node * curr = root;
    stack<Node *> st;
    SubNode * subNode;
    if(curr==NULL){
        LeafNode * newLeaf = new LeafNode();
        newLeaf->keys[0] = key;
        newLeaf->pointers[0] = value;
        newLeaf->key_num++;
        root = newLeaf;
        return true;
    }else if (curr->is_leaf){
        if(curr->key_num != maxKeys){
           subNode = nonSplitInsertLeaf(key, value, curr);
        }else{
            subNode = SplitInsertLeaf(key, value, curr);
        }
        while(subNode!=NULL){
            InternalNode * newIN = new InternalNode();
            newIN->keys[0] = subNode->key;
            newIN->children[0] = subNode->leftChild;
            newIN->children[1] = subNode->rightChild;
            newIN->key_num++;
            root = newIN;
            subNode = NULL;
        }
        return true;
    }else{
        curr = findLeafNodeInsert(key, st);
        if(curr->key_num != maxKeys){
           subNode = nonSplitInsertLeaf(key, value, curr);
        }else{
            subNode = SplitInsertLeaf(key, value, curr);
        }
        while(subNode!=NULL){
            if(st.empty()){
            InternalNode * newIN = new InternalNode();
            newIN->keys[0] = subNode->key;
            newIN->children[0] = subNode->leftChild;
            newIN->children[1] = subNode->rightChild;
            newIN->key_num++;
            root = newIN;
            subNode = NULL;
            }else{
                curr = st.top();
                st.pop();
                if(curr->key_num != maxKeys){
                   subNode = nonSplitInsertIn(subNode, curr);
                }else{
                    subNode = SplitInsertIn(subNode, curr);
                }
                
            }
        }
        return true;
    }

    return false; }

/*****************************************************************************
 * REMOVE
 *****************************************************************************/
/*
 * Delete key & value pair associated with input key
 * If current tree is empty, return immdiately.
 * If not, User needs to first find the right leaf node as deletion target, then
 * delete entry from leaf node. Remember to deal with redistribute or merge if
 * necessary.
 */


void BPlusTree::Remove(const KeyType &key) {
    if(root!=NULL){
    stack<ParPosHolder *> st;
    Node * curr = NULL;
    curr = findLeafNodeTD(key, st);
    if(delKeyLeafNode(curr, key)){
        if(!st.empty()){
        bool parentChanReq = (curr->key_num < leafMinKeys)?true:false;
        if(parentChanReq){
            //borrow
            if(!borrowLeafNode(curr, st)){
                //merge(if borrow not successful)
                bool treeChanReq  =mergeLeafNode(curr,st);
                while(treeChanReq&&st.size()>1){
                    curr = st.top()->ParentNode;
                    st.pop();
                    if(!borrowIntNode(curr, st)){
                        treeChanReq = mergeIntNode(curr, st);
                    }else{
                        treeChanReq = false;
                        break;
                    }
                }if(treeChanReq){
                    curr = st.top()->ParentNode;
                    st.pop();
                    if(curr->key_num==0){
                        InternalNode * newC = static_cast<InternalNode *>(curr);
                        root = newC->children[0];
                    }
                }
    
            }
            
        }
        update_index(key);
        }else{
            if(curr->key_num==0){
                root = NULL;
            }
        }
    }
    }
                                 
    
}

/*****************************************************************************
 * RANGE_SCAN
 *****************************************************************************/
/*
 * Return the values that within the given key range
 * First find the node large or equal to the key_start, then traverse the leaf
 * nodes until meet the key_end position, fetch all the records.
 */
void BPlusTree::RangeScan(const KeyType &key_start, const KeyType &key_end,
                          std::vector<RecordPointer> &result) {
    if(root!=NULL){
    Node * curr = NULL;
    stack<ParPosHolder *> sta;
    curr = findLeafNodeTD(key_start, sta);
    LeafNode * curre = static_cast<LeafNode *>(curr);
        int index = -1;
        for(int i = 0;i<curre->key_num;i++){
            if(curre->keys[i]>=key_start){
                index = i;
                break;
            }
        }
        if(index==-1){
            index = curre->key_num;
        }
    if(index!=-1){
        while(curre!=NULL){
        for(int i = index;i<curre->key_num;i++){
            if(curre->keys[i]>=key_end){
                return;
            }
            result.push_back(curre->pointers[i]);
        }
            curre = static_cast<LeafNode *>(curre->next_leaf);
            index = 0;
        }
       
    }
    }
}
