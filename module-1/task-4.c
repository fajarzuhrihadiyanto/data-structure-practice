/**
 * Plagiarism 1
 * Source : https://www.hackerrank.com/contests/sdf-m1/challenges/plagiarism-1-1
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
typedef struct stackNode_t {
    int data;
    struct stackNode_t *next;
} StackNode;

// DEFINE STACK TYPE
typedef struct stack_t {
    StackNode *_top;
    unsigned _size;
} Stack;

// PROTOTYPING
void stack_init(Stack *stack);
bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, int value);
void stack_pop(Stack *stack);
bool stack_compare(Stack *stack1, Stack *stack2);
int stack_top(Stack *stack);

/**
 * Main Function
 * Description :
 *      This function is used as a main console app
 * */
int main() {

    // PREPARE THE STACK TO STORE ANSWERS OF EACH PERSON
    Stack nawab, holen;
    stack_init(&nawab);
    stack_init(&holen);

    // GET THE NUMBER OF QUERY
    int nQuery;
    scanf("%d\n", &nQuery);

    char query[100];
    int value;

    // REPEAT FOR THE NUMBER OF QUERY
    for(int i = 0; i < nQuery; i++){

        // GET THE QUERY
        scanf("%s", query);

        // IF THE QUERY IS UNDO ...
        if(strcmp(query, "undo") == 0){
            // ... THEN, REMOVE THE LAST ANSWER OF EACH PERSON
            stack_pop(&nawab);
            stack_pop(&holen);
        }
        // IF NOT ...
        else {
            // ... THEN GET THE ANSWER ...
            scanf("%d", &value);

            // ... AND PUSH IT TO THE CORRESPONDING QUERY
            if(strcmp(query, "NAWAB") == 0){
                stack_push(&nawab, value);
            } else {
                stack_push(&holen, value);
            }
        }
    }

    // IF STACK COMPARE RETURN TRUE (SAME ANSWER), THEN
    // DISPLAY "NYONTEK", AND IF NOT, DISPLAY "JUJUR"
    if(stack_compare(&nawab, &holen)){
        printf("NYONTEK");
    } else {
        printf("JUJUR");
    }

    return 0;
}

/**
 * Function stack_init
 * Description :
 *      This function is used to initialize the stack.
 *
 * @param stack pointer to stack to be initialized
 * */
void stack_init(Stack *stack){
    stack->_top = NULL;
    stack->_size = 0;
}

/**
 * Function stack_isEmpty
 * Description :
 *      This function is used to check if the stack is empty or not.
 *
 * @param stack pointer to stack to be checked the emptiness
 * @return true if top of the stack is null, else false
 * */
bool stack_isEmpty(Stack *stack) {
    return (stack->_top == NULL);
}

/**
 * Function stack_push
 * Description :
 *      This function is used to add a value to the top of the stack.
 *
 * @param stack pointer to stack to be added by new data
 * @param value new data to be added to the top of the stack
 * */
void stack_push(Stack *stack, int value)
{
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        newNode->data = value;

        if (stack_isEmpty(stack)) newNode->next = NULL;
        else newNode->next = stack->_top;

        stack->_top = newNode;
    }
}

/**
 * Function stack_pop
 * Description :
 *      This function is used to remove the top element of the stack.
 *
 * @param stack pointer to stack to be removed at the top element
 * */
void stack_pop(Stack *stack)
{
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        free(temp);
        stack->_size--;
    }
}

/**
 * Function stack_compare
 * Description :
 *      This function is used to check if two stacks have the same value of each node
 *
 * @param stack1 pointer to the first stack
 * @param stack2 pointer to the second stack
 * @return true if two stacks have the same value of each node, else false
 * */
bool stack_compare(Stack *stack1, Stack *stack2) {
    StackNode *temp1 = stack1->_top;
    StackNode *temp2 = stack2->_top;

    if(!stack_isEmpty(stack1) && !stack_isEmpty(stack2)){
        while(temp1 != NULL && temp2 != NULL){
            if(temp1->data != temp2->data){
                return false;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    return true;
}

/**
 * Function stack_top
 * Description :
 *      This function is used to get the top element of the given stack.
 *
 * @param stack pointer to stack to be gotten at the top element
 * @return top element of the stack if the stack is not empty, else 0
 * */
int stack_top(Stack *stack)
{
    if (!stack_isEmpty(stack))
        return stack->_top->data;
    return 0;
}
