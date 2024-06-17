#ifndef rbtree_h
#define rbtree_h

#include <iostream>

enum colors {RED, BLACK};

// Tree nodes
template <typename T>
class rbtnode{

    public:
        T key;
        rbtnode<T> *p, *left, *right;
        enum colors color;
        
        // Omision constructor
        rbtnode() {};
        
        // Constructor
        rbtnode (

                    const T& value, 
                    rbtnode<T> *parent = nullptr, // The parent node
                    rbtnode<T> *Lchild = nullptr, // Left child
                    rbtnode<T> *Rchild = nullptr, // Rigth child
                    enum colors c = RED

                ):key(value), p(parent), left(Lchild), right(Rchild), color(c) {};
        
        // Destructor
        ~rbtnode() {};
};

// Red-black tree:".
template <typename T>
class rbtree {
    public:
        rbtnode<T> *root;    // root of the tree
        rbtnode<T> *nil;     // nil node of the tree
    
        // Constructor
        rbtree() {
            nil = new rbtnode<T>();
            nil->color = BLACK;
            root = nil;
        };
    
        // Destructor
        ~rbtree() {
            // If the tree isn't empty 
            if (root != nil) {
                DeleteTree(root);
            }
            delete nil;
        };
    
        // Recursive auxiliar function that helps delete the tree
        void DeleteTree(rbtnode<T> *x) {
            // In order recursive traversal
            if (x != nil) {
                DeleteTree(x->left);
                DeleteTree(x->right);
                delete x;
            }
        }

        void Insert(rbtnode<T>* newInsertion) {
            // Initialize y to nil, which will be used to keep track of the parent of the new node
            rbtnode<T> *tempParent = nil;
            // Start at the root of the tree
            rbtnode<T> *x = root;
            
            // Traverse the tree to find the correct insertion point for the new node
            while (x != nil) {
                // Update tempParent to the current node
                tempParent = x;
                
                if (newInsertion->key < x->key) {
                    // Move to the left child if the new key is smaller
                    x = x->left;
                } else {
                    // Move to the right child if the new key is bigger
                    x = x->right;
                }
            }
            
            // Set the parent of the new node to newInsertion
            newInsertion->p = tempParent;

            if (tempParent == nil) {
                // If the tree was empty
                root = newInsertion;
            } else if (newInsertion->key < tempParent->key) {
                // Insert the new node as the left child
                tempParent->left = newInsertion;
            } else {
                // Insert the new node as the right child
                tempParent->right = newInsertion;
            }
            // Initialize the left child of the new node to nil
            newInsertion->left = nil;

            // Initialize the right child of the new node to nil
            newInsertion->right = nil;

            // Set the color of the new node to RED
            newInsertion->color = RED;

            // Fix up the tree to maintain red-black properties
            InsertFixup(newInsertion);
        }


        void InsertFixup(rbtnode<T>* newInsertion) {

            // Loop to fix up the tree until the red-black properties are restored
            while (newInsertion->p->color == RED) {

                if (newInsertion->p == newInsertion->p->p->left) {
                    // If newInsertion's parent is the left child of it's grandparent
                    
                    /*       G (Grandparent)    */
                    /*      / \                 */
                    /*    P    U (Uncle)        */
                    /*   /                      */
                    /*  N (newInsertion)        */

                    rbtnode<T>* uncle = newInsertion->p->p->right; // y is z's uncle

                    if (uncle->color == RED) { // Case 1: newInsertion's uncle is red

                        // Recolor newInsertion's parent to black
                        newInsertion->p->color = BLACK;
                        // Recolor newInsertion's uncle to black
                        uncle->color = BLACK;
                        // Recolor newInsertion's grandparent to red
                        newInsertion->p->p->color = RED;
                        // Move newInsertion to it's grandparent, now "newInsertion" it's it's grandfather and start again to check if everithing it's ok
                        newInsertion = newInsertion->p->p;

                    } else {
                        
                        // If newInsertion's uncle is black
                        if (newInsertion == newInsertion->p->right) { // Case 2: newInsertion is a right child
                                /* 
                                     G (Negro)
                                    /
                                   P (Rojo)
                                    \
                                     N (Rojo)
                                */

                            newInsertion = newInsertion->p; // Move newInsertion to it's parent

                            LeftRotate(newInsertion); // Perform a left rotation on z's parent

                            /* 
                                     G (Negro)
                                    /
                                   N (Rojo)
                                 /
                                P (Rojo)

                            */
                        }

                        // Case 3: z is a left child
                        
                        // Recolor newInsertion's parent to black
                        newInsertion->p->color = BLACK;
                        // Recolor newInsertion's grandparent to red
                        newInsertion->p->p->color = RED;
                        // Perform a right rotation on newInsertion's grandparent
                        RightRotate(newInsertion->p->p);
                    }

                } else {
                    // Symmetric case: newInsertion's parent is the right child of its grandparent

                    // This part mirrors the first case with "left" and "right" exchanged
                    rbtnode<T>* uncle = newInsertion->p->p->left;

                    // Case 1: newInsertion's uncle is red
                    if (uncle->color == RED) {

                        // Recolor newInsertion's parent to black
                        newInsertion->p->color = BLACK;
                        // Recolor newInsertion's uncle to black
                        uncle->color = BLACK;
                        // Recolor newInsertion's grandparent to red
                        newInsertion->p->p->color = RED; 
                        // Move newInsertion to its grandparent
                        newInsertion = newInsertion->p->p; 

                    } else {

                        // If newInsertion's uncle is black
                        
                        // Case 2: newInsertion is a left child
                        if (newInsertion == newInsertion->p->left) {
                            // Move newInsertion to its parent
                            newInsertion = newInsertion->p;
                            // Perform a right rotation on newInsertion's parent
                            RightRotate(newInsertion);
                        }

                        // Case 3: z is a right child

                        // Recolor z's parent to black
                        newInsertion->p->color = BLACK; 
                        // Recolor z's grandparent to red
                        newInsertion->p->p->color = RED;
                        // Perform a left rotation on z's grandparent 
                        LeftRotate(newInsertion->p->p); 
                    }
                }
            }
            // Ensure the root is always black
            root->color = BLACK;
        }

