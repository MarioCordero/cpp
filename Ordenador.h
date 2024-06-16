#ifndef Ordenador_h
#define Ordenador_h
//To use size_t
#include <stddef.h>
#include <random>

class Ordenador{
	private:
		// Defina aquí los métodos auxiliares de los algoritmos de ordenamiento solamente.
		// Puede definir cuantos métodos quiera.

		//-----------------------------------------METHODS OF MERGESORT-------------------------------------------//
		void merge(int *arr, int left, int mid, int right);

		void mergesort_aux(int *A, int first, int last, int n) { //Aux method for mergesort

			// Divide. "p" is the first element, "n"

			if (first < last) {
				int middle = first + (last - first) / 2;

				//The subarray divided
				mergesort_aux(A, first, middle, n);

				// The other part of the subarray
				mergesort_aux(A, middle + 1, last, n);

				// Join the both sorted subarrays
				merge(A, first, middle, last);
			}

		}

		//------------------------------------------METHODS OF HEAPSORT-------------------------------------------//
		// A trivial Swap Method
		void swap(int& a, int& b) {
			int tmp = a;
			a = b;
			b = tmp;
		}

		void heapify(int* A, int n, int parent) {

			// Initialize with the parent position
			int localRoot = parent;

			// The left son using the formula
			int Lson = parent * 2;
			int Rson = (parent * 2) + 1;

			// Check if we can Heapify for the left side
			if (Lson < n && A[Lson] > A[localRoot]) {
				localRoot = Lson;
			}

			// Check if we can Heapify for the rigth side
			if (Rson < n && A[Rson] > A[localRoot]) {
				localRoot = Rson;
			}


			// If the value of the parent node is not the largest, it is swapped with the child that has the largest value
			if (localRoot != parent) {
				swap(A[parent], A[localRoot]);
				// Recursively call heapify on the modified child
				heapify(A, n, localRoot);
			}

		}

		//------------------------------------------METHODS OF QUICKSORT------------------------------------------//
		int partition(int* A, int start, int end) {
			// Select the pivot element, which is the last element of the array or subarray
			int pivot = A[end];

    		// Initialize pointers, i and j
			int i = start;
			int j = end - 1;

			// Loop until i is less than j
			while (i < j) {
				// Move i to the right until it finds an element greater than the pivot
				while (i < j && A[i] <= pivot) {
					i++;
				}
				// Move j to the left until it finds an element smaller than the pivot
				while (i < j && A[j] >= pivot) {
					j--;
				}
				// Swap the elements at positions i and j if i is still less than j
				if (i < j) {
					swap(A[i], A[j]);
				}
			}

			// Move the pivot element to its correct position in the partitioned array
			if (A[i] > pivot) {
				swap(A[i], A[end]);
				// Return the index of the pivot element
				return i;
			} else {
				swap(A[i + 1], A[end]);
				// Return the index of the pivot element
				return i + 1;
			}

		}
		
		//------------------------------------------METHODS OF RADIXSORT------------------------------------------//
		// A struct used in the RadixSort
		struct arrayRadixProperties{
			int max = 0;
			int min = 0;
			int size = 0;
			int negatives = 0;
			int positives = 0;
		};

		// A trivial getMax method
		int getMax(const int* A, int n) {
			int max = INT32_MIN;
			for(int i = 0; i < n; i++) {
			if (A[i] > max) {
				max = A[i];
			}
			}
			return max;
		}

		int* getNegativeArray(const int* A, arrayRadixProperties& arrayProperties) {
			// Count the number of negative elements in the array
			for (int i = 0; i < arrayProperties.size; i++) {
				if (A[i] < 0) {
					arrayProperties.negatives++;
				}
			}

			// Create an array to store negative elements
			int* negativesArray = new int[arrayProperties.negatives];
			int index = 0;

			// Populate the negativesArray with negative elements from the original array
			for (int i = 0; i < arrayProperties.size; i++) {
				if (A[i] < 0) {
					negativesArray[index] = -A[i]; // Store the absolute value of the negative element
					index++;
				}
			}

			return negativesArray; // Return the array containing negative elements
		}

		int* getPositiveArray(const int* A, arrayRadixProperties& arrayProperties) {
			// Count the number of positive elements in the array
			for (int i = 0; i < arrayProperties.size; i++) {
				if (A[i] >= 0) {
					arrayProperties.positives++;
				}
			}

			// Create an array to store positive elements
			int* positives = new int[arrayProperties.positives];
			int index = 0;

			// Populate the positives array with positive elements from the original array
			for (int i = 0; i < arrayProperties.size; i++) {
				if (A[i] >= 0) {
					positives[index] = A[i];
					index++;
				}
			}

			return positives; // Return the array containing positive elements
		}

		void binaryRadixHandler(int* A, int n, int bitPos) {
			// Calculate the number of bits to process at a time
			const int BITS_PER_GROUP = static_cast<int>(log2(n)); // Number of bits to process at once
			const int GROUP_MASK = (1 << BITS_PER_GROUP) - 1; // Mask to extract bits from the group

			// Array to count the frequency of each combination of bits
			int count[1 << BITS_PER_GROUP] = {0};

			// Counting the frequency of each combination of bits at the specified position
			for (int i = 0; i < n; i++) {
				int group = (A[i] >> bitPos) & GROUP_MASK;
				count[group]++;
			}

			// Calculate cumulative count to determine positions of elements in the output array
			for (int i = 1; i < (1 << BITS_PER_GROUP); i++) {
				count[i] += count[i - 1];
			}

			// Array to store the sorted elements
			int* results = new int[n];

			// Building the output array
			for (int i = n - 1; i >= 0; i--) {
				int group = (A[i] >> bitPos) & GROUP_MASK;
				results[count[group] - 1] = A[i];
				count[group]--;
			}

			// Copying the output array back to the original array
			for (int i = 0; i < n; i++) {
				A[i] = results[i];
			}

			// Freeing memory used for the temporary array
			delete[] results;
		}

