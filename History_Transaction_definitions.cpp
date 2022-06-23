////////////////////////////////////
// ECE 150: Project 4
//
// Authors: Bowen Zheng
// compile and run this program with command
// g++ -o main History_Transaction_definitions.cpp project4.cpp main.cpp -std=c++11      
////////////////////////////////////

#include <cassert>
#include <iomanip>
#include <iostream>
#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//





// Constructor   
// TASK 1
  // What is a constructor?
      // A constructor is a member function that is automatically called when the object is created.
      // Objective programming protect data, and it is impossible not to be called.
  // How do we create a constructor for Transaction class?
      // The syntext for a constructor: The name of the constructor is the same with the name of the class.
      // No return type on a constructor. 
      // (std::string ticker_symbol, unsigned int day_date, unsigned int month_date, unsigned year_date, 
      // bool buy_sell_trans, unsigned int number_shares, double trans_amount) are the parameters it takes.
  // What are the parameters to the teransaction constructor for?
      // These are the initialization values for constructor (ticker_symbol, day_date, month_date, year_date, biu_sell_trans, number_share, trans_amount)
  // We are initializing the constructor values from transaction 'private' member variables
      /* void print();
          private:
          std::string symbol;         ----> Stores the ticker symbol as a std::string.
          unsigned int day;
          unsigned int month;
          unsigned int year;
          std::string trans_type;
          unsigned int shares; 
          double amount;
          unsigned int trans_id;      ----> Stores a unique transaction identifier for every transaction.
      */
//class name::function name
Transaction::Transaction ( std::string ticker_symbol, 
                           unsigned int day_date, 
                           unsigned int month_date, 
                           unsigned year_date, 
                           bool buy_sell_trans, 
                           unsigned int number_shares, 
                           double trans_amount )
{
  //set private member variables (transaction) to each initialization values.
  symbol = ticker_symbol;
  day = day_date;
  month = month_date;
  year = year_date;
  //trans_type is a string.
  //Stores 'Buy' if the transaction is a Buy, and 'Sell' if it is a Sell.
  if ( buy_sell_trans == true)
  {
    trans_type = "Buy";
  }
  else
  {
    trans_type = "Sell";
  }
  shares = number_shares;
  amount = trans_amount;
  /* 
  "trans_id" is the transaction ID.
  "static unsigned int assigned_trans_id;" is a static class variable used to generate unique identifiers whenever a transaction objectis created. 
  This is the identifier you will use to set the trans_id private member, andincrement it after the assignment.
    * The Transaction ID must be unique for all transacations.
    * We need to use a static class variable to keep what the next 
    * static variable is all object of this class shares the same variable (constant). 
  */
  /*
 To make transaction ID unique:
    1. We know that main function get assigned_trans_id = 0 initially in transaction A (test_transaction), and this will causes trans_id in A = 0. trans_id = assigned_trans_id
    2. We then will want to increase the assigned_trans_id for each assign to notice other transactions. Now assigned_trans_id = 1;
    3. For example, if got assigned_trans_id = 1 (global for transaction class), the trans_id of Transaction B(*P_transaction) will be set to 1. 
    4. This will set the trans_id in transaction B = 1, and then we will want to increase the "assigned_trans_id" again after the assginment. 
  */
  trans_id = assigned_trans_id;
  //increament of assigned_trans_id
  ++assigned_trans_id;
}



// Destructor
// TASK 1
  //This is a default destructor.
  // What is a destructor?
      // A memeber fuction that is automatically called when the object is deallocated.
          // When is an object/variable deallocated?
              // 1. for local variables, when they go out of scope.
              // 2. for dynamically allocated variables, when they are deleated.
      // Destuctors are used to delete/deallocate dynamically allocated data structures. （ex. new array[], needs to be deleted]
      // It does not take any parameters.
      // It returns nothing.

Transaction::~Transaction ()
{

}


// Overloaded < operator.
// TASK 2
  //"this" is a keyword 
  //if the date of other is > this.day, return true.
  //标识箭头 “->” 是指针的 “.”
