#include "../include/hash_join_executor.h"

HashJoinExecutor::HashJoinExecutor(AbstractExecutor *left_child_executor,
                                   AbstractExecutor *right_child_executor,
                                   SimpleHashFunction *hash_fn)
    : left_(left_child_executor),
      right_(right_child_executor),
      hash_fn_(hash_fn) {}

void HashJoinExecutor::Init(){
    if(!tupList.empty()){
        iter_ = tupList.begin();
    }
    left_->Init();
    right_->Init();
    Tuple tupleL;
    hash_t hval;
    while (left_->Next(&tupleL)) {
        hval = hash_fn_->GetHash(tupleL);
        ht.Insert(hval,tupleL);
    }
};

bool HashJoinExecutor::Next(Tuple *tuple) {
    if(!tupList.empty() && iter_!=tupList.end()) {
        const Tuple &curr_tuple = *iter_;
        *tuple = Tuple(curr_tuple);
        ++iter_;
        return true;
    }else{
        Tuple tupleR;
        while (right_->Next(&tupleR)) {
            hash_t hval = hash_fn_->GetHash(tupleR);
            ht.GetValue(hval,&tupList);
            if(!tupList.empty()){
                iter_ = tupList.begin();
                const Tuple &curr_tuple = *iter_;
                *tuple = Tuple(curr_tuple);
                ++iter_;
                return true;
            }
        }
    }
    
    return false;
}
