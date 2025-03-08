#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------
struct IsOdd {
    bool operator()(int value) {
        return (value % 2) != 0;  // returns true if value is odd
    }
};

struct IsEven {
    bool operator()(int value) {
        return (value % 2) == 0;      // returns true if value is even
    }
};

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------

    // 1) Test llpivot()
    // Read the list from file
    Node* head = readList(argv[1]);

    cout << "Original list for pivot test:" << endl;
    print(head);

    // Choose a pivot (you could parse from argv if you like)
    int pivotVal = 10;
    Node* smaller = nullptr;
    Node* larger = nullptr;

    // Partition the list
    llpivot(head, smaller, larger, pivotVal);

    cout << "Pivot value = " << pivotVal << endl;
    cout << "smaller (<= pivot): ";
    print(smaller);
    cout << "larger  (> pivot): ";
    print(larger);

    // Clean up
    dealloc(smaller);
    dealloc(larger);
    // 'head' is now nullptr due to llpivot()

    cout << endl;

    // 2) Test llfilter()
    // Read the list again (since the previous call to llpivot used it up)
    head = readList(argv[1]);

    cout << "Original list for filter test:" << endl;
    print(head);

    // Example: filter out odd numbers
    Node* filtered = llfilter(head, IsOdd());
    cout << "After removing odd values:" << endl;
    print(filtered);

    // Clean up
    dealloc(filtered);

    cout << endl;

    // Optionally, do another test: for example, remove anything > 5
    head = readList(argv[1]);
    cout << "Original list again (for second filter test):" << endl;
    print(head);

    Node* filtered2 = llfilter(head, IsEven());
    cout << "After removing even values" << endl;
    print(filtered2);

    // Clean up again
    dealloc(filtered2);

    return 0;

}
