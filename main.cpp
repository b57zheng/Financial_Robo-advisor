#include <iostream>
#include "History.hpp"
#include "Transaction.hpp"


#ifndef MARMOSET_TESTING
unsigned int Transaction::assigned_trans_id = 0;
int main() {
  // Create a new variable called 'test_transaction' with type 'Transaction'
  // The objective programming forced to have all the information to proceed {"VGRO", 15, 2, 2020, true, 300, 9900}
  // Transaction test_transaction {"VGRO", 15, 2, 2020, true, 300, 9900};
  // // Make it dynamic.
  // Transaction * p_transaction { new Transaction {"VGRO", 15, 2, 2020, false, 200, 9900} };
  // Transaction test1_transaction {"VGRO", 15, 2, 2021, true, 300, 9900};
  // if (test_transaction < test1_transaction)
  // {
  //   std::cout << "less";
  // }


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
