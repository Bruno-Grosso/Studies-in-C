#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPACITY 2000003
#define EMPTY -99999999LL

typedef struct Hash {
    long long* buckets;
    int a;
    int b;
    int p;
} Hash;

Hash* create_hash() {
    Hash* table = (Hash*)malloc(sizeof(Hash));
    table->buckets = (long long*)malloc(CAPACITY * sizeof(long long));
    
    for (int i = 0; i < CAPACITY; i++) {
        table->buckets[i] = EMPTY;
    }
    
    // Universal hashing random coefficients and a large prime number
    table->a = rand();
    table->b = rand();
    table->p = 10485767;
    
    return table;
}

long long hash_function(Hash* table, long long key) {
    int a = table->a, b = table->b, p = table->p;
    
    // Universal hashing formula
    long long index = ((a * (llabs(key) % p) + b) % p) % CAPACITY;
    
    return index;
}

Hash* insert_hash(Hash* table, long long key) {
    long long index = hash_function(table, key);
    
    if (table->buckets[index] == EMPTY) {
        table->buckets[index] = key;    
        return table;
    }
    
    // Double hashing: calculating the step size for the probe sequence
    long long step_size = 1 + (llabs(key) % (CAPACITY - 1));
    
    // Probe until an empty bucket or the same key is found
    while (table->buckets[index] != EMPTY && table->buckets[index] != key) {
        index = (index + step_size) % CAPACITY;
    }
    
    table->buckets[index] = key;
    
    return table;
}

int search(Hash* table, long long target_val) {
    long long index = hash_function(table, target_val);
    
    if (table->buckets[index] == target_val) {
        return 1;
    }
    
    long long temp_index = index;
    long long step_size = 1 + (llabs(target_val) % (CAPACITY - 1));
    
    while (table->buckets[temp_index] != target_val) {
        if (table->buckets[temp_index] == EMPTY) {
            return 0; // Target not found
        }
        
        temp_index = (temp_index + step_size) % CAPACITY;
        
        if (temp_index == index) {
            return 0; // Full cycle completed, target not found
        }
    } 
    
    return 1;
}

int main() {
    freopen("prob-2sum.txt", "r", stdin);
    srand(time(NULL));
    
    Hash* table = create_hash();
    long long key;
    
    // Load the 1,000,000 integers into the hash table
    for (int i = 0; i < 1000000; i++) {
        scanf("%lld", &key);
        table = insert_hash(table, key);
    }
    
    int current_target = -10000;
    int valid_targets = 0;
    long long y, x;
    
    // Check for each target sum in the range [-10000, 10000]
    while (current_target <= 10000) {
        
        for (int k = 0; k < CAPACITY; k++) {
            x = table->buckets[k];
            
            if (x != EMPTY) {
                y = current_target - x;
                int is_found = search(table, y);
                
                // x and y must be distinct values
                if (is_found == 1 && x != y) {
                    valid_targets++;
                    break; // Move to the next target sum once a valid pair is found
                }
            }
        }
        
        current_target++;
    }
    
    printf("%d\n", valid_targets);
    
    // Free allocated memory to prevent memory leaks
    free(table->buckets);
    free(table);
    
    return 0;
}
