#ifndef llist_h
#define llist_h

// List nodes:
template <typename T>
class llnode {
    public:
        // This class is intended to be used by other classes. Attributes are left public for efficiency.
        T value;
        llnode<T> *previousNode, *nextNode;

        // Default constructor.
        llnode() : value(T()), previousNode(nullptr), nextNode(nullptr) {
            // Initializes member data with default values
        };

        // Member data initialization.
        llnode(const T& val, llnode<T> *prev = nullptr, llnode<T> *next = nullptr) : value(val), previousNode(prev), nextNode(next) {
            // Initializes member data with provided values
        };

        // Copy constructor with member data initialization.
        llnode(const llnode& other) : value(other.value), previousNode(other.previousNode), nextNode(other.nextNode) {
            // Initializes member data by copying from another node
        };

        // Move constructor.
        llnode(llnode&& other) noexcept : value(std::move(other.value)), previousNode(other.previousNode), nextNode(other.nextNode) {
            // Transfers ownership of resources from 'other' to this node
            other.nextNode = nullptr;
            other.previousNode = nullptr;
        }

        // Destructor
        ~llnode() {
            this->previousNode = nullptr;
            this->nextNode = nullptr;
        };

        // Overload of the equality operator.
        bool operator==(const llnode& other) const {
            return this->value == other.value;
        };

        // Overload of the move assignment operator.
        llnode& operator=(llnode&& other) noexcept {
            if (this != &other) {
                this->value = std::move(other.value);
                this->nextNode = other.nextNode;
                this->previousNode = other.previousNode;

                other.nextNode = nullptr;
                other.previousNode = nullptr;
            }
            return *this;
        }

        // Overload of the insertion operator.
        friend std::ostream& operator<<(std::ostream& os, const llnode<T>& node) {
            os << node.value;
            return os;
        }
};


// Linked list with a sentinel node:
template <typename T>
class llist {
    public:

        llnode<T> *nil;

        // Default constructor.
        llist() : nil(new llnode<T>(T())) {
            nil->nextNode = nil;
            nil->previousNode = nil;
        };
        
        // Destructor
        ~llist() {
            llnode<T>* current = nil->next;
            while(current != nil) {
                llnode<T>* temp = current;
                current = current->next;
                delete temp;
            }
            delete nil;
        };
        
        // Inserts a new node x into the list.
        void Insert(llnode<T>* x) {
            if (nil->nextNode == nil) {
                nil->nextNode = x;
                nil->previousNode = x;
                x->previousNode = nil;
                x->nextNode = nil;
            } else {
                x->previousNode = nil->previousNode;
                x->nextNode = nil;
                nil->previousNode->nextNode = x;
                nil->previousNode = x;
            }
        };

        // Searches for a node with the value k.
        llnode<T>* Search(const T& k) {
            llnode<T>* current = nil->nextNode;
            while(current != nil) {
                if (current->value == k) { // Changed `key` to `value` to match previous code
                    return current;
                }
                current = current->nextNode;
            }
            return nullptr;
        };
            
        // Deletes a node x from the list.
        void Delete(llnode<T>* x) {
            if (x != nil) {
                x->prev->next = x->next;
                x->next->prev = x->prev;
                delete x;
            }
        };    
};
#endif