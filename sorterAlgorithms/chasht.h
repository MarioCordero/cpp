#ifndef chtable_h
#define chtable_h

#include <list>
#include <vector>

template <typename T>
class chtable {
    public:
        // Constructor: Initializes the hash table with the specified size. It allocates memory for the table
        // and sets its size to the given value. Each entry in the table is initialized as an empty list.
        chtable(int sz) {
            // Set the size of the hash table
            size = sz;              
            // Resize the table vector to accommodate 'size' elements
            table.resize(size);     
        };

        // Destructor: Cleans up the hash table. As this implementation does not involve dynamic memory
        // allocation or resource management, the destructor does not perform any specific cleanup actions.
        ~chtable() {};

        
        // This function inserts the given element into the hash table. It starts by calculating the hash index
        // for the provided key. Then, it adds the key to the list at that position in the table.
        void Insert(const T& k) {
            // Calculate the hash index for the key
            int index = HashFunction(k);
            // Add the key to the list at the calculated index
            table[index].push_back(k); 
        };
        
        // This function searches for an element in the hash table. It starts by calculating the hash index
        // corresponding to the provided key. Then, it iterates over the list at that position in the table
        // and compares each element with the searched key. If it finds the key, it returns a pointer to it.
        // Otherwise, it returns nullptr, indicating that the key was not found in the table.
        T* Search(const T& k) {
            // Calculate the hash index for the key
            int index = HashFunction(k);
            // Iterate over the list at the hash index position
            for (const auto& elem : table[index]) {
                // If the current element is equal to the searched key
                if (elem == k) {
                    // Return a pointer to the found key
                    return &const_cast<T&>(elem);
                }
            }
            // If the key is not found in the table, return nullptr
            return nullptr;
        };
    
    private:
        int size;
        std::vector<std::list<T>> table;

        // Simple hash function
        int HashFunction(const T& k) {
            // This hash function is assumed to be for illustrative purposes only
            // Returns the remainder of k divided by the size of the table
            return k % size;
        }

};

#endif