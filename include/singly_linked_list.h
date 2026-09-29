#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
struct SNode {
    T value;
    SNode* next;

    explicit SNode(const T& v, SNode* n = nullptr) : value(v), next(n) {}
};

template <typename T>
class SLinkedList {
public:
    SLinkedList();
    ~SLinkedList();
    SLinkedList(const SLinkedList& other);
    SLinkedList& operator=(const SLinkedList& other);

    void push_front(const T& value);
    void push_back(const T& value);
    bool pop_front();
    bool pop_back();

    T& front();
    const T& front() const;
    std::size_t size() const noexcept;
    bool empty() const noexcept;
    bool contains(const T& value) const;
    std::vector<T> to_vector() const;
    void clear();

private:
    SNode<T>* head_;
    std::size_t size_;
};

template <typename T>
SLinkedList<T>::SLinkedList() : head_(nullptr), size_(0) {
    size_ = 0;
    head_ = new SNode<T>(T(), nullptr);
    head_->next = nullptr;
}

template <typename T>
SLinkedList<T>::~SLinkedList() {
//TODO: Implement the destructor for the SLinkedList class
    clear();
    delete head_;
}

template <typename T>
SLinkedList<T>::SLinkedList(const SLinkedList& other) : head_(nullptr), size_(0) {
//TODO: Implement the copy constructor for the SLinkedList class
    head_ = new SNode<T> (T(), nullptr);
    head_->next = nullptr;
    for (SNode<T>* curr = other.head_->next; curr != nullptr; curr = curr->next)
        push_back(curr->value);

}

template <typename T>
SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList& other) {
    if (this != &other) {
        clear();
        for (SNode<T>* current = other.head_->next; current != nullptr; current = current->next) {
            push_back(current->value);
        }
    }
    return *this;
}

template <typename T>
void SLinkedList<T>::push_front(const T& value) {
    SNode<T>* new_node = new SNode<T>(value, head_->next);
    head_->next = new_node;
    ++size_;
}

template <typename T>
void SLinkedList<T>::push_back(const T& value) {
    SNode<T>* last_node = head_;
    while (last_node->next != nullptr) {
        last_node = last_node->next;
    }
    last_node->next = new SNode<T>(value, nullptr);
    ++size_;
}

template <typename T>
bool SLinkedList<T>::pop_front() {
    if (empty()) {
        return false;
    }
    SNode<T>* popNode = head_->next;
    head_->next = popNode->next;
    delete popNode;
    --size_;
    return true;
}

template <typename T>
bool SLinkedList<T>::pop_back() {
    if (empty()) {
        return false;
    }
    SNode<T>* previous = head_;
    while (previous->next->next != nullptr) {
        previous = previous->next;
    }
    delete previous->next;
    previous->next = nullptr;
    --size_;
    return true;
}

template <typename T>
T& SLinkedList<T>::front() {
// TODO: Implement the front function for the SLinkedList class
    if (empty()) {
        throw std:: out_of_range("SLinkedList is empty");
    }
    return head_->next->value;
}

template <typename T>
const T& SLinkedList<T>::front() const {
    if (empty()) {
        throw std::out_of_range("SLinkedList is empty");
    }
    return head_->next->value;
}

template <typename T>
std::size_t SLinkedList<T>::size() const noexcept {
// TODO: Implement the size function for the SLinkedList class
    return size_;
}

template <typename T>
bool SLinkedList<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
bool SLinkedList<T>::contains(const T& value) const {
// TODO: Implement the contains function for the SLinkedList class
    for (SNode<T>* current = head_->next; current != nullptr; current = current->next) {
        if(current->value == value)
            return true;
    }
    return false;
}

template <typename T>
std::vector<T> SLinkedList<T>::to_vector() const {
    std::vector<T> values;
    values.reserve(size_);
    for (SNode<T>* current = head_->next; current != nullptr; current = current->next) {
        values.push_back(current->value);
    }
    return values;
}

template <typename T>
void SLinkedList<T>::clear() {
    SNode<T>* curr = head_->next;
    while (curr != nullptr) {
        SNode<T>* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    head_->next = nullptr;
    size_ = 0;
}