	public:
		Ordenador(){};
		~Ordenador(){};
		// Si no implementa algunos de los métodos de ordenamiento no lo borre;
		// déjelo con el cuerpo vacío para evitar errores de compilación, ya
		// que se va a ejecutar el mismo «main» para todas las tareas.
		// Implemente los algoritmos en este archivo, no en un CPP.
		void seleccion(int *A, int n);
		void insercion(int *A, int n);
		void mergesort(int *A, int n);
		void heapsort(int *A, int n);
		void quicksort(int *A, int start, int end);
		void radixsort(int *A, int n);
};


// ------------------------------------------------------------------------------------------------------ //
// --------------------------------------------Implement------------------------------------------------- //
// ------------------------------------------------------------------------------------------------------ //

//----------------------------------------------SELECTION SORT--------------------------------------------//
void Ordenador::seleccion(int *A, int n) {
	for (int i = 0; i < n - 1; ++i) {\

        // Find the index of the min element in the subarray
        int MinIndex = i;

        for (int j = i + 1; j < n; ++j) {
            if (A[j] < A[MinIndex]) {
                MinIndex = j;
            }
        }
        
        // Exchange the min element founded with the first element of the subarray
        if (MinIndex != i) {
            int temp = A[i];
            A[i] = A[MinIndex];
            A[MinIndex] = temp;
        }
    }
}

//----------------------------------------------INSERTION SORT--------------------------------------------//
void Ordenador::insercion(int *A, int n) { //Insertion sort
    
	for(size_t i = 1; i < n; i++){

		int key = A[i];
		int j = i -1;

		while((j>=0) && (A[j]>key)){
			A[j+1] = A[j];
			j = j-1;
		}

		A[j+1] = key;
	}

}

//-----------------------------------------------MERGESORT------------------------------------------------//
void Ordenador::mergesort(int *A, int n) { //Merge sort
    
	mergesort_aux(A, 0, n-1, n);

}

void Ordenador::merge(int *arr, int first, int mid, int last){

	// Divide the array
	int nleft = mid - first + 1;
	int nright = last - mid;

	// New arrays, left and right
	int L [nleft];
	int R [nright];

	// Copy to the new arrays
	for(size_t i = 0; i < nleft; i++){//The left array
		//The first element + iterator
		L[i] = arr[ first + i ];
	}
	
	for(size_t i = 0; i < nright; i++){//The right part
		//The middle + iterator + 1
		R[i] = arr[ mid + 1 + i ];
	}

	int i = 0;
	int j = 0;
	int k = first;

	// As long as each of the arrays L and R contains an unmerged element,
	// copy the smallest unmerged element back into arr[ first:last ]

	while((i<nleft) && (j<nright)){

		if(L[i] <= R[j]){

			arr[k] = L[i];
			i++;

		}else{

			arr[k] = R[j];
			j++;

		}
		k++;
	}

	// Having gone through one of L and R entirely, copy the
	// remainder of the other to the end of arr[ first:last ]
	while(i<nleft){
		arr[k] = L[i];
		i++;
		k++;
	}

	while(j<nright){
		arr[k] = R[j];
		j++;
		k++;
	}
	
}

//----------------------------------------------HEAPSORT--------------------------------------------------//
void Ordenador::heapsort(int *A, int n) {

    for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(A, n, i);
    }

	for (int i = n - 1; i > 0; i--) {
		swap(A[0], A[i]);
		heapify(A, i, 0);
    }

}


//----------------------------------------------QUICKSORT-------------------------------------------------//
void Ordenador::quicksort(int *A, int start, int end) {
    if (start < end) {
		int key = partition(A, start, end);
		quicksort(A, start, key - 1);
		quicksort(A,key + 1, end);
    }
}


//----------------------------------------------RADIXSORT-------------------------------------------------//
void Ordenador::radixsort(int *A, int n) {
    // Structure to store properties of the array
	arrayRadixProperties arrayProperties;
    arrayProperties.max = getMax(A, n); // Get the maximum element in the array
    arrayProperties.size = n; // Set the size of the array

    // Separate the array into negative and positive parts
    int* negatives = getNegativeArray(A, arrayProperties);
    int* positives = getPositiveArray(A, arrayProperties);

    // Perform radix sort on negative values
    int maxNegative = getMax(negatives, arrayProperties.negatives); // Get the maximum negative value
    for (int i = 0; (maxNegative >> i) > 0; i++) {
        binaryRadixHandler(negatives, arrayProperties.negatives, i); // Sort negatives using binary radix sort
    }

    // Perform radix sort on positive values
    int maxPositive = getMax(positives, arrayProperties.positives); // Get the maximum positive value
    for (int i = 0; (maxPositive >> i) > 0; i++) {
        binaryRadixHandler(positives, arrayProperties.positives, i); // Sort positives using binary radix sort
    }

    // Merge sorted negative and positive values back into the original array
    int j = arrayProperties.negatives - 1;
    for (int i = 0; i < arrayProperties.negatives; i++) {
        A[i] = -negatives[j]; // Restore negatives with their original sign
        j--;
    }

    int k = 0;
    for (int i = arrayProperties.negatives; i < arrayProperties.size; i++) {
        A[i] = positives[k]; // Copy sorted positive values
        k++;
    }

    // Free memory allocated for separate arrays
    delete[] negatives;
    delete[] positives;
}

#endif
