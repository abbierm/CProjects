// Creates an array of non repeating random integers 
// and uses the numbers to create a sorted linked list


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define N 5

int array[N];

struct node
{
    int number;
    struct node *next;
}
typedef node;

node *linked_list;

void make_array(void)
{
    // Random Seed
    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
        for (;;)
        {

            int flag = 0;
            int random = rand() % 2000;

            for (int j = 0; j < i; j++)
            {
                if (random == array[j])
                {
                    flag = 1;
                    break;
                }
            }

            if (flag == 0)
            {
                array[i] = random;
                printf("Array index: %i = %i\n", i, random);
                break;
            }
        }
    }
}


void print_list(void)
{
    node *ptr = linked_list;
    while (ptr != NULL)
    {
        printf("Current number: %i\n", ptr->number);
        printf("Next Address: %p\n", ptr->next);
        printf("\n");
        ptr = ptr->next;
    }
}

// Frees the linked list
void unload(void)
{
    node *ptr = linked_list;

    while (ptr != NULL)
    {
        node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
}

// Creates the sorted linked list
bool make_list(void)
{
    for (int i = 0; i < N; i++)
    {
        // Create a new node with the current number in the array
        
        // Carve out enough space for a new node for the linked_list
        node *new = malloc(sizeof(node));

        // Make sure the new node has enough space
        if (new == NULL)
        {
            // Unload all of the lists we've made thus
            // for and return fast to the main function 
            printf("Not enough memory for list\n");
            unload();
            return false;
        }

        // Add the number in the array to the current node 
        new->number = array[i];

        // Set the next value to NULL
        new->next = NULL;

        // Determine where the new node should exist on the linked_list

        // if the linked_list is empty we assign the new item to that place
        if (linked_list == NULL)
        {
            linked_list = new;
        }

        // If the new number is less than the number for the current linked list
        else if (new->number < linked_list->number)
        {
            new->next = linked_list;
            linked_list = new;
        }

        // We need to traverse down the list to find where the current node goes
        else
        {
            for (node *ptr = linked_list; ptr != NULL; ptr = ptr->next)
            {
                // The next number is larger than the current number
                if (ptr->next == NULL)
                {
                    ptr->next = new;
                    break;
                }

                // If there are no more numbers we set next to be new
                else if (new->number < ptr->next->number)
                {
                    node *tmp = ptr->next;
                    ptr->next = new;
                    new->next = tmp;
                    break;
                }
            }
        }
        
    }
    return true;   
}



int main(void)
{
    make_array();
    
    if (make_list() == false)
    {
        return 1;
    }

    //print_list();

    unload();
    
    return 0;
}