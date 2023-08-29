//
//  main.cpp
//  dbmsProj2
//
//  Created by Sriram Nidadavolu on 11/28/22.
//

//#include <iostream>
//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    std::cout << "Hello, World!\n";
//    return 0;
//}


#include <iostream>
#include <string>
#include <vector>

#include "include/seq_scan_executor.h"

using std::cout;
using std::endl;
using std::vector;

int main() {
  Table t1;
  t1.insert(0, 0, "0");
  t1.insert(0, 0, "0");

  for (int i = 0; i < 10; i++) {
    t1.insert(i, i, std::to_string(i));
  }

  SeqScanExecutor executor(&t1);

  executor.Init();
  Tuple tuple;
  while (executor.Next(&tuple)) {
    cout << "Successfully get tuple! id: " << tuple.id
         << " val1: " << tuple.val1 << " val2: " << tuple.val2 << endl;
  }

  return 0;
}