bool Transaction::operator < (Transaction const & other)
{
  if ( this->year < other.year )
  {
    return true;
  }
  else if ( this->year == other.year )
  {
    if (this->month < other.month)
    {
      return true;
    }
    else if (this->month == other.month)
    {
      if (this->day < other.day)
      {
        return true;
      }
    }
  } 
  return false;
}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "

    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() )
  {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//

// A linked-list is a dynamica data sturcture that allows us to grow and shrink the size of the sturcture by one element at a time.
// We need a linked list for our history class:
// p_head -----> Transaciton
      // p_next -----> Transaciton
            // p_next -----> Transaction
                  // p_next -----> nullptr


// Constructor
// TASK 3
//This is the default constructor. It will set the Transaction *p_head to nullptr .

History::History ()
{
  this->p_head = nullptr;
}


// Destructor
// TASK 3
// Destructor is a member function that automatically called when the object gose out of scope or gets de-allocated.

History::~History ()
{
  Transaction * current_transaction{p_head};
  Transaction * delete_transaction{current_transaction};
  while (current_transaction != nullptr)
  {
    delete_transaction = current_transaction;
    current_transaction = current_transaction->get_next();
    delete_transaction->set_next(nullptr);
    delete delete_transaction;
  }
  this->p_head = nullptr;
}


// read_history(...): Read the transaction history from file.
// TASK 4
// read_history is going to read transaction info from file (one transacition at a time, and call insert(...) for each transaction) to compelte a linked-list.
// This is where the dynamica allocation of transaction happen, we need to create a linked list.
// For read_history, what is the input and output? 
    //input:
      //we need to have a file to read (input the file)
    //output:
      //we need to out put a linked-list with all the transaction inserted.
      //A linked-list is a series of dymamically allocated objectes that are joined together using pointers.

// SUDO code:
/*
  open the file (we have been given a number of functions called ece150)
  read transactions (one at a time)
      for specific parts: day, month, year...
      dynamically allocate the Transaction objects
      call insert
  close the file
Data Structure:

*/
void History::read_history()
{
  //first we open the file with given function ece150::open file...(at pdf page 3)
  //This opens the file named transaction_history.txt for reading. This function must be called before any of the provided functions.
  ece150::open_file();
  // use next_trans_entry to read history files (read one line per call)
  while( ece150::next_trans_entry() != false )
  {
    //value from ece150 library.
    // create a new transaction pointer to store history files
    Transaction * p_transaction { new Transaction { ece150::get_trans_symbol(),
                                                    ece150::get_trans_day(),
                                                    ece150::get_trans_month(),
                                                    ece150::get_trans_year(),
                                                    ece150::get_trans_type(), 
                                                    ece150::get_trans_shares(), 
                                                    ece150::get_trans_amount()} };
    //call insert function and insert the read transaction (p_transaction) to the linked-list.
    //std::cout << "in read history";
    //p_transaction->print();
    //std::cout << std::endl;
    insert (p_transaction);
    //p_transaction = nullptr;
  }

  //we close the file with given function (at pdf page 3)
  //This closes the file named transaction_history.txt for reading. This function must be called once the reading of the file is complete.
  ece150::close_file();
}

// insert(...): Insert transaction into linked list.
// TASK 5
  //This is a custome data type using pointers.
  // Inserts a new Transaction instance to the end of the linked list of transactions. You must have dynamically allocated an instance to Transaction class and pass the pointer to that as an argument to this member function.
  // What are the desired output and input for insert(...) function?
  // input: state of history(within history): p_head -> nullptr, We are also getting one pointer to a d-allocated Transaction (i.e new node) that is to be inserted
      // history
      // p_new_trans -> Transaction
              // p_next ---> nullptr
  // output: The  linked-list will contain a new node (single)
  // history
      // p_head -> Transaction
              // p_next ---> nullptr
  
//worked throught insert function with Dr. David Lau
void History::insert ( Transaction * p_new_trans)
{
  //we need to have p_head to point p_new_trans only at the very first node
  //we need to find the right p_next pointer to modefy (there are three p_next pointer)
      // To find the correct p_next pointer, we need to use another pointer to go through the linked-list until we find the right p_next pointer.
  p_new_trans->set_next(nullptr);
  if (this->p_head == nullptr)
  {
    //std::cout << "HERE" << std::endl;
    this->p_head = p_new_trans;
  }
  //after executng this->p_head = p_new_trans; both p_head and p_new_trans are pointing to the transaction to be inserted.
  //History
  // p_head -----> Transaciton
      // p_next -----> Transaciton
            // p_next -----> Transaction
                 // p_next -----> nullptr
//p_through pointing to the first p_next
//if we can move the p_through to pointing the last transaction(node, nullptr), we cab=n use the p_throught to modify the p_next pointer of the last transaction.
  else
  {
    Transaction * p_through {p_head};
    //std::cout << "hello" << std::endl;
    //p_through->print();
    while (p_through->get_next() != nullptr)
    {
      p_through = p_through->get_next(); //or p_through = (*p_through).get_next();
    }
    //we need the setn_next to gain access to the private
    p_through->set_next(p_new_trans);
  }
}

bool compare_id(Transaction t1, Transaction t2)
{
  if (t1.get_year() == t2.get_year() && t1.get_month() == t2.get_month()  && t1.get_day() == t2.get_day())
  {
    return t1.get_trans_id() < t2.get_trans_id();
  }
  return false;
}


// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//bool unsorted = true;
// while(unsorted) {
//     unsorted = false;
//     cur = head;         

//     while(cur != nullptr) {
//         next = cur->next;
//         if(next < cur) {
//             swap(cur, next)
//             unsorted = true;
//         }

//         cur = cur->next;
//     }       
// }
// 1. declare a new transaction pointer.
// 2. we need to have a place holder to point to the removed. (p_head is now pointing the second)
// 3. p_head = p_head(first element)->p_next
void History::sort_by_date()
{
  Transaction * sorted_list {nullptr};
  Transaction * removed_transaction{p_head};
  Transaction * current_transaction{sorted_list};

  while ( p_head != nullptr )
  {
    removed_transaction = p_head;
    p_head = p_head->get_next();
    //let removed tranaction became a single transaction
    removed_transaction->set_next(nullptr);

    if (sorted_list == nullptr)
    {
      sorted_list = removed_transaction;
    }
    else
    {
      current_transaction = sorted_list;
      // current_transaction->print();
      // std::cout << "Before if" << std::endl;
      // removed_transaction->print();
      if ( *current_transaction < *removed_transaction || compare_id(*current_transaction, *removed_transaction) )
      {
        while (current_transaction != nullptr)
        {
          if ( current_transaction->get_next() == nullptr)
          {
            current_transaction->set_next(removed_transaction);
            break;
          }
          else if ( *removed_transaction < *current_transaction->get_next() || compare_id(*current_transaction, *removed_transaction) )
          {
            removed_transaction->set_next( current_transaction->get_next() );
            current_transaction->set_next( removed_transaction );
            break;
          }
          else
          {
            current_transaction = current_transaction->get_next();
          }
        }
      }
      else
        {
          // std::cout << "change head" << std::endl;
          // sorted_list->print();
          // std::cout << "remove transaction" << std::endl;
          removed_transaction->print();
          removed_transaction->set_next(sorted_list);
          sorted_list = removed_transaction;
          // sorted_list->print();
          // std::cout << "end of change lane" << std::endl;
        }
    }
  }

  p_head = sorted_list;
}


// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
// You will implement a member function called update_acb_cgl() for the History class that
// computes appropriate values for the private member variables that were not initialized with the
// data from the input file. These are acb , acb_per_share , share_balance , and cgl . In this
// member function, you should compute these and set them in their respective transaction
// instances in the linked list.
void History::update_acb_cgl()
{
  double current_acb{0.0};
  int currentSB {0};
  Transaction *current_trans{ p_head };
  double currentCGL{ 0.0 };

  while ( current_trans != nullptr )
  {
    if ( current_trans->get_trans_type()  )
    {
      current_acb = current_acb + current_trans->get_amount();
      currentSB = currentSB + current_trans->get_shares();
      current_trans->set_cgl( 0.0 );
    }
    else
    {
      current_acb =  current_acb - ( current_trans->get_shares() * current_acb/currentSB );
      currentSB = currentSB - current_trans->get_shares();
      currentCGL = ( current_trans->get_amount() - ( current_trans->get_shares() * current_acb/currentSB ) );
      current_trans->set_cgl( currentCGL );
    }
    //set currentSB and current_acb
    current_trans->set_acb(current_acb);
    current_trans->set_share_balance(currentSB);
    current_trans->set_acb_per_share(current_acb/currentSB);

    current_trans = current_trans->get_next();
  }

  // p_head = first transaction amount paid
  // p_head->p_next
  // double get_acb() const;
  // double get_acb_per_share() const;
  // unsigned int get_share_balance() const;
  // double get_cgl() const;

  // //sets private member variable
  // void set_acb( double acb_value );
  // void set_acb_per_share( double acb_per_share_value );
  // void set_share_balance( unsigned int balance );
  // void set_cgl ( double value );
}



// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8
// You will implement a member function called compute_cgl(…) for the History class that will
// return a double , which is the CGL for the year provided as a parameter.
double History::compute_cgl ( unsigned int year )
{
  Transaction *current_trans{ p_head };
  double currentCGL{ 0.0 };

  while ( current_trans != nullptr )
  {
    if ( current_trans->get_year() == year )
    {
      currentCGL = currentCGL + current_trans->get_cgl();
    }
    current_trans = current_trans->get_next();
  }
  return currentCGL;
}


// print() Print the transaction history.
//TASK 9
//

void History::print ()
{ // Create a copy p_head and use current_transaction to get current transaction in the linked-list
  Transaction * current_transaction{p_head};
  std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;
  while (current_transaction != nullptr)
  {
    current_transaction->print();
    current_transaction = current_transaction->get_next();
  }
  std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;
}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }
