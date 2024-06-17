## Archivos de encabezado

### Ordenador.h

Este archivo de encabezado (`Ordenador.h`) define una clase `Ordenador` que implementa varios algoritmos de ordenamiento en C++. Está diseñado para ordenar números enteros, puede adaptarse para ser usado en proyectos que requieran ordenamiento de arreglos utilizando diferentes métodos. A continuación se detallan los métodos y su uso.

La clase `Ordenador` contiene implementaciones de los siguientes algoritmos de ordenamiento:
- Selección
- Inserción
- Mergesort
- Heapsort
- Quicksort
- Radixsort

### rbtree.h

El archivo `rbtree.h` define una estructura de datos conocida como Árbol Rojo-Negro (Red-Black Tree). Esta estructura es un tipo de árbol binario balanceado que garantiza operaciones eficientes de inserción, eliminación y búsqueda. A continuación se detallan las clases y métodos principales:

- **Clases principales**:
  - `rbtnode<T>`: Define los nodos del árbol, incluyendo la clave, los punteros a los hijos y al padre, y el color del nodo (rojo o negro).
  - `rbtree<T>`: Define el árbol rojo-negro en sí, incluyendo métodos para insertar, eliminar, buscar y recorrer el árbol.

- **Métodos principales**:
  - **Insertar**: Inserta un nuevo nodo en el árbol y realiza las operaciones necesarias para mantener las propiedades del árbol rojo-negro.
  - **InsertFixup**: Ajusta el árbol después de una inserción para asegurar que se mantengan las propiedades del árbol rojo-negro.
  - **Eliminar**: Elimina un nodo del árbol y realiza las operaciones necesarias para mantener las propiedades del árbol rojo-negro.
  - **Buscar**: Busca un nodo con una clave específica en el árbol.
  - **Rotaciones**: Métodos `LeftRotate` y `RightRotate` para realizar rotaciones izquierda y derecha en el árbol.

### llist.h

El archivo `llist.h` define una estructura de datos conocida como Lista Enlazada (Linked List) con un nodo centinela. Esta estructura permite la inserción, eliminación y búsqueda de elementos en una lista enlazada doblemente. A continuación se detallan las clases y métodos principales:

- **Clases principales**:
  - `llnode<T>`: Define los nodos de la lista, incluyendo el valor y los punteros al nodo anterior y siguiente.
  - `llist<T>`: Define la lista enlazada en sí, incluyendo métodos para insertar, eliminar y buscar elementos.

- **Métodos principales**:
  - **Insertar**: Inserta un nuevo nodo en la lista.
  - **Eliminar**: Elimina un nodo de la lista.
  - **Buscar**: Busca un nodo con un valor específico en la lista.

### chtable.h

El archivo `chtable.h` define una estructura de datos conocida como tabla hash con encadenamiento (Chained Hash Table). Esta estructura permite la inserción y búsqueda eficiente de elementos mediante el uso de listas enlazadas para manejar colisiones. A continuación se detallan las clases y métodos principales:

- **Clases principales**:
  - `chtable<T>`: Define la tabla hash, incluyendo métodos para insertar y buscar elementos, así como una función de hash simple.

- **Métodos principales**:
  - **Constructor**: Inicializa la tabla hash con un tamaño especificado.
    ```cpp
    chtable(int sz);
    ```
    Ejemplo de uso:
    ```cpp
    chtable<int> myTable(10);
    ```

  - **Destructor**: Limpia la tabla hash.
    ```cpp
    ~chtable();
    ```

  - **Insertar**: Inserta el elemento dado en la tabla hash.
    ```cpp
    void Insert(const T& k);
    ```
    Ejemplo de uso:
    ```cpp
    myTable.Insert(15);
    ```

  - **Buscar**: Busca un elemento en la tabla hash.
    ```cpp
    T* Search(const T& k);
    ```
    Ejemplo de uso:
    ```cpp
    int* found = myTable.Search(15);
    if (found != nullptr) {
        std::cout << "Elemento encontrado: " << *found << std::endl;
    } else {
        std::cout << "Elemento no encontrado." << std::endl;
    }
    ```

- **Atributos principales**:
  - `size`: Entero que almacena el tamaño de la tabla hash.
  - `table`: Vector de listas que representa la tabla hash. Cada entrada en el vector es una lista que almacena elementos que tienen el mismo índice de hash.

- **Función de Hash**:
  - `HashFunction`: Calcula el índice de hash para una clave dada.
    ```cpp
    int HashFunction(const T& k);
    ```

### bstree.h

El archivo `bstree.h` define una estructura de datos conocida como Árbol Binario de Búsqueda (Binary Search Tree). Esta estructura permite la inserción, eliminación y búsqueda de elementos de manera eficiente. A continuación se detallan las clases y métodos principales:

- **Clases principales**:
  - `bstnode<T>`: Define los nodos del árbol, incluyendo el valor y los punteros al padre, al hijo izquierdo y al hijo derecho.
  - `bstree<T>`: Define el árbol binario de búsqueda en sí, incluyendo métodos para insertar, eliminar, buscar y recorrer el árbol.

- **Métodos principales**:
  - **Insertar**: Inserta un nuevo nodo en el árbol.
    ```cpp
    void Insert(bstnode<T>* newNode);
    ```
    Ejemplo de uso:
    ```cpp
    bstree<int> tree;
    bstnode<int>* node = new bstnode<int>(10);
    tree.Insert(node);
    ```

  - **Buscar**: Busca un nodo con una clave específica en el árbol.
    ```cpp
    bstnode<T>* Search(bstnode<T>* node, const T& key);
    ```
    Ejemplo de uso:
    ```cpp
    bstnode<int>* foundNode = tree.Search(tree.root, 10);
    if (foundNode != nullptr) {
        std::cout << "Nodo encontrado: " << foundNode->value << std::endl;
    } else {
        std::cout << "Nodo no encontrado." << std::endl;
    }
    ```

  - **Eliminar**: Elimina un nodo del árbol.
    ```cpp
    void Delete(bstnode<T>* nodeToDelete);
    ```
    Ejemplo de uso:
    ```cpp
    tree.Delete(node);
    ```

  - **Mínimo**: Encuentra el nodo con la clave mínima.
    ```cpp
    bstnode<T>* Minimum(bstnode<T>* node);
    ```

  - **Máximo**: Encuentra el nodo con la clave máxima.
    ```cpp
    bstnode<T>* Maximum(bstnode<T>* node);
    ```

  - **Sucesor**: Encuentra el sucesor de un nodo dado.
    ```cpp
    bstnode<T>* Successor(bstnode<T>* node);
    ```

  - **Recorrido en orden**: Recorre el árbol en orden.
    ```cpp
    void InorderWalk(bstnode<T>* node);
    ```

- **Atributos principales**:
  - `root`: Puntero al nodo raíz del árbol.
  - `lastInserted`: Puntero al último nodo insertado en el árbol.

- **Métodos privados**:
  - `deleteSubTree`: Elimina de manera recursiva el subárbol enraizado en un nodo dado.
  - `Transplant`: Transplanta un subárbol reemplazando un nodo con otro.