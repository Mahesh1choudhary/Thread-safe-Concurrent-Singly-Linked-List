#include <mutex>


// simple structure to represent node in the list
template<typename Value> struct Node{
    explicit Node(Value value_):value(value_){
    }

    ~Node(){
        next=nullptr;
    }

    const Value &getValue() const
    {
        return value;
    }

    private:
        Value value;
        Node *next= nullptr;
        mutable shared_mutex mutex_;    // we choose shared_mutex to allow multiple reads to the same node
};


template<typename Value> class ThreadSafeSinglyLinkedList{
    public:
        ThreadSafeSinglyLinkedList(): head(nullptr),tail(nullptr){

        }
        ~ThreadSafeSinglyLinkedList(){
            Node* curr=nullptr;
            while(head!=nullptr){
                curr=head;
                head=head->next;
                delete curr;
            }
            head=nullptr;
        }

        // deleting copy and move constructors to maintain thread safety
        ThreadSafeSinglyLinkedList(const ThreadSafeSinglyLinkedList&)= delete;
        ThreadSafeSinglyLinkedList(ThreadSafeSinglyLinkedList&&)=delete;
        ThreadSafeSinglyLinkedList& operator=(const ThreadSafeSinglyLinkedList&)=delete;
        ThreadSafeSinglyLinkedList& operator=(ThreadSafeSinglyLinkedList&&)=delete;

        // function to insert node at the end of linkedlist
        void push_back(Value value){
            std::unique_lock<shared_mutex> lock(tail->mutex_);
            if(tail==nullptr){
                tail= new Node(value);
            }
            else{
                Node* curr= new Node(value);
                next->next=curr;
            }
        }

        // function to erase given value from linkedlist if found
        void erase(Value value){
            std::unique_lock<shared_mutex> lock_curr(head->mutex_);
            Node* prev=nullptr, curr=nullptr, nxt=nullptr;
            curr= head;
            while(curr!=nullptr && curr->value){
                

            }

            // value is not present in linked list
            if(curr==nullptr){
                return;
            }

        }



    private:
        Node* head;
        Node* tail;
        
};