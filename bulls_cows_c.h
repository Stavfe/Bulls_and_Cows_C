#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_OF_DIGITS 4

#define ENTERANCE_TEXT "\nWelcome to the game Bulls&Cows, guess a number and let the programm" \
                       " find your guess.\n"                                                   \
                       "Think of a number of 4 digits, no duplicates, and no zeros.\n"         \
                       "answer the questions by assigning 2 numbers each time "                \
                       "like that-\n\"Bulls\" \"Cows\" \n"                                     \
                       "Example: the number is 1234, the guess was 2134, "                     \
                       "so your answer should be \'2 2\'\n"                                    \
                       "Good luck!\n"

/**
 * @brief struct to hold array of numbers(strings)
 * and the size of the array
 * 
 */
typedef struct Number_List {
    unsigned long size;
    char **array;
} Number_List;


bool compare_two_numbers(const char *a, const char *b, const int *list);


void compare_two_numbers_for_player(const char *a, const char *b, int *list);



bool num_is_legit(char *num);



Number_List *create_initial_list();



Number_List *filter_list(Number_List **old_list, char *question, int answer[2]);



void free_single_game(Number_List **number_list, char **computer_pick, char **choice);

void run_single_game();


void run_game();

