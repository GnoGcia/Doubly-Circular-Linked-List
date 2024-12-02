#include <iostream>
#include <sstream>

using namespace std;

// Forward List Declaration
class List;

// Doubly Circular Linked Node Class
class Node {
    private:
        // Node Data
        string data;
        // Node Links
        Node* prev;
        Node* next;
        // Node Friends
        friend class List;
        friend class Iterator;
    public:
        // Parameterized Constructor
        Node(string element) {
            // Initialize with Existing Data
            data = element;
            // Links Point to Self
            prev = this;
            next = this;
        }
};
// Helper Class for Linked List Traversal
class Iterator {
    private:
        // Node and List References
        Node* pos;
        List* container;
        // Iterator Friend
        friend class List;
    public:
        // Default Constructor
        Iterator() {
            pos = nullptr;
            container = nullptr;
        }
        // Node Data Getter
        string get() const {
            return pos->data;
        }
        // Iterate to Next Node
        void next() {
            pos = pos->next;
        }
        // Iterate to Prev Node
        void prev() {
            pos = pos->prev;
        }
        // Return True if This Iter Pos Equals Other Iter Pos
        bool equals(Iterator other) const {
            return pos == other.pos;
        }
};
// Linked List Utility Class
class List {
    private:
        // List Head Node
        Node* head;
        // List Friend
        friend class Iterator;
    public:
        // Default Constructor
        List() {
            // Empty Head
            head = nullptr;
        }
        // Append Data at End of List
        void push_back(string element) {
            // Store Data in New Node
            Node* newNode = new Node(element);
            // If List is Empty, Assign newNode to head
            if(!head) {
                head = newNode;
                return;
            }
            // Otherwise...
            // Curr Node to Head Prev
            Node* currNode = head->prev;
            // Head Prev to New Node
            head->prev = newNode;
            // New Node Next to Head
            newNode->next = head;
            // New Node Prev to Curr Node
            newNode->prev = currNode;
            // Curr Node Next to New Node
            currNode->next = newNode;
        }
        // Insert Data at Position in List
        void insert(Iterator iter, string element) {
            // If the Position is Head
            if(iter.pos == head) {
                // Push Back Element
                push_back(element);
                // Head to Head Prev
                head = head->prev;
                return;
            }
            // Otherwise...
            // Create New Node with Data
            Node* newNode = new Node(element);
            // Store Iter Pos Node in After
            Node* after = iter.pos;
            // Store After Prev in Before
            Node* before = after->prev;
            // New Node Prev and Next to Before and After
            newNode->prev = before;
            newNode->next = after;
            // After Prev and Before Next to New Node
            after->prev = newNode;
            before->next = newNode;
        }
        // Print List Content
        string print() {
            // Store Head Data in SS
            stringstream ss;
            Iterator iter = begin();
            ss << iter.get() << " ";
            // Increment Iter
            iter.next();
            // While Iter is Not Head
            while(!iter.equals(begin())) {
                // Store Iter Data in SS
                ss << iter.get() << " ";
                // Increment Iter
                iter.next();
            }
            // Return SS as String
            return ss.str();
        }
        // Remove Node at Position
        void erase(Iterator iter) {
            // Store Iter Pos and Increment Iter
            Node* remove = iter.pos;
            iter.next();
            // Set Before and After to Remove Prev and Next
            Node* before = remove->prev;
            Node* after = remove->next;
            // If Remove Node is Head, Set Head to After
            if(remove == head) {
                head = after;
            }
            // Set Before Next to After and After Prev to Before
            before->next = after;
            after->prev = before;
            // Delete Remove Node
            delete remove;
        }
        // Create an Iterator at Head
        Iterator begin() {
            Iterator iter;
            iter.pos = head;
            iter.container = this;
            return iter;
        }
};
// Driver Code
int main() {
    // Initialize List called Names
    List names;
    names.push_back("Tom"); // Push Tom to Names
    names.push_back("Diana"); // Push Diana to Names
    names.push_back("Harry"); // Push Harry to Names
    names.push_back("Juliet"); // Push Juliet to Names

    // Output Names
    cout << names.print() << endl;

    // Create Iterator at Names Begin
    Iterator iter = names.begin();
    iter.next(); // Next Node
    iter.next(); // Next Node
    iter.next(); // Next Node

    // Insert Romeo at Iter
    names.insert(iter, "Romeo");

    // Output Names
    cout << names.print() << endl;

    // Reset Iter to Names Begin
    iter = names.begin();
    iter.next(); //Next Node

    // Erase Names Node at Iter
    names.erase(iter);

    // Output Names
    cout << names.print() << endl;

    // Reset Iter to Names Begin
    iter = names.begin();
    iter.prev(); // Prev Node
    iter.prev(); // Prev Node

    // Insert Bob at Iter
    names.insert(iter, "Bob");

    // Output Names
    cout << names.print() << endl;

    return 0;
}
