// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int insert_hash(char *);
// Number of buckets in hash table 45631
const unsigned int N = 69389;

// Hash table
node *table[N];

//global counter
unsigned int global_count = 0;

//initializing table to NULL
void initialise()
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char buff_word[strlen(word) + 1];
    strcpy(buff_word, word);
    int l = strlen(buff_word);
    for (int i = 0; i < l; i++)
    {
        buff_word[i] = (char)tolower(buff_word[i]);
    }

    node *traverse = table[hash(buff_word)];
    if (traverse == NULL)
    {
        return false;
    }
    else
    {
        do
        {
            if (strcmp(traverse->word, buff_word) == 0)
            {
                return true;
            }
            traverse = traverse->next;
        }
        while (traverse != NULL);
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //h(k) = sum of ascii mod 23
    /*int sum_ascii = 0;
    for(int i = 0; word[i] != '\0'; i++)
    {
            sum_ascii += word[i];
    }
    return sum_ascii % N;*/

    //ref: https://old.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn/
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % N;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //initialise fn
    initialise();
    //buffer to store each word
    char word[LENGTH + 2];
    //load file into pointer
    FILE *inptr = fopen(dictionary, "r");
    //error check file
    if (inptr == NULL)
    {
        printf("ERROR OPENING POINTER TO FILE IN LOAD FUNC.!\n");
        return false;
    }
    //loop over file and load each line
    while (fgets(word, LENGTH + 2, inptr) != NULL)
    {

        //remove newline character from end
        strtok(word, "\n");

        //insert woord into hash table
        if (!insert_hash(word))
        {
            return false;
        }
    }
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return global_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *traverse;
    node *tmp;
    for (int i = 0; i < N; i++)
    {
        traverse = table[i];
        if (traverse != NULL)
        {
            while (traverse != NULL)
            {
                tmp = traverse;
                traverse = traverse->next;
                free(tmp);
            }
            //free(traverse);
        }
    }
    return true;
}

//fn to insert into hash table
int insert_hash(char *word)
{
    global_count++;
    //claculate index to inser
    int index = hash(word);
    //temp ptr variable and allocate mem;
    node *tmp = malloc(sizeof(node));
    //error check malloc
    if (tmp == NULL)
    {
        printf("ERROR ALLOCATION MEM TO TMP PTR!");
        return 0;
    }
    //insert data into tmp variable
    strcpy(tmp->word, word);
    tmp->next = NULL;
    //insert into hash table
    node *temp = table[index];
    table[index] = tmp;
    tmp->next = temp;

    /*if (table[index] == NULL)
    {
        table[index] = tmp;
    }
    //if bucket not empty, traverse till end to insert
    else
    {
        node *traverse = table[index];
        while (traverse->next != NULL)
        {
            traverse = traverse->next;
        }
        traverse->next = tmp;
    }*/
    return 1;
}