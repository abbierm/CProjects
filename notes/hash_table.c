// Accepts words from terminal and puts them inside of a hash table

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define rows 26

// Max word length
#define MAX 45


// Max line length
#define N 256

// Stores a word inside of the hash table
struct node
{
    char word[MAX + 1];
    struct node *next;
}
typedef node;


// The hash table
node *hash_table[rows];

void make_table(void);

// Returns the hash value for the word
int hash_value(char w);

bool check(const char *w, int hash);

bool load(const char *w);

// frees the hash table
void free_table(void);

// Prints the hash table
void print_table(void);

int main(void)
{

    make_table();
    
    // Helpers to get words
    char line[N];

    // Stores the new word
    char new_word[MAX];

    printf("Type words to be loaded into the hash table 256 characters at a time.\n");
    printf("If you would like to add more than 256 words, press enter and keep typing\n");
    printf("Once you are done, enter an empty line\n");        
    
    // Takes in one line at a time via the terminal
    while (fgets(line, sizeof(line), stdin) != NULL)
        {
            if (line[0] == '\n')
            {
                break;
            }

            // controls whether to load to word
            bool valid = true;

            // Controls whether to add the line endings
            bool current_word = false;
            int letter_count = 0;
            for (int i = 0; i < N; i++)
            {
                char c = line[i];
                if (c == '\n' && current_word == false)
                {
                    valid = false;
                }

                // if it wasn't valid but its a new word
                if (!valid && (c == ' ' || ispunct(c)))
                {
                    valid = true;
                    letter_count = 0;
                    
                }

                // first letter and the char isn't a letter
                else if (!isalpha(c) && letter_count == 0)
                {
                    valid = false;
                }

                // First letter has to be alphabetic
                else if (letter_count == 0 && isalpha(c))
                {
                    
                    new_word[letter_count] = c;
                    letter_count++;
                    current_word = true;
                    
                }

                // the end of the word
                else if ((ispunct(c) || c == ' ' || c == '\n') && valid && 
                            (letter_count > 0  && letter_count < MAX) )
                {
                    
                    new_word[letter_count] = '\0';

                    if(!load(new_word))
                    {
                        return 1;
                    }

                    letter_count = 0;
                    current_word = false;

                }

                // all the other letters can be whatever
                else if (valid && (letter_count > 0 || letter_count < MAX))
                {
                    new_word[letter_count] = c;
                    letter_count++;
                }

                // too many letters set valid to false to this loop can continue reading letters
                else if (letter_count >= MAX)
                {
                    valid = false;
                }
            }
        }

    print_table();
    free_table();
    return 0;
}


void make_table(void)
{
    for (int i = 0; i < rows; i++)
    {
        // Make a new NULL node
        node *new = NULL;
        hash_table[i] = new;
    }
}

void free_table(void)
{
    for (int i = 0; i < rows; i++)
    {
        node *ptr = hash_table[i];
        while (ptr != NULL)
        {
            node *tmp = ptr->next;
            free(ptr);
            ptr = tmp;
        }
    }
    return;
}

int hash_value(char w)
{
    // Super simple hash function converts word to 
    // base 26 with A = 0, B = 1, etc.... 
    int new_hash = toupper(w) - 65;
    return new_hash;
}

bool check(const char *w, int hash)
{
    for (node *ptr = hash_table[hash]; ptr != NULL; ptr = ptr->next)
    {
        if (strcmp(ptr->word, w) == 0)
        {
            return false;
        }
    }
    return true;
}

bool load(const char *w)
{
    node *new = malloc(sizeof(node));
    if (new == NULL)
    {
        printf("Memory Error\n");
        free_table();
        return false;
    }

    strcpy(new->word, w);
    new->next = NULL;

    int hash = hash_value(new->word[0]);

    // put in hash table
    if (hash_table[hash] == NULL)
    {
        hash_table[hash] = new;
    }

    else
    {
        // if word is already in the hash table we just let it go
        if (!check(new->word, hash))
        {
            free(new);
        }
        else
        {
            node *tmp = hash_table[hash];
            hash_table[hash] = new;
            hash_table[hash]->next = tmp; 
        }
    }
    return true;
}

void print_table(void)
{
    // Prints a list of all of the hash table
    // items and the index location they exist in.
    for (int i = 0; i < rows; i++)
    {
        printf("Array index number: %i\n", i);
        int count = 0;
        for (node *ptr = hash_table[i]; ptr != NULL; ptr = ptr->next)
        {
            printf("Word #%i, Current word: %s\n", count + 1, ptr->word);
            count++;
        }
    }
}