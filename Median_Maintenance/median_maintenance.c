#include <stdio.h>
#include <stdlib.h>

// Architecture: 0 for Max-Heap (lower half), 1 for Min-Heap (upper half)
typedef struct Heap {
    int* data;
    int capacity;
    int size;
    int type;
} Heap;

Heap* create_heap(int capacity, int type) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->type = type;
    heap->data = (int*)malloc(capacity * sizeof(int));
    return heap;
}

// Moves the element down to restore heap priority O(log N)
void heapify_down(Heap* heap, int position) {
    int left = (2 * position) + 1;
    int right = (2 * position) + 2;
    int target = position; 

    if (heap->type == 0) { 
        if (left < heap->size && heap->data[left] > heap->data[target]) target = left;
        if (right < heap->size && heap->data[right] > heap->data[target]) target = right;
    } else { 
        if (left < heap->size && heap->data[left] < heap->data[target]) target = left;
        if (right < heap->size && heap->data[right] < heap->data[target]) target = right;
    }
    
    if (target != position) {
        int temp = heap->data[position];
        heap->data[position] = heap->data[target];
        heap->data[target] = temp;
        heapify_down(heap, target);
    }
}

// Moves the newly inserted element up O(log N)
void heapify_up(Heap* heap, int position) {
    if (position == 0) return; 
    
    int parent = (position - 1) / 2;
    int should_swap = 0;

    if (heap->type == 0 && heap->data[position] > heap->data[parent]) should_swap = 1;
    if (heap->type == 1 && heap->data[position] < heap->data[parent]) should_swap = 1;

    if (should_swap) {
        int temp = heap->data[position];
        heap->data[position] = heap->data[parent];
        heap->data[parent] = temp;
        heapify_up(heap, parent);
    }
}

// Insertion O(log N)
void insert_heap(Heap* heap, int value) {
    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
}

// Extraction and maintenance O(log N)
int extract_top(Heap* heap) {
    int top = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    
    if (heap->size > 0) {
        heapify_down(heap, 0);
    }
    return top;
}

int main() {
    int capacity = 10000;
    
    Heap* max_heap = create_heap(capacity, 0);
    Heap* min_heap = create_heap(capacity, 1);
    
    int value;
    int sum = 0;
    
    // Data stream input
    freopen("Median.txt", "r", stdin);
    
    for (int i = 0; i < capacity; i++) {
        if (scanf("%d", &value) != 1) break;
        
        // 1. Basic insertion (smaller in Max-Heap, larger in Min-Heap)
        if (max_heap->size == 0 || value < max_heap->data[0]) {
            insert_heap(max_heap, value);
        } else {
            insert_heap(min_heap, value);
        }
        
        // 2. Rebalancing (size difference cannot exceed 1)
        if (max_heap->size > min_heap->size + 1) {
            insert_heap(min_heap, extract_top(max_heap));
        } else if (min_heap->size > max_heap->size + 1) {
            insert_heap(max_heap, extract_top(min_heap));
        }
        
        // 3. Capturing current Median
        int current_median;
        if (max_heap->size >= min_heap->size) {
            current_median = max_heap->data[0];
        } else {
            current_median = min_heap->data[0];
        }
        
        // Accumulate last 4 digits to avoid integer overflow
        sum = (sum + current_median) % 10000;
    }
    
    printf("Sum of Medians (mod 10000): %d\n", sum);

    // Memory cleanup
    free(max_heap->data);
    free(max_heap);
    free(min_heap->data);
    free(min_heap);
    
    return 0;
}