        // Perform a left rotation on the given node x
        void LeftRotate(rbtnode<T>* x) {
            // Set y to be the right child of x
            rbtnode<T>* y = x->right;
            // Update x's right child to be y's left child
            x->right = y->left;
            // Update y's left child's parent to be x
            if (y->left != nil) {
                y->left->p = x;
            }
            // Update y's parent to be x's parent
            y->p = x->p;
            // Update x's parent's child pointer to y
            if (x->p == nil) {
                root = y; // If x is the root, update the root to be y
            } else if (x == x->p->left) {
                x->p->left = y; // If x is a left child, update x's parent's left child to be y
            } else {
                x->p->right = y; // If x is a right child, update x's parent's right child to be y
            }
            // Set y's left child to be x
            y->left = x;
            // Set x's parent to be y
            x->p = y;
        }


        // Perform a right rotation on the given node y
        void RightRotate(rbtnode<T>* y) {
            // Set x to be the left child of y
            rbtnode<T>* x = y->left;
            // Update y's left child to be x's right child
            y->left = x->right;
            // Update x's right child's parent to be y
            if (x->right != nil) {
                x->right->p = y;
            }
            // Update x's parent to be y's parent
            x->p = y->p;
            // Update y's parent's child pointer to x
            if (y->p == nil) {
                root = x; // If y is the root, update the root to be x
            } else if (y == y->p->right) {
                y->p->right = x; // If y is a right child, update y's parent's right child to be x
            } else {
                y->p->left = x; // If y is a left child, update y's parent's left child to be x
            }
            // Set x's right child to be y
            x->right = y;
            // Set y's parent to be x
            y->p = x;
        }

    
        // Perform an inorder walk (left-root-right traversal) starting from the given node x
        void InorderWalk(rbtnode<T> *x) {
            // If the node is not nil
            if (x != nil) {
                // Recursively traverse the left subtree
                InorderWalk(x->left);
                // Print the key of the current node
                std::cout << x->key << std::endl;
                // Recursively traverse the right subtree
                InorderWalk(x->right);
            }
        }


        // Search for a node with key k starting from the given node x
        // If the node with key k is found, return a pointer to that node; otherwise, return nil
        rbtnode<T>* Search(rbtnode<T> *x, const T& k) {
            // Traverse the tree until reaching a nil node or finding the node with key k
            while (x != nil && k != x->key) {
                // If k is less than the key of the current node, move to the left subtree
                if (k < x->key) {
                    x = x->left;
                } else { // Otherwise, move to the right subtree
                    x = x->right;
                }
            }
            // Return the pointer to the node (which may be nil if the key was not found)
            return x;
        }


        // Iteratively search for a node with key k starting from the given node x
        // If the node with key k is found, return a pointer to that node; otherwise, return nil
        rbtnode<T>* IterativeSearch(rbtnode<T>* x, const T& k) {
            // Iterate until reaching a nil node or finding the node with key k
            while (x != nil && k != x->key) {
                // If k is less than the key of the current node, move to the left subtree
                if (k < x->key) {
                    x = x->left;
                } else { // Otherwise, move to the right subtree
                    x = x->right;
                }
            }
            // Return the pointer to the node (which may be nil if the key was not found)
            return x;
        }

        // Find and return the node with the minimum key value in the subtree rooted at x
        rbtnode<T>* Minimum(rbtnode<T>* x) {
            // Traverse the left subtree until reaching the leftmost node
            while (x->left != nil) {
                x = x->left;
            }
            // Return the leftmost node (which will have the minimum key value)
            return x;
        }

        // Find and return the node with the maximum key value in the subtree rooted at x
        rbtnode<T>* Maximum(rbtnode<T>* x) {
            // Traverse the right subtree until reaching the rightmost node
            while (x->right != nil) {
                x = x->right;
            }
            // Return the rightmost node (which will have the maximum key value)
            return x;
        }

        // Find and return the successor of the node x in the tree
        // The successor is the node with the smallest key greater than x's key
        rbtnode<T>* Successor(rbtnode<T>* x) {
            // If x has a right subtree, the successor is the minimum node in that subtree
            if (x->right != nil) {
                return Minimum(x->right);
            }
            // Otherwise, the successor is the lowest ancestor of x whose left child is also an ancestor of x
            rbtnode<T>* y = x->p; // Set y to be x's parent
            while (y != nil && x == y->right) { // Traverse up the tree until x is not a right child
                x = y;
                y = y->p;
            }
            // Return the lowest ancestor (which will be the successor)
            return y;
        }

};
#endif