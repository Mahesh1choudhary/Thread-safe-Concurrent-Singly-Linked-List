# Thread safe singly Linked List Implementation
##### Note: This implementation is used as helper class in my project- Thread safe LRU cache system, So only functions that are needed are implemented, and the structure also differs from normal implementation; But the ideas can be used to implement general thread safe linked list.

### Node structure
each node has one value parameter, pointer to next node and a mutex for protection.

### General rules to be followed
When we want to remove a node, we have to take lock on previous node, current node and next node in this order to avoid deadlock and maintain thread safety. Also since it is singly linked list, so movement is possible in one direction only; But in case of Doubly linked list also , we have to limit movement in one direction only to avoid deadlock.

Since, in cahce system, keys are unique, so we assume that all values in linked list are unique and there are no duplicates.