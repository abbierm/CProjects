//
// merge_sort.c
//
// Creates an array with random integers and sorts
// the array using the merge sort algorithm
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Controls the size of the array 
#define N 20

// The array that gets sorted
int list[N];


// Fills the array with non-repeating integers
void fill_array(void)
{
    // Sets random seed
    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
        // Controls whether to continue
        for (;;)
        {
            int random_integer = rand() % 100;
            
            // Used as a control to determine if there are any repeated numbers
            int flag = 0;

            for (int j = 0; j < i; j++)
            {
                if (list[j] == random_integer)
                {
                    flag = 1;
                    break;
                }
            }

            // If the flag stayed 0, the number wasn't repeated 
            // and list[i] can be set as the random_integer value
            if (flag == 0)
            {
                list[i] = random_integer;
                break;
            }
        }
    }
}

// Prints the array
void print_array(int arr[], int length)
{
    printf("[");
    for (int i = 0; i < length; i++)
    {
        printf("%i, ", arr[i]);
    }
    printf("]\n");
}

// Creates two subarrays and merges them togethr
// left = left index
// right = right index
// mid = midpoint using left + (right - left) / 2
void merge(int left, int right, int mid)
{
    // initialize sub array sizes from the current left, right, and midpoint
    int left_size = mid - left + 1;
    int right_size = right - mid;

    // Initialize sub arrays
    int L[left_size];
    int R[right_size];

    // Fill up the sub arrays from the original array
    for (int i = 0; i < left_size; i++)
    {
        L[i] = list[i + left];
    }
    for (int j = 0; j < right_size; j++)
    {
        R[j] = list[mid + j + 1];
    }

    // Helps keep track of which numbers from the sub arrays have been merged
    int l = 0, r = 0;

    // Keeps track of which number gets sorted into the new array next
    int p = left;

    // The merging while loop adds the smallest
    // number the subarray to the index at p
    while (l < left_size && r < right_size)
    {
        if (L[l] < R[r])
        {
            list[p] = L[l];
            l++;
        }
        else
        {
            list[p] = R[r];
            r++;
        }
        p++;
    }

    // Any of the numbers that didn't get added to the array from
    // the subarrays in the previous while loop get added in one 
    // of the subsequent while loops. 
    // 
    // If multiple numbers from one subarray were consistently 
    // smaller than the numbers in the other subarray then 
    // one of these while loops will add all of the numbers 
    // from the other subarray to finish the "merge".
    while (l < left_size)
    {
        list[p] = L[l];
        p++;
        l++;
    }
    while (r < right_size)
    {
        list[p] = R[r];
        p++;
        r++;
    }
}

// Spilts the arrays in two halves and recursively calls 
// itself until the arrayis either 1 ir 0 in length. Upon 
// returning, the array gets sorted using the merge function 
void mergesort(int left, int right)
{
    // Ensures that midpoint is at least 1
    int midpoint = left + (right - left) / 2;

    if (left < right)
    {
        // recursively calls the left side of the array
        mergesort(left, midpoint);

        // recursively calls the right side of the array
        mergesort(midpoint + 1, right);

        // Merges the two subarrays
        merge(left, right, midpoint);
    }
}

int main(void)
{
    fill_array();
    
    printf("Unsorted Array\n");
    print_array(list, N);

    mergesort(0, N - 1);

    printf("Sorted Array\n");
    print_array(list, N);
}