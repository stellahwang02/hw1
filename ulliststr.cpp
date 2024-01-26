#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
// You need to examine the code provided in ulliststr.h 
// and ulliststr.cpp and add the implementations for 
// push_back, push_front, pop_back, pop_front, back, front and 
// getValAtLoc in ulliststr.cpp.

void ULListStr::push_back(const std::string& val) {
  // check and see if the list is empty. If so, set head and tail equal to the new node
  if (empty()) {
    // new head node
    head_ = new Item();
    tail_ = head_;
  }
  // check to see if the last node is full
  if (tail_->last == ARRSIZE) {
    // create a new node and update
    Item* newTail = new Item();
    tail_->next = newTail;
    
    newTail->prev = tail_;
    tail_->next = newTail;
    tail_ = newTail;
  }
  // adding the values at the back of the list 
  tail_->val[tail_->last] = val;
  tail_->last++;
  size_++;
}


void ULListStr::push_front(const std::string& value) {
  // check to see if the head is NULL or full
  if (head_ == nullptr) {
    // new head node
    head_ = new Item();
    tail_ = head_;
    head_->val[ARRSIZE-1] = value;
    head_->first = ARRSIZE-1;
    head_->last = ARRSIZE;
  }
  // Add the value to the head node
  else if (head_->first != 0) {
    head_->val[--head_->first] = value;
  }
  else {
    head_->prev = new Item();
    Item* temp = head_;
    head_ = head_->prev;
    head_->next = temp;
    head_->val[ARRSIZE-1] = value;
    head_->first = ARRSIZE-1;
    head_->last = ARRSIZE;
  }
  //first and last are the index of the array
  ++size_;
}


void ULListStr::pop_back() {
  // if the list is already empty, there's nothign to pop back
  if (empty()) {
    return;
  }
  if (tail_->last - tail_->first > 1) { // more than one element
    tail_->last--;
  }
  else if (tail_ == head_) { // only one node
    delete tail_;
    head_ = NULL;
    tail_ = NULL;
    }
  else { 
      Item* temp = tail_;
      tail_ = tail_->prev;
      delete temp;
      tail_->next = NULL; // there's no next item
    }
    size_--;
  }

void ULListStr::pop_front() {
  // if the list is not empty
  if (empty()) {
    return;
  }
  // more than one element
  if (head_->last - head_->first > 1) {
    head_->first++;
  }
  // only one node
  else if (tail_ == head_) {
      delete head_;
      head_ = NULL;
      tail_ = NULL;
    }
  else {
    Item* temp = head_;
    head_ = head_->next;
    delete temp;
    head_->prev = NULL;
    }
    size_--;
  }

std::string const& ULListStr::back() const {
  /**
   * Returns a const reference to the back element
   *   - MUST RUN in O(1)
   */

  // assume the list is not empty 
  if (!empty()) {
    return tail_->val[tail_->last-1];
  }
}


std::string const& ULListStr::front() const {
  /**
   * Overwrites the old value at index, pos, with val
   *   - Can run in O(n)
   */
  if (!empty()) {
    return head_->val[head_->first];
  }
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
  /** 
   * Returns a pointer to the item at index, loc,
   *  if loc is valid and NULL otherwise
   *   - MUST RUN in O(n) 
   */
  // iterate to find the location
  Item* current = head_;
  size_t count = 0;

  while (current != nullptr) {
    // if the location is in the current node's range
    if (count + (current->last - current->first) > loc) {
      // calc the index within the node's array
      size_t index = loc - count + current->first;
      return &(current->val[index]);
    }
    // move the node to the next
    count += (current->last - current->first);
    current = current->next;
  }
  return nullptr;
  
}


void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == nullptr){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == nullptr){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == nullptr){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != nullptr){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = nullptr;
  size_ = 0;
}
