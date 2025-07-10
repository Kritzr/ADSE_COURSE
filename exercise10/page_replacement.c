#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_FRAMES 100

int find_victim(int frames[], int recency[], int capacity) {
    int victim_index = -1;
    int min_recency = INT_MAX;
    int tie_break_value = -1;  

    for (int i = 0; i < capacity; i++) {
        if (recency[i] < min_recency) {
            min_recency = recency[i];
            victim_index = i;
            tie_break_value = frames[i];
        } else if (recency[i] == min_recency) {
            // Tie-breaker: if current page value is higher, choose that one to evict
            if (frames[i] > tie_break_value) {
                tie_break_value = frames[i];
                victim_index = i;
            }
        }
    }
    return victim_index;
}

int main(void) {
    
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int num_pages = sizeof(pages) / sizeof(pages[0]);
    
    // frame size 
    int capacity = 3;
    int frames[MAX_FRAMES];
    int recency[MAX_FRAMES];
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        recency[i] = 0;
    }
    
    int time = 0;  
    int hits = 0, faults = 0;
    
    printf("Page\tFrames\t\tResult\n");
    for (int i = 0; i < num_pages; i++) {
        int current_page = pages[i];
        time++;  
        int found = 0;
        
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == current_page) {
                hits++;
                recency[j] = time;  
                found = 1;
                break;
            }
        }
        
       
        if (!found) {
            faults++;
          
            int free_index = -1;
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1) {
                    free_index = j;
                    break;
                }
            }
            if (free_index != -1) {
        
                frames[free_index] = current_page;
                recency[free_index] = time;
            } else
            {
                int victim = find_victim(frames, recency, capacity);
                frames[victim] = current_page;
                recency[victim] = time;
            }
        }
       
        printf("%d\t", current_page);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        if (found)
            printf("\tHIT\n");
        else
            printf("\tFAULT\n");
    }
    
    // Summary of results
    printf("\nTotal Hits: %d\n", hits);
    printf("Total Faults: %d\n", faults);
    printf("Hit Ratio: %.2f\n", (float)hits / num_pages);
    
    return 0;
}

