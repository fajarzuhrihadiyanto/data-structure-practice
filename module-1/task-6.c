/**
 * String si Cantok
 * Source : https://www.hackerrank.com/contests/sdf-m1/challenges/string-si-cantok
 *
 * @author Fajar Zuhri Hadiyanto
 * @version 1.0
 * @since April 3rd 2021
 * */

// IMPORT PACKAGES
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// DEFINE NODE TYPE
typedef struct stackNode_t {
    char data;
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
void stack_push(Stack *stack, char value);
void stack_pop(Stack *stack);
char stack_top(Stack *stack);
void stack_display(Stack *stack);
void stack_reverse(Stack *stack, Stack *result);

/**
 * Main Function
 * Description :
 *      This function is used as a main console app
 * */
int main() {
    // PREPATE THE STACK
    Stack word;
    stack_init(&word);

    // GET THE WORD
    char input[1001];
    scanf("%s", &input);

    // REPEAT FOR EVERY CHARACTER IN THE INPUT WORD
    for(int i = 0; input[i] != '\0'; i++){

        // IF THE STACK IS EMPTY ...
        if(stack_isEmpty(&word)){
            // ... THEN, JUST PUSH CURRENT CHARACTER TO THE STACK
            stack_push(&word, input[i]);
        } else {
            // ELSE, CHECK IF CURRENT CHARACTER AND TOP OF THE STACK ARE THE SAME
            if(stack_top(&word) == input[i]){
                // THEN, POP THE STACK
                stack_pop(&word);
            } else {
                // ELSE, PUSH CURRENT CHARACTER TO THE STACK
                stack_push(&word, input[i]);
            }
        }
    }

    // REVERSE THE STACK
    Stack result;
    stack_init(&result);
    stack_reverse(&word, &result);

    // DISPLAY STACK NODE
    stack_display(&result);

    return 0;
}

/**
 * Function stack_init
 * Description :
 *      This function is used to initialize the stack.
 *
 * @param stack pointer to stack to be initialized
 * */
void stack_init(Stack *stack) {
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
void stack_push(Stack *stack, char value) {
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
 * Function stack_top
 * Description :
 *      This function is used to get the top element of the given stack.
 *
 * @param stack pointer to stack to be gotten at the top element
 * @return top element of the stack if the stack is not empty, else 0
 * */
char stack_top(Stack *stack)
{
    if (!stack_isEmpty(stack))
        return stack->_top->data;
    return 0;
}

/**
 * Function stack_reverse
 * Description :
 *      This function is used to reverse the stack and store them to the result stack
 *
 * @param stack pointer to the source stack
 * @param result pointer to the result stack
 * */
void stack_reverse(Stack *stack, Stack *result){
    if(!stack_isEmpty(stack)){
        StackNode *temp = stack->_top;
        while(temp != NULL){
            stack_push(result, temp->data);
            temp = temp->next;
        }
    }
}

/**
 * Function stack_display
 * Description :
 *      This function is used to display all elements of the stack
 *
 * @param stack pointer to stack to be displayed it's element
 * */
void stack_display(Stack *stack) {
    if(!stack_isEmpty(stack)){
        StackNode *temp = stack->_top;
        while(temp != NULL){
            printf("%c", temp->data);
            temp = temp->next;
        }
    } else {
        printf("Yah habis :(");
    }
}
