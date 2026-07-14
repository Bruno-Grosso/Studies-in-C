#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPACITY 2000003
// Using the smallest possible 64-bit value to avoid conflicts with real dataset numbers
#define EMPTY -999999999999999LL 

typedef struct Hash {
    long long* buckets;
} Hash;

Hash* create_hash() {
    Hash* table = (Hash*)malloc(sizeof(Hash));
    table->buckets = (long long*)malloc(CAPACITY * sizeof(long long));
    
    for (int i = 0; i < CAPACITY; i++) {
        table->buckets[i] = EMPTY;
    }
    
    return table;
}

// Direct and optimized hashing using the prime capacity
long long hash_function(long long key) {
    return llabs(key) % CAPACITY;
}

Hash* insert_hash(Hash* table, long long key) {
    long long index = hash_function(key);
    
    if (table->buckets[index] == EMPTY) {
        table->buckets[index] = key;    
        return table;
    }
    
    // Double hashing: using (CAPACITY - 2) to ensure coprime step sizes
    long long step_size = 1 + (llabs(key) % (CAPACITY - 2));
    
    // Probe until an empty bucket or the same key is found
    while (table->buckets[index] != EMPTY && table->buckets[index] != key) {
        index = (index + step_size) % CAPACITY;
    }
    
    table->buckets[index] = key;
    
    return table;
}

int search(Hash* table, long long target_val) {
    long long index = hash_function(target_val);
    
    if (table->buckets[index] == target_val) {
        return 1;
    }
    
    long long temp_index = index;
    long long step_size = 1 + (llabs(target_val) % (CAPACITY - 2));
    
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
    // 1. Safe File Reading
    FILE* file = fopen("prob-2sum.txt", "r");
    if (!file) {
        printf("CRITICAL ERROR: 'prob-2sum.txt' not found!\n");
        return 1;
    }

    Hash* table = create_hash();
    
    // 2. Auxiliary Array for Search Optimization
    long long* inputs = (long long*)malloc(1000000 * sizeof(long long));
    int total_numbers = 0;
    long long key;

    printf("Loading integers into the Hash Table...\n");
    
    // fscanf returns 1 only if it successfully reads an integer
    while (fscanf(file, "%lld", &key) == 1 && total_numbers < 1000000) {
        table = insert_hash(table, key);
        inputs[total_numbers++] = key; 
    }
    fclose(file);

    printf("Data loaded. Total entries: %d\n", total_numbers);
    printf("Starting 2-SUM processing...\n");
    
    int current_target = -10000;
    int valid_targets = 0;
    long long y, x;

    // Check for each target sum in the range [-10000, 10000]
    while (current_target <= 10000) {
        
        // Progress tracker to monitor the processing speed
        if (current_target % 100 == 0) {
            printf("Checking targets... Current: %d\n", current_target);
        }

        // Loop only through the actual numbers present in the file
        for (int k = 0; k < total_numbers; k++) {
            x = inputs[k];
            y = current_target - x;
            
            // Search for the complement in the Hash Table
            if (x != y && search(table, y) == 1) {
                valid_targets++;
                break; // Move to the next target sum once a valid pair is found
            }
        }
        
        current_target++;
    }

    printf("\nFINAL RESULT: %d\n", valid_targets);

    // Free dynamically allocated memory
    free(inputs);
    free(table->buckets);
    free(table);

    return 0;
}
