//===----------------------------------------------------------------------===//
//
//                         Rutgers CS539 - Database System
//                         ***DO NO SHARE PUBLICLY***
//
// Identification:   test/nested_loop_join_test.cpp
//
// Copyright (c) 2022, Rutgers University
//
//===----------------------------------------------------------------------===/

#include <iostream>
#include <string>
#include <vector>

#include "../include/nested_loop_join_executor.h"
#include "../include/seq_scan_executor.h"

using std::cout;
using std::endl;
using std::vector;

int main() {
  Table t1;
  for (int i = 0; i < 15; i++) {
    t1.insert(i, i, std::to_string(i));
  }

  Table t2;
  for (int i = 5; i < 20; i++) {
    t2.insert(i, i, std::to_string(i));
  }

  SeqScanExecutor seq1(&t1);
  SeqScanExecutor seq2(&t2);

  NestedLoopJoinExecutor executor1(&seq1, &seq2, "val1");

  executor1.Init();
  Tuple tuple;
  while (executor1.Next(&tuple)) {
    cout << "Successfully get tuple! id: " << tuple.id
         << " val1: " << tuple.val1 << " val2: " << tuple.val2 << endl;
  }

  cout << endl;
  NestedLoopJoinExecutor executor2(&seq1, &seq2, "val2");
  executor2.Init();
  while (executor2.Next(&tuple)) {
    cout << "Successfully get tuple! id: " << tuple.id
         << " val1: " << tuple.val1 << " val2: " << tuple.val2 << endl;
  }

  return 0;
}
