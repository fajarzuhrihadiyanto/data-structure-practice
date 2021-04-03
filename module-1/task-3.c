/**
 * Modified Uno Stacko
 * Source : https://www.hackerrank.com/contests/sdf-m1/challenges/modified-uno-stacko
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
int stack_top(Stack *stack);

/**
 * Main Function
 * Description :
 *      This function is used as a main console app
 * */
int main() {
    int N, X, Nx, V, Y = 0;

    // GET THE NUMBER OF STACKO
    scanf("%d %d", &N, &X);

    // PREPARE THE STACKO
    Stack *stacko = malloc(N * sizeof(Stack));

    // REPEAT FOR THE NUMBER OF STACKO
    for(int i = 0; i < N; i++){
        // GET THE NUMBER OF BLOCK OF EACH STACKO
        scanf("%d", &Nx);

        // INITIALIZE EACH STACKO
        stack_init(&stacko[i]);

        // ADD THE VALUE FOR EVERY BLOCK OF EACH STACKO
        for(int j = 0; j < Nx; j++){
            scanf("%d", &V);
            stack_push(&stacko[i], V);
        }
    }

    // REPEAT UNTIL A CERTAIN BREAK CONDITION
    while(true){

        // SET DEFAULT CONDITION
        int temp = 1001;
        int index = 0;

        // GET THE MINIMUM VALUE OF THE TOP OF EACH STACK
        for(int i = 0; i < N; i++){
            if(!stack_isEmpty(&stacko[i]) && (stack_top(&stacko[i]) < temp || stack_top(&stacko[i]) == 1)){
                temp = stack_top(&stacko[i]);
                index = i;
            }
        }

        // IF THE MINIMUM VALUE IS LOWER OR EQUAL TO THE MAX VALUE ...
        if(X >= temp){
            // ... THEN, POP THAT STACKO ...
            stack_pop(&stacko[index]);

            // ... THEN, DECREASE THE MAX VALUE BY THE VALUE FOUND ...
            X -= temp;

            // ... AND INCREASE THE NUMBER OF STEP
            Y++;
        } else {
            // ... ELSE, BREAK THE LOOP
            break;
        }
    }

    // DISPLAY THE NUMBER OF STEP
    printf("%d", Y);

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
void stack_push(Stack *stack, int value) {
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
void stack_pop(Stack *stack) {
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
int stack_top(Stack *stack) {
    if (!stack_isEmpty(stack))
        return stack->_top->data;
    return 0;
}




