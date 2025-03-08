#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T> // Use private inheritance to restrict access to vector member functions
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
};
// Constructor
template <typename T>
Stack<T>::Stack() : std::vector<T>()  // Calls std::vector<T>'s default constructor
{
}
// Destructor
template <typename T>
Stack<T>::~Stack()
{
}
// Empty()
template <typename T>
bool Stack<T>::empty() const
{
    return std::vector<T>::empty(); // Calls std::vector<T>'s empty() function
}
// Size()
template <typename T>
size_t Stack<T>::size() const
{
    return std::vector<T>::size(); // Calls std::vector<T>'s size() function
}
// Push()
template <typename T>
void Stack<T>::push(const T& item)
{
    std::vector<T>::push_back(item); // Adds item to "top" of stack by appending to end of the vector container
}
// Pop()
template <typename T>
void Stack<T>::pop()
{
    if (empty()) { // Throws error if stack is empty
        throw std::underflow_error("Attempted pop() on an empty stack");
    }
    std::vector<T>::pop_back(); // Removes item from "top" of stack by popping from end of the vector container
}
// Top()
template <typename T>
const T& Stack<T>::top() const
{
    if (empty()) { // Trhows error if stack is empty
        throw std::underflow_error("Attempted top() on an empty stack");
    }
    return std::vector<T>::back(); // Returns item from "top" of stack by returning end of the vector container
}


#endif