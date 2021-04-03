/**
 * Kosimp Bermain Pesan Berantai
 * Source : https://www.hackerrank.com/contests/sdf-m1/challenges/kosimp-bermain-pesan-berantai
 *
 * @author Fajar Zuhri Hadiyanto
 * @version 1.0
 * @since April 3rd 2021
 * */

// IMPORT PACKAGES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// DEFINE NODE TYPE
typedef struct node {
    char data[100];
    struct node *next, *previous;
} ListNode;

// DEFINE LIST TYPE
typedef struct list {
    unsigned _size;
    ListNode *_head;
    ListNode *_tail;
} List;

// PROTOTYPING
void listInit(List *list);
bool listIsEmpty(List *list);
void listPushBack(List *list, char *value);

/**
 * Main Function
 * Description :
 *      This function is used as a main console app
 * */
int main() {
    // PREPARE LIST OF PEOPLE
    List people;
    listInit(&people);

    // GET THE NUMBER OF POEPLE
    int nPeople;
    scanf("%d", &nPeople);

    // INSERT EVERY PERSON TO THE LIST
    char person[100];
    for(int i = 0; i < nPeople; i++){
        scanf("%s", person);
        listPushBack(&people, person);
    }

    // START THE GAME
    int value;
    char direction[10];
    ListNode *temp = people._head;

    // REPEAT FOR THE NUMBER OF PEOPLE - 1
    for(int i = 1; i < nPeople; i++){

        // GET THE VALUE OF STEP AND DIRECTION
        scanf("%d %s", &value, direction);

        // IF DIRECTION IS "Kanan" ...
        if(strcmp(direction, "Kanan") == 0){
            // ... THEN, GO TO THE NEXT (STEP - 1) TIMES
            for(int j = 1; j < value; j++){
                temp = temp->next;
            }
        }
        // IF DIRECTION IS "Kiri" ...
        else {
            // ... THEN, GO TO THE PREVIOUS (STEP - 1) TIMES
            for(int j = 1; j < value; j++){
                temp = temp->previous;
            }
        }

        // DISPLAY THE DATA
        printf("%s\n", temp->data);
    }

    return 0;
}

/**
 * Function listInit
 * Description :
 *      This function is used to initialize the circular doubly linked list
 *
 * @param list pointer to list to be initialized
 * */
void listInit(List *list) {
    list->_head = NULL;
    list->_tail = NULL;
    list->_size = 0;
}

/**
 * Function listIsEmpty
 * Description :
 *      This function is used to check if the list is empty or not
 *
 * @param list pointer to list to be checked the emptiness
 * @return true if head of the list is NULL, else false
 * */
bool listIsEmpty(List *list) {
    return (list->_head == NULL);
}

/**
 * Function listPushBack
 * Description :
 *      This function is used to add new data to tail of the list.
 *
 * @param list pointer to list to be added by new data
 * @param value data to be added to the list
 * */
void listPushBack(List *list, char *value) {
    ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
    if (newNode) {
        list->_size++;
        strcpy(newNode->data, value);

        if (listIsEmpty(list)){
            list->_head = newNode;
            list->_tail = newNode;
        }
        else {
            newNode->next = list->_head;
            newNode->previous = list->_tail;

            list->_head->previous = newNode;
            list->_tail->next = newNode;
            list->_tail = newNode;
        }
    }
}


