////////////////////////////////////
// Project: Financial Robo Advisor
// Authors: Bowen Zheng, Electrical Engineering, University of Waterloo
// compile and run this program with command:
// g++ -o main History_Transaction_definitions.cpp project4.cpp main.cpp -std=c++11
// ./main      
////////////////////////////////////

#include <iostream>
#include "History.hpp"
#include "Transaction.hpp"


#ifndef MARMOSET_TESTING
unsigned int Transaction::assigned_trans_id = 0;
int main() {
  History trans_history{};
  //std::cout << "Hello" << std::endl;
  trans_history.read_history();

  // std::cout << "[Starting history]:" << std::endl;
  // trans_history.print();
  trans_history.sort_by_date();

  std::cout << "[Sorted          ]:" << std::endl;
  trans_history.print();

  trans_history.update_acb_cgl();
  trans_history.print();

  std::cout << "[CGL for 2018    ]: " << trans_history.compute_cgl(2018) << std::endl;
  std::cout << "[CGL for 2019    ]: " << trans_history.compute_cgl(2019) << std::endl;

  return 0;
}
#endif
