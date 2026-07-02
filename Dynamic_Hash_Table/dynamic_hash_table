#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Tombstone mechanism states for logical deletion
#define EMPTY -1
#define DELETED -2

typedef struct Hash {
    int* slots;
    int a;
    int b;
    int prime;
    int capacity;
    int current_size;
} Hash;

Hash* create_table(int capacity) {
    Hash* table = (Hash*)malloc(sizeof(Hash));
    table->slots = (int*)malloc(capacity * sizeof(int));
    
    for(int i = 0; i < capacity; i++) {
        table->slots[i] = EMPTY;
    }
    
    table->capacity = capacity;
    table->prime = 104729;
    
    // Random multipliers for Universal Hashing
    table->a = 1 + (rand() % (table->prime - 1));
    table->b = rand() % table->prime;
    table->current_size = 0;
    
    return table;
}

// Universal Hashing formula: ((a * key + b) % p) % m
int hash_function(Hash* table, int key) {
    int b = table->b, p = table->prime, capacity = table->capacity;
    long long a = table->a;
    
    long long index = ((a * key + b) % p) % capacity;
    return index;
}

Hash* insert_back(Hash* table, int key) {
    int index = hash_function(table, key);
    
    if(table->slots[index] == EMPTY) {
        table->slots[index] = key;
        table->current_size++;
        return table;
    }
    
    // Double Probing step to avoid primary clustering
    int mod = 1 + (key % 5);
    
    while(table->slots[index] != EMPTY && table->slots[index] != DELETED) {
        if (table->slots[index] == key) {
            return table; 
        } 
        index = (index + mod) % table->capacity;
    }
    
    table->slots[index] = key;
    table->current_size++;
    
    return table;
}

// Rehashing: Allocates new memory and recalculates physical indices
Hash* realloc_table(Hash* table, int type) {
    int new_capacity;
    
    if(type == 1) {
        new_capacity = table->capacity * 2;
    } else {
        new_capacity = table->capacity / 2;
        if (new_capacity < 4) {
            new_capacity = 4; // Minimum capacity threshold
        } 
    }

    Hash* new_table = create_table(new_capacity);
    
    int i = 0;
    while(table->current_size > 0 && i < table->capacity) {
        // Only rehash valid keys (ignore EMPTY and DELETED)
        if(table->slots[i] != EMPTY && table->slots[i] != DELETED) {
            new_table = insert_back(new_table, table->slots[i]);
            table->current_size--;  
        }
        i++;
    }
    
    free(table->slots);
    free(table);
    
    return new_table;
}

Hash* insert_front(Hash* table) {
    // Upscale trigger: Load factor reaches 75%
    if(table->current_size >= (3 * table->capacity) / 4) {
        table = realloc_table(table, 1);
    }
    
    int key = -1;
    
    while(key < 0) {
        printf("Which positive key would you like to add? ");
        scanf("%d", &key);
    }
    
    return insert_back(table, key);
}

int search_back(Hash* table, int key) {
    int index = hash_function(table, key);
    int current_index = index;
    int mod = 1 + (key % 5);
    
    // Crucial: Continue searching through DELETED (Tombstones), stop only at EMPTY
    while(table->slots[current_index] != EMPTY) {
        if(table->slots[current_index] == key) {
            return current_index;
        }
        
        current_index = (current_index + mod) % table->capacity;
        
        if(current_index == index) {
            break; // Full loop completed
        }
    }
    
    return -1;
}

Hash* search(Hash* table) {
    int key;
    printf("Which key would you like to search for? ");
    scanf("%d", &key);
    
    int index = search_back(table, key);
    
    if(index != -1) {
        printf("The key %d was found at index %d.\n", key, index);
    } else {
        printf("This key does not exist in the table.\n");
    }
    
    return table;
}

Hash* delete_hash(Hash* table) {
    int key;
    printf("Which key would you like to delete? ");
    scanf("%d", &key);
    
    int index = search_back(table, key);
    
    if(index == -1) {
        printf("The key does not exist in the table.\n");
        return table;
    }   
    
    // Logical deletion using Tombstone to preserve search chains
    table->slots[index] = DELETED;
    table->current_size--;
    printf("Key deleted successfully!\n");
    
    // Downscale trigger: Load factor drops to 25%
    if(table->current_size > 0 && table->current_size <= table->capacity / 4) {
        table = realloc_table(table, 2);
    }
    
    return table;
}

void free_table(Hash* table) {
    free(table->slots);
    free(table);
}

int main() {
    // Seed for universal hashing random multipliers
    srand(time(NULL));
    
    int capacity = 0, option = 0;
    
    while(capacity <= 0) {
        printf("How many initial slots would you like? ");
        scanf("%d", &capacity);  
    }
    
    Hash* table = create_table(capacity);
    
    while(option != 4) {
        printf("\nChoose an option:\n");
        printf("1- Insert\n");
        printf("2- Search\n");
        printf("3- Delete\n");
        printf("4- Exit\n");
        scanf("%d", &option);
        
        switch(option) {
            case 1:
                table = insert_front(table);
                break;
            case 2:
                table = search(table);
                break;
            case 3:
                table = delete_hash(table);
                break;
            case 4:
                printf("Exiting program.\n");
                free_table(table);
                break;
            default:
                printf("Invalid option.\n");
        }
    }
    
    return 0;
}
