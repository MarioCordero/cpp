#ifndef bstree_h
#define bstree_h

#include <iostream>

// Tree nodes:
template <typename T>
class bstnode {
    public:

        T value;
        bstnode<T> *parent, *leftChild, *rightChild;
        
        // Default constructor
        bstnode() : value(), parent(nullptr), leftChild(nullptr), rightChild(nullptr) {
        };
        
        // Member data initialization
        bstnode(const T& val, bstnode<T> *par = nullptr, bstnode<T> *left = nullptr, bstnode<T> *right = nullptr)
        : value(val), parent(par), leftChild(left), rightChild(right) {
        };
        
        // Destructor
        ~bstnode() {
            // Currently empty. No specific resource management needed.
        };

        // Overload of the insertion operator
        friend std::ostream& operator<<(std::ostream& os, const bstnode<T>& node) {
            os << node.value;
            return os;
        }
};



// Binary search tree:
template <typename T>
class bstree {
    public:
        bstnode<T>* root; // root of the tree
        bstnode<T>* lastInserted; // last inserted node

        // Default constructor
        bstree() : root(nullptr), lastInserted(nullptr) {
            
        };
    
        // Destructor
        ~bstree() {
            deleteSubTree(this->root);
        };
    
        // Insert a node into the tree
        void Insert(bstnode<T>* newNode) {
            if (newNode != nullptr) {
                bstnode<T>* current = this->root;
                bstnode<T>* parent = nullptr;

                while (current != nullptr) {
                    parent = current;
                    if (newNode->value < current->value) {
                        current = current->leftChild;
                    } else {
                        current = current->rightChild;
                    }
                }

                newNode->parent = parent;

                if (this->root == nullptr) {
                    this->root = newNode;
                } else if (newNode->value < parent->value) {
                    parent->leftChild = newNode;
                } else {
                    parent->rightChild = newNode;
                }
            }
        };

        // Insert a node into the tree with additional parameter (example overload)
        void Insert(bstnode<T>* newNode, int i) {
            if (newNode != nullptr) {
                bstnode<T>* current = this->lastInserted;

                if (this->root == nullptr) {
                    this->root = newNode;
                } else {
                    if (newNode->value > current->value) {
                        current->rightChild = newNode;
                        newNode->parent = current;
                    }
                }
                this->lastInserted = newNode;
            }
        };
    
        // In-order tree walk
        void InorderWalk(bstnode<T> *node) {
            if (node != nullptr) {
                // Traverse the left subtree
                InorderWalk(node->left);

                // Prints the actual node
                std::cout << node->value << std::endl;

                // Traverse the right subtree
                InorderWalk(node->right);
            }
        };
    
        // Search for a node with a specific key
        bstnode<T>* Search(bstnode<T> *node, const T& key) {
            if (node != nullptr) {
                if (key == node->value) {
                    return node;

                } else if (key > node->value) {
                    return Search(node->right, key);

                } else {
                    return Search(node->left, key);

                }
            }
            return nullptr;
        };
    
        // Iterative search for a node with a specific key
        bstnode<T>* IterativeSearch(bstnode<T> *node, const T& key) {
            bstnode<T>* current = node;
            bstnode<T>* result = nullptr;
        
            while(current != nullptr) {
                if (key == current->value) {
                    result = current;
                    return result;

                } else if (key > current->value) {
                    current = current->rightChild;

                } else {
                    current = current->leftChild;
                }
            }
            return nullptr;
        };
    
        // Find the node with the minimum key
        bstnode<T>* Minimum(bstnode<T>* node) {
            if (this->root != nullptr) {
                bstnode<T>* current = node;
                bstnode<T>* min = nullptr;

                while(current != nullptr) {
                    min = current;
                    current = current->left;
                }
                return min;
            }
            return nullptr;
        };
    
        // Find the node with the maximum key
        bstnode<T>* Maximum(bstnode<T>* node) {
            if (this->root != nullptr) {
                bstnode<T>* current = node;
                bstnode<T>* max = nullptr;

                while(current != nullptr) {
                    max = current;
                    current = current->right;
                }
                return max;
            }
            return nullptr;
            // Returns the node with the maximum key. If the tree is empty, returns nullptr.
        };
    
        // Find the successor of a given node
        bstnode<T>* Successor(bstnode<T>* node) {
            if (this->root != nullptr && node != nullptr) {
                if (node->right != nullptr) {
                    return Minimum(node->right);
                }
            }

            bstnode<T>* successor = node->p;
            bstnode<T>* current = nullptr;
            while (successor != nullptr && node == successor->right) {
                current = successor;
                successor = successor->p;
            }
            return successor;
        };
    
        // Delete a node from the tree
        void Delete(bstnode<T>* nodeToDelete) {
            if (nodeToDelete != nullptr) {
                if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) {
                    Transplant(nodeToDelete, nullptr);

                } else if (nodeToDelete->right == nullptr) {
                    // The node only has a left child
                    Transplant(nodeToDelete, nodeToDelete->left);

                } else if (nodeToDelete->left == nullptr) {
                    // The node only has a right child
                    Transplant(nodeToDelete, nodeToDelete->right);

                } else {
                    bstnode<T>* replacer = Minimum(nodeToDelete->right);
                    if (replacer->p != nodeToDelete) {
                        Transplant(replacer, replacer->right);
                        replacer->right = nodeToDelete->right;
                        replacer->right->p = replacer;
                    }

                    Transplant(nodeToDelete, replacer);
                    replacer->left = nodeToDelete->left;
                    replacer->left->p = replacer;
                }
            }
            delete nodeToDelete;
        };

    private:
        // Recursively delete the subtree rooted at a given node
        void deleteSubTree(bstnode<T>* node) {
            if (node != nullptr) {
                deleteSubTree(node->left);
                deleteSubTree(node->right);
                delete node;
            }
        }

        // Transplant a subtree by replacing one node with another
        void Transplant(bstnode<T>* toReplace, bstnode<T>* replacer) {
            if (toReplace->p == nullptr) {
                this->root = replacer;
            } else if (toReplace == toReplace->p->left) {
                toReplace->p->left = replacer;
            } else if (toReplace == toReplace->p->right) {
                toReplace->p->right = replacer;
            }

            if (replacer != nullptr) {
                replacer->p = toReplace->p;
            }
        }
};
#endif

