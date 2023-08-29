#include "../include/nested_loop_join_executor.h"

NestedLoopJoinExecutor::NestedLoopJoinExecutor(
    AbstractExecutor *left_child_executor,
    AbstractExecutor *right_child_executor, const std::string join_key)
    : left_(left_child_executor),
      right_(right_child_executor),
      join_key_(join_key){};

void NestedLoopJoinExecutor::Init() {
    left_->Init();
    right_->Init();
    
}

bool NestedLoopJoinExecutor::Next(Tuple *tuple) {
    Tuple tupleL;
    Tuple tupleR;
    right_->Init();
    while (left_->Next(&tupleL)) {
        while(right_->Next(&tupleR)){
            if(join_key_=="id"){
                if(tupleL.id ==tupleR.id){
                    *tuple=tupleL;
                    return true;
                }
            }else if(join_key_=="val1"){
                if(tupleL.val1 ==tupleR.val1){
                    *tuple=tupleL;
                    return true;
                }
            }else if(join_key_=="val2"){
                if(tupleL.val2 ==tupleR.val2){
                    *tuple=tupleL;
                    return true;
                }
            }
        }
        right_->Init();
    }
    
    return false; }
