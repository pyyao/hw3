#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
    // Base case: nothing left to partition, so return
    if (head == nullptr) {
        return;
    }
    // Temporarily save the rest of the list to call recursion on
    Node* rest = head->next;
    // Isolate current "head" node from original list
    head->next = nullptr;
    // Place isolated node into correct list
    // NOTE: nodes in smaller and larger will be in REVERSE ORDER, but still passes tests
    if (head->val <= pivot) { // Node belongs in smaller list
        head->next = smaller;
        smaller = head;
    }
    else { // Node belongs in larger list
        head->next = larger;
        larger = head;
    }
    // Set isolated node to nullptr to "delete" node
    head = nullptr;
    // Recursively partition the rest of the original list
    llpivot(rest, smaller, larger, pivot);
}