#include "bulls_cows_c.h"


int main() {
//    run_game();
    for (int i = 0; i < 100; ++i) {
        printf("%d, ",rand());
    }
    return 0;
}





/**
 * @brief
 * gets 2 numbers, compare bulls and cows.
 *  if same as list return true
 *
 * @param a first number
 * @param b second number
 * @param list 2 numbers:[bulls,cows]
 * @return true if same as list
 */
bool compare_two_numbers(const char *a, const char *b, const int *list) {
    int bulls = 0;
    int cows = 0;
    for (int i = 0; i < NUM_OF_DIGITS; i++) {
        if (a[i] == b[i]) {
            bulls += 1;
        }
        for (int j = 0; j < NUM_OF_DIGITS; j++) {
            if (a[i] == b[j]) {
                cows += 1;
            }
        }
    }
    cows -= bulls; // becasue it includes the bulls
    if (bulls == list[0] &&
        cows == list[1]) {
        return true;
    }
    return false;
}


void compare_two_numbers_for_player(const char *a, const char *b, int *list) {
    list[0] = list[1] = 0;
    for (int i = 0; i < NUM_OF_DIGITS; i++) {
        if (a[i] == b[i]) {
            list[0] += 1;
        }
        for (int j = 0; j < NUM_OF_DIGITS; j++) {
            if (a[i] == b[j]) {
                list[1] += 1;
            }
        }
    }
    list[1] -= list[0]; // becasue it includes the bulls
}



/**
 * @brief gets a number in string. if it has duplicates
 * or zeros return false
 *
 * @return true
 * @return false
 */
bool num_is_legit(char *num) {
    for (int i = 0; i < NUM_OF_DIGITS; i++) {
        if (num[i] == '0') {
            return false;
        }
        for (int j = i + 1; j < NUM_OF_DIGITS; j++) {
            if (num[i] == num[j]) {
                return false;
            }
        }
    }
    return true;
}


/**
 * Create a initial list object with all the possible answers
 * @return pointer to the list
 */
Number_List *create_initial_list() {
    //+-amount of numbers in list
    int starting_num = pow(10, NUM_OF_DIGITS - 1);
    int ending_num = pow(10, NUM_OF_DIGITS);
    int amount_of_nums = ending_num - starting_num;
    Number_List *number_list = (Number_List *) malloc(sizeof(Number_List));
    number_list->array = (char **) malloc(sizeof(char *) * amount_of_nums);
    if (!number_list->array) {
        exit(1);
    }
    number_list->size = 0;
    // run on all numbers, if fits go into list
    for (int i = starting_num; i < ending_num; i++) {
        char num[NUM_OF_DIGITS + 1];
        sprintf(num, "%d", i);
        if (num_is_legit(num)) {
            char *num_ptr = (char *) malloc(sizeof(char) * (NUM_OF_DIGITS + 1));//not sure about the +1 bcs '\0'
            if (!num_ptr) {
                exit(1);
            }
            sprintf(num_ptr, "%d", i);
            number_list->array[number_list->size] = num_ptr;
            number_list->size++;
        }
    }

    return number_list;
}



/**
 * @brief filter the list based on answer
 *
 * @param old_list list to filter
 * @param question string number that was asked from user
 * @param answer int[2] [bulls,cows]
 * @return Number_List* new filtered list
 */
Number_List *filter_list(Number_List **old_list, char *question, int answer[2]) {
    char temp_question[4];
    strcpy(temp_question, question);
    Number_List *new_list = (Number_List *) malloc(sizeof(Number_List));
    //add malloc fail
    new_list->array = (char **) malloc(sizeof(char *) * (*old_list)->size);
    new_list->size = 0;
    //add malloc fail
    for (int i = 0; i < (*old_list)->size; i++) {
        //if fits, add to new list and remove from old
        if (compare_two_numbers((*old_list)->array[i], temp_question, answer)) {
            new_list->array[new_list->size] = (*old_list)->array[i];
            (*old_list)->array[i] = NULL;
            new_list->size++;
        }

            //if not, delete data and pointer
        else {
            free((*old_list)->array[i]);
            (*old_list)->array[i] = NULL;
        }
    }
    free(*old_list);
    return new_list;
}

/**
 * free all params from the game when finished
 * @param number_list
 * @param computer_pick
 * @param choice
 */
void free_single_game(Number_List **number_list, char **computer_pick, char **choice) {
    for (int i = 0; i < (*number_list)->size; ++i) {
        if ((*number_list)->array != NULL) {
            free((*number_list)->array[i]);
        }
    }
    free((*number_list)->array);
    free(*number_list);
    *number_list = NULL;
    free(*computer_pick);
    *computer_pick = NULL;
    free(*choice);
    *choice = NULL;
}

/**
 * runs a full single game
 */
void run_single_game() {

    //create list of allowed numbers
    srand(time(0));
    Number_List *number_list = create_initial_list();
    char *computer_pick = (char *) malloc(sizeof(char) * NUM_OF_DIGITS);
    strcpy(computer_pick, number_list->array[rand() % number_list->size]);
//    printf("computer pick is %s\n\n", computer_pick); // if want to see computer pick each game
    int iteration_counter = 0;
    char *choice = malloc(NUM_OF_DIGITS);
    int player_guess_list[2] = {0};
    int bulls_cows[2] = {0};
    //run game as long as number_list.size>1
    while (number_list->size > 1 && 0 != strcmp(choice, computer_pick)) {


        iteration_counter += 1;
        //(guess first number, maybe change to random)
        printf("Question #%d: %s\nHow many bulls and cows?\n", iteration_counter, number_list->array[0]);;
        scanf("%d %d", &bulls_cows[0], &bulls_cows[1]);
        number_list = filter_list(&number_list, number_list->array[0], bulls_cows);


        /** player's side**/
        printf("Your turn to ask:");
//        char str[2];
        scanf("%s", choice);
//        printf(number_list)
        compare_two_numbers_for_player(choice, computer_pick, player_guess_list);
        if (0 == strcmp(choice, computer_pick)) {
            printf("You're right!! %s was my choice :)\n", computer_pick);
        } else {
            printf("You got %d bulls and %d cows.\n", player_guess_list[0], player_guess_list[1]);
        }


    }
    //if number_list.size=0 mistake in answers
    if (number_list->size == 0) {
        printf("You probably made a mistake along the way, there's no such number!\n");
    }

        //return last option=
    else if (number_list->size == 1) {
        printf("Your number is %s!\n", number_list->array[0]);
    }
    free_single_game(&number_list, &computer_pick, &choice);
}

/**
 * run game until player asks to stop
 */
void run_game() {
    bool flag = true;
    int game_counter = 0;
    printf(ENTERANCE_TEXT);
    while (flag) {
        game_counter += 1;
        printf("@@@@@@@@@@@@@@@@@@@@@\nGame #%d \n@@@@@@@@@@@@@@@@@@@@@\n", game_counter);
        run_single_game();
        printf("Would you like to play again? yes[Y/y] no[N/n]:\n");

        char c;
        scanf("\n %c", &c);
        if (c == 'Y' || c == 'y') {
            flag = true;
        } else {
            flag = false;
        }
    }
}