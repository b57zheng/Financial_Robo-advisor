////////////////////////////////////
// Project: Financial Robo Advisor
// Authors: Bowen Zheng, Electrical Engineering, University of Waterloo
// compile and run this program with command:
// g++ -o main History_Transaction_definitions.cpp project4.cpp main.cpp -std=c++11
// ./main      
////////////////////////////////////

#include <cassert>
#include <iomanip>
#include <iostream>
#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"


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
  trans_id = assigned_trans_id;
  //increament of assigned_trans_id
  ++assigned_trans_id;
}



// Destructor
Transaction::~Transaction ()
{

}


// Overloaded < operator.”
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

// Member functions to get values.
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

// Member functions to set values.
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// Print the transaction.
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

// Constructor
History::History ()
{
  this->p_head = nullptr;
}


// Destructor
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
void History::read_history()
{
  ece150::open_file();
  while( ece150::next_trans_entry() != false )
  {
    Transaction * p_transaction { new Transaction { ece150::get_trans_symbol(),
                                                    ece150::get_trans_day(),
                                                    ece150::get_trans_month(),
                                                    ece150::get_trans_year(),
                                                    ece150::get_trans_type(), 
                                                    ece150::get_trans_shares(), 
                                                    ece150::get_trans_amount()} };
    insert (p_transaction);

  }
  //we close the file with given function (at pdf page 3)
  ece150::close_file();
}

// insert(...): Insert transaction into linked list.
void History::insert ( Transaction * p_new_trans)
{
  p_new_trans->set_next(nullptr);
  if (this->p_head == nullptr)
  {
    this->p_head = p_new_trans;
  }
  else
  {
    Transaction * p_through {p_head};
    while (p_through->get_next() != nullptr)
    {
      p_through = p_through->get_next();
    }
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
void History::sort_by_date()
{
  Transaction * sorted_list {nullptr};
  Transaction * removed_transaction{p_head};
  Transaction * current_transaction{sorted_list};

  while ( p_head != nullptr )
  {
    removed_transaction = p_head;
    p_head = p_head->get_next();
    removed_transaction->set_next(nullptr);

    if (sorted_list == nullptr)
    {
      sorted_list = removed_transaction;
    }
    else
    {
      current_transaction = sorted_list;
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
          removed_transaction->print();
          removed_transaction->set_next(sorted_list);
          sorted_list = removed_transaction;
        }
    }
  }

  p_head = sorted_list;
}


// update_acb_cgl(): Updates the ACB and CGL values.
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
}



// compute_cgl(): )Compute the ACB, and CGL.
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
void History::print ()
{
  Transaction * current_transaction{p_head};
  std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;
  while (current_transaction != nullptr)
  {
    current_transaction->print();
    current_transaction = current_transaction->get_next();
  }
  std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;
}

// get_p_head(): Full access to the linked list.
Transaction *History::get_p_head() { return p_head; }
