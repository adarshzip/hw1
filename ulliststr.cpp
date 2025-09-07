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

void ULListStr::push_back(const std::string& val){
  if(tail_==nullptr){ //no tail
    tail_ = new Item();
    head_ = tail_;

    tail_->first = 0; 
    tail_->last = 1; 
    tail_->val[0] = val; 

    size_ += 1; 
  }

  else if(tail_->last < ARRSIZE){ //existing tail, empty array spaces
    tail_->val[tail_->last] = val;
    tail_->last += 1; 
    size_ += 1;
  }

  else { // existing tail, no empty array spaces
    Item* newTail = new Item();
    newTail->first = 0; 
    newTail->last = 1; 
    newTail->val[0] = val;

    newTail->prev = tail_;
    tail_->next = newTail;

    tail_ = newTail;
    size_ += 1; 
  }

  return;
}


void ULListStr::push_front(const std::string& val){
  if(head_ == nullptr){ // non existent head
    head_ = new Item();
    tail_ = head_;

    head_->first = ARRSIZE - 1; 
    head_->last = ARRSIZE; // more efficient head node allocation since only pushing front

    head_->val[head_->first] = val; 
    size_ += 1; 
  }

  else if(head_->first > 0){ // existing head, empty spaces
    head_->first -= 1; 
    head_->val[head_->first] = val;

    size_ += 1;
  }

  else { //existing head, no empty spaces
    Item* newHead = new Item();
    
    newHead->first = ARRSIZE - 1; 
    newHead->last = ARRSIZE;

    newHead->val[newHead->first] = val;

    newHead->next = head_;
    head_->prev = newHead;

    head_ = newHead;
    size_ += 1; 
  }

  return; 
}


void ULListStr::pop_back(){
  if(size_ == 0){
    return; 
  }

  tail_->last -= 1; 
  size_ -= 1; 

  if(tail_->last == tail_->first) {
    if(head_ == tail_){
      delete tail_;
      head_ = tail_ = nullptr; 
    } 
    
    else {
      tail_ = tail_->prev; 
      delete tail_->next; 
      tail_->next = nullptr; 
    }
  }
}


void ULListStr::pop_front(){
  if(size_ == 0){
    return; 
  }

  head_->first += 1; 
  size_ -= 1; 

  if(head_->first == head_->last) {
    if(head_ == tail_){
      delete tail_;
      head_ = tail_ = nullptr; 
    } 
    
    else {
      head_ = head_->next; 
      delete head_->prev; 
      head_->prev = nullptr; 
    }
  }
}


std::string const & ULListStr::back() const {
  if (size_ == 0){
    return nullptr;
  }
  else {
    return tail_->val[tail_->last - 1];
  }
}


std::string const & ULListStr::front() const {
  if (size_ == 0){
    return nullptr;
  }
  else {
    return head_->val[head_->first];
  }
}


std::string* ULListStr::getValAtLoc(size_t loc) const{
  Item* traverse = head_; 
  size_t toGo = loc; 

  if (loc >= size_){
    return nullptr;
  }

  while(traverse != nullptr){
    if(toGo < (traverse->last - traverse->first)){
      return &traverse->val[traverse->first + toGo];
    }
    else {
      toGo -= (traverse->last - traverse->first);
      traverse = traverse->next; 
    }
  }

  return nullptr;
}


// below functions alr implemented

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
