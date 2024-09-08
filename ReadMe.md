# Thread safe singly Linked List Implementation
##### Note: This implementation is used as helper class in my project- Thread safe LRU cache system, So only functions that are needed are implemented, and the structure also differs from normal implementation; But the ideas can be used to implement general thread safe linked list.


### LinkedList Structure
##### Node structure
each node has one value parameter, pointer to next node and a mutex for protection.

##### LinkedList structure
We keep a dummy head to make implementation easy. A new node is always inserted at the start of linkedlist

### General rules to be followed
When we want to remove a node, we have to take lock on previous node and current node in this order to avoid deadlock and maintain thread safety. Also since it is singly linked list, so movement is possible in one direction only; But in case of Doubly linked list also , we have to limit movement in one direction only to avoid deadlock.

Since, in cache system, keys are unique, so we assume that all values in linked list are unique and there are no duplicates.





### API

void add_front(value) -> add a new node at the start of linked list with given value.  It return nothing
This method first takes lock on dummy head and then add new node next to dummy head node.


bool erase(value) -> If node with given value exist, this method will remove first occurrence of this value and returns true. If no such node exists, then this will return false. For removing a node, we have to take lock on previous node and current node.


void erase_tail()  -> this method will remove last node from the linkedlist if it exists. This method returns nothing.

