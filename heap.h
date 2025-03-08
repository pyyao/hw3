#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector> // Include vector for vector container of heap

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  void heapifyUp(size_t idx); // Helper function to restore heap property upward (for push())
  void heapifyDown(size_t idx); // Helper function to restore heap property downward (for pop())
  // Data members
  std::vector<T> store_;   // Underlying vectory container
  int m_;                  // Determines "m-ary"ness of tree
  PComparator comp_;       // Comparator
};

// Add implementation of member functions here
// Constructor
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : m_(m), comp_(c)
{
}
// Destructor
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
}
// Push()
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  store_.push_back(item); // First, add new item to end of heap
  heapifyUp(store_.size() - 1); // Call helper fn heapifyUP to move item to correct position in heap
}
// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return store_[0]; // Top element of heap is first element in vectory container
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  store_[0] = store_.back(); // First, move top item to last position in vector container
  store_.pop_back(); // Next, remove top item from last position in vector container
  if(!empty()){ // Check remaining heap is not empty
    heapifyDown(0); // If not empty, call helper fn heapifyDown to restore heap property
  }
}
// Empty()
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return store_.empty();
}
// Size()
template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return store_.size();
}
// Helper functions
// HeapifyUp()
template <typename T, typename PComparator>
void Heap<T,PComparator>::heapifyUp(size_t idx)
{
  while(idx > 0) { // Perform heapifyUp until break or item is moved to top position of heap
    size_t parent = (idx - 1) / m_; // Calculate parent index in m-ary heap
    if(comp_(store_[idx], store_[parent])) { // If current node has greater "priority" than parent node, swap
      std::swap(store_[idx], store_[parent]);
      idx = parent; // Update node's index to the index of the parent node
    } 
    else { // Parent node has higher "priority" and heap priority is restored
      break;
    }
  }
}
// HeapfiyDown()
template <typename T, typename PComparator>
void Heap<T,PComparator>::heapifyDown(size_t idx)
{
  while(true) { // Perform heapifyDown until heap property is restored
    size_t best = idx; // best stores index of node with highest "priority," initialized to current idx
    for(int i = 1; i <= m_; i++) { // For m-ary tree, need to check up to m children
      size_t child = m_*idx + i; // Calculate index of child node
      if(child < store_.size() && comp_(store_[child], store_[best])) { // If child node is within range and has higher "priority", update best
        best = child;
      }
    }
    if(best == idx) { // If after checking m children, current idx is still best, heap property is restored
      break;
    }
    std::swap(store_[idx], store_[best]); // Swap current idx with child with higher "priority"
    idx = best; // Update idx to continue performing heapifyDown
  }
}


#endif

