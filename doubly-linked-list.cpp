#include "doubly-linked-list.h"
#include <iostream>
#include <new>

DoublyLinkedList::Node::Node(DataType data):
        value(data), next(NULL), prev(NULL)
{
}
DoublyLinkedList::DoublyLinkedList()
        :head_(NULL), tail_(NULL), size_(0)
{
}
/*DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& list)
:size_(list.size_)
{
	


}*/
DoublyLinkedList::~DoublyLinkedList()
{
    


}
bool DoublyLinkedList::empty() const
{
    if (size_ == 0)
        return true;
    return false;
}
unsigned int DoublyLinkedList::size() const
{
    return size_;
}
void DoublyLinkedList::print() const
{
   std::cout << std::endl;
    Node *temp = head_;
    while (temp != NULL){
        std::cout << temp->value<< " - ";
        temp = temp->next;
    }
    std::cout << std::endl;
}
bool DoublyLinkedList::insert_front(DataType value)
{
    Node *new_node = new Node(value);
    new_node->next = head_;//should work for empty list bc head is null
    new_node->prev = NULL;
    if (empty()){
        tail_ = new_node;
    } else {
        head_->prev = new_node;
    }
    head_ = new_node; //pointer might be errant
    size_++;
    return true;
}
bool DoublyLinkedList::remove_front()
{
    if (size_ == 0)
        return false;
    if (size_ == 1){
        delete(head_); //this might be a bad idea?
        head_ = NULL;
        tail_ = NULL;
    } else {
        head_ = head_->next; // might be a memory leak here
        head_->prev = NULL;
    }
    size_--;
    return true;
}
bool DoublyLinkedList::insert_back(DataType value) {
    Node *new_node = new Node(value);
    new_node->next = NULL; //not necessary already set to null
    if (size_==0){
        head_ = new_node;
        new_node->prev = NULL;
    } else { //if (tail_ != NULL){
        tail_->next = new_node;
    }
    new_node->prev = tail_; // if first tail should be null
    tail_ = new_node;
    size_++;
    return true;
}
bool DoublyLinkedList::remove_back()
{
    if (size_ == 0)
        return false;
    if (size_ == 1){
        head_ = NULL;
        tail_ = NULL;
    } else {
        tail_ = tail_->prev;
        tail_->next = NULL;
    }
    size_--;
    return true;
}
bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    Node *in = new Node(value);
    if ( index==0 ) {
        if ( size_== 0 ) {
            head_ = in;
            tail_ = in;
        }
        else {
            head_ -> prev = in;
            in -> next = head_;
            head_ = in;
        }
    } else if ( index==size_ ){
        in -> prev = tail_;
        tail_ -> next = in;
        tail_ = in;
    }else if ( index>size_ ) {
        return false;
    }else {
        int cnt = 0;
        Node* curr = head_;
        while ( cnt<index-1 ) {
            curr = curr -> next;
            ++ cnt;
        }
        in -> prev = curr;
        in -> next = curr -> next;
        curr -> next = in;
        in -> next -> prev = in;
    }
    ++ size_;
    return true;
}
bool DoublyLinkedList::remove(unsigned int index)
{
    if (size_ == 0 || index >= size_)
        return false;
    if (index == 0) {
        remove_front();
    } else if (index == size_-1) {
        remove_back();
    } else {
        Node *pre = getNode(index)->prev;
        Node *aft = getNode(index)->next;
        pre->next = aft;
        aft->prev = pre;
        size_--;
    }
    return true;
}
unsigned int DoublyLinkedList::search(DataType value) const
{
    Node *temp = head_;
    unsigned int cnt = 0;
    while (temp != NULL){
        if (temp->value == value){
            return cnt;
        }
        cnt++;
        temp = temp->next;
    }
    return size_;
}
DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    if (index > size_)
        return tail_->value;
    Node *temp = head_;
    for (int i = 0; i < index; i++){
        temp = temp->next;
    }
    return temp->value;
}
bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    if (size_ == 0)
        return false;
    getNode(index)->value = value;
    return true;
}
DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    Node *temp = head_;
    for (int i = 0; i < index ; i++){
        temp = temp->next;
    }
    return temp;
}
bool DoublyLinkedList::full() const
{
    if (size_ == CAPACITY)
        return true;
    return false;
}

unsigned int DoublyLinkedList::capacity() const {
    return CAPACITY;
}
