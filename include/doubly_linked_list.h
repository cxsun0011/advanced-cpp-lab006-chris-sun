#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
struct DNode {
    T value;
    DNode* prev;
    DNode* next;

    explicit DNode(const T& v, DNode* p = nullptr, DNode* n = nullptr)
        : value(v), prev(p), next(n) {}
};

template <typename T>
class DLinkedList {
public:
    DLinkedList();
    ~DLinkedList();
    DLinkedList(const DLinkedList& other);
    DLinkedList& operator=(const DLinkedList& other);

    void push_front(const T& value);
    void push_back(const T& value);
    bool pop_front();
    bool pop_back();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    std::size_t size() const noexcept;
    bool empty() const noexcept;
    bool contains(const T& value) const;
    std::vector<T> to_vector() const;
    void clear();

private:
    DNode<T>* header_;
    DNode<T>* trailer_;
    std::size_t size_;
};

template <typename T>
DLinkedList<T>::DLinkedList() : size_(0) { //constructor
    header_ = new DNode<T>(T(), nullptr, nullptr);
    trailer_ = new DNode<T>(T(), nullptr, nullptr);
    header_->next = trailer_;
    trailer_->prev = header_;
}

//TODO: Implement the destructor, copy constructor, assignment operator, and other member functions for the DLinkedList class.
template <typename T>
DLinkedList<T>::~DLinkedList() {
    clear();
    delete header_;
    delete trailer_;
}

//TODO: Implement the copy constructor for the DLinkedList class.
template <typename T>
DLinkedList<T>::DLinkedList(const DLinkedList& other) : size_(0) {
    header_ = new DNode<T>(T(), nullptr, nullptr);
    trailer_ = new DNode<T>(T(), nullptr, nullptr);
    header_ ->next = trailer_;
    trailer_->prev = header_;

    for(DNode<T>* curr = other.header_->next; curr != other.trailer_; curr = curr->next) {
        push_back(curr->value);
    }
}

// TODO: Implement the assignment operator for the DLinkedList class.
template <typename T>
DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList& other) {
    if(this != &other) {
        clear();
        for(DNode<T>* curr = other.header_->next; curr != other.trailer_; curr = curr->next) {
            push_back(curr->value);
        }
    }
    return *this;
}

//TODO: Implement the push_front function for the DLinkedList class.
template <typename T>
void DLinkedList<T>::push_front(const T& value) {
    DNode<T>* new_node = new DNode<T>(value, header_, header_->next);
    header_->next->prev = new_node;
    header_->next = new_node;
    size_++;
}

//TODO: Implement the push_back function for the DLinkedList class.
template <typename T>
void DLinkedList<T>::push_back(const T& value) {
    DNode<T>* new_node = new DNode<T>(value, trailer_->prev, trailer_);
    trailer_->prev->next = new_node;
    trailer_->prev = new_node;
    size_++;
}


//TODO: Implement the pop_front function for the DLinkedList class.
template <typename T>
bool DLinkedList<T>::pop_front() {
    if (empty()) {
        return false;
    }
    DNode<T>* node_to_delete = header_->next;
    header_->next = node_to_delete -> next;
    node_to_delete->next->prev = header_;
    delete node_to_delete;
    size_--;
    return true;
}

//TODO: Implement the pop_back function for the DLinkedList class.
template <typename T>
bool DLinkedList<T>::pop_back() {
    if(empty()) {
        return false;
    }
    DNode<T>* node_to_delete = trailer_->prev;
    trailer_ -> prev = node_to_delete -> prev;
    node_to_delete->prev->next = trailer_;
    delete node_to_delete;
    size_--;
    return true;

}

//TODO: Implement the front function for the DLinkedList class
template <typename T>
T& DLinkedList<T>::front() {
    if (empty()) {
        throw std::out_of_range("front() called on empty list");
    }
    return header_ -> next -> value;
}

template <typename T>
const T& DLinkedList<T>::front() const {
//TODO: Implement the const version of the front function for the DLinkedList class
    if (empty()) {
        throw std::out_of_range("front() called on empty list");
    }
    return header_ -> next -> value;
}

template <typename T>
T& DLinkedList<T>::back() {
//TODO: Implement the back function for the DLinkedList class
    if (empty()) {
        throw std::out_of_range("back() called on empty list");
    }
    return trailer_ -> prev -> value;
}

template <typename T>
const T& DLinkedList<T>::back() const {
//TODO: Implement the const version of the back function for the DLinkedList class
    if (empty()) {
        throw std::out_of_range("back() called on empty list");
    }
    return trailer_ -> prev -> value;
}

template <typename T>
std::size_t DLinkedList<T>::size() const noexcept {
//TODO: Implement the size function for the DLinkedList class
    return size_;
}

template <typename T>
bool DLinkedList<T>::empty() const noexcept {
//TODO: Implement the empty function for the DLinkedList class
    if(size_ == 0)
        return true;
    return false;
}

template <typename T>
bool DLinkedList<T>::contains(const T& value) const {
//TODO: Implement the contains function for the DLinkedList class
    for(DNode<T>* curr = header_->next; curr!= trailer_; curr=curr->next) {
        if(curr->value == value)
            return true;
    }
    return false;
}

template <typename T>
std::vector<T> DLinkedList<T>::to_vector() const {
// TODO: Implement the to_vector function for the DLinkedList class
    std::vector<T> vec;
    vec.reserve(size_);
    for (DNode<T>* curr = header_->next; curr != trailer_; curr = curr->next) {
        vec.push_back(curr->value);
    }
    return vec;
}

template <typename T>
void DLinkedList<T>::clear() {
// TDOO: Implement the clear function for the DLinkedList class
    DNode<T>* curr = header_->next;
    while(curr != trailer_) {
        DNode<T>* next_node = curr->next;
        delete curr;
        curr = next_node;
    }
    header_->next = trailer_;
    trailer_->prev = header_;
    size_ = 0;
}
