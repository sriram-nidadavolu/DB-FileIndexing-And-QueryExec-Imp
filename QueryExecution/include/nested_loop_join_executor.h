#pragma once

#include <vector>

#include "abstract_executor.h"
#include "storage.h"

/**
 * NestedLoopJoinExecutor executes a nested-loop JOIN on two tables.
 */
class NestedLoopJoinExecutor : public AbstractExecutor {
 public:
  /**
   * Creates a new hash join executor.
   * @param left_child_executor the left child, used by convention to build the
   * hash table
   * @param right_child_executor the right child, used by convention to probe
   * the hash table
   * @param join_key specify which attribute we should use to join. It must be
   * one of the {"id","val1","val2"}; Don't foget to check the join_key.
   */
  NestedLoopJoinExecutor(AbstractExecutor *left_child_executor,
                         AbstractExecutor *right_child_executor,
                         const std::string join_key);

  /** Initialize the join */
  void Init() override;

  /**
   * Yield the next tuple from join.
   * @param tuple the next tuple produced by scan
   * @return `true` if a tuple was produced, `false` if there are no more tuples
   */
  bool Next(Tuple *tuple) override;

 private:
  AbstractExecutor *left_;
  AbstractExecutor *right_;
  std::string join_key_;
};
