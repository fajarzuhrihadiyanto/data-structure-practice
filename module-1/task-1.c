/**
 * Udin Petot Belajar Dynamic Array
 * Source : https://www.hackerrank.com/contests/sdf-m1/challenges/udin-petot-belajar-dynamic-array
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

// DEFINE THE DYNAMIC ARRAY
typedef struct dynamicarr_t {
    int *_arr;
    unsigned _size, _capacity;
} DynamicArray;

// PROTOTYPING
void dArray_init(DynamicArray *darray);
bool dArray_isEmpty(DynamicArray *darray);
void dArray_pushBack(DynamicArray *darray, int value);
void dArray_popBack(DynamicArray *darray);
int dArray_back(DynamicArray *darray);
int dArray_front(DynamicArray *darray);
void dArray_setAt(DynamicArray *darray, unsigned index, int value);
int dArray_getAt(DynamicArray *darray, unsigned index);
int dArray_sum(DynamicArray *darray, int index1, int index2);
void dArray_removeAt(DynamicArray *darray, int index);

/**
 * Main Function
 * Description :
 *      This function is used as a main console app
 * */
int main() {

    // PREPARE THE DYNAMIC ARRAY
    DynamicArray array;
    dArray_init(&array);

    // GET THE NUMBER OF QUERY
    int nQuery;
    scanf("%d", &nQuery);

    // DECLARE THE QUERY
    char query[20];
    int val1, val2;

    // REPEAT FOR THE NUMBER OF QUERY
    for(int i = 0; i < nQuery; i++){

        // GET THE QUERY
        scanf("%s", query);

        // IF THE QUERY IS INSERT ...
        if(strcmp(query, "INSERT") == 0){

            // ... THEN, GET THE VALUE TO BE INSERTED ...
            scanf("%d", &val1);

            // ... AND PUSH IT TO THE DYNAMIC ARRAY.
            dArray_pushBack(&array, val1);

        }
        // IF THE QUERY IS DELETE ...
        else if(strcmp(query, "DELETE") == 0){

            // ... THEN, GET THE INDEX ...
            scanf("%d", &val1);

            // ... AND REMOVE AT A CERTAIN INDEX.
            dArray_removeAt(&array, val1);
        }
        // IF THE QUERY IS UPDATE ...
        else if(strcmp(query, "UPDATE") == 0){

            // ... THEN, GET THE INDEX AND VALUE TO BE UPDATED WITH ...
            scanf("%d %d", &val1, &val2);

            // ... AND UPDATE THE DYNAMIC ARRAY.
            dArray_setAt(&array, val1, val2);
        }
        // IF THE QUERY IS GET ...
        else if(strcmp(query, "GET") == 0){

            // ... THEN, GET THE INDEX ...
            scanf("%d", &val1);

            // ... AND PRINT ELEMENT OF THE DYNAMIC ARRAY AT THE GIVEN INDEX.
            printf("%d\n", dArray_getAt(&array, val1));
        }
        // IF THE QUERY IS SUM ...
        else{
            // ... THEN, GET TWO INDEX OF DYNAMIC ARRAY TO SUM UP ...
            scanf("%d %d", &val1, &val2);

            // ... AND SUM THEM UP.
            printf("%d\n", dArray_sum(&array, val1, val2));
        }
    }

    return 0;
}


/**
 * Function dArray_init
 * Description :
 *      This function is used to initialize the dynamic array.
 *
 * @param darray pointer to dynamic array to be initialized
 * */
void dArray_init(DynamicArray *darray) {
    darray->_capacity = 2u;
    darray->_size = 0u;
    darray->_arr = (int*) malloc(sizeof(int) * 2);
}

/**
 * Function dArray_isEmpty
 * Description :
 *      This function is used to check id the dynamic array is empty or not
 *
 * @param darray pointer to dynamic array to be checked the emptiness
 * @return true if size of dynamic array is 0, else false
 * */
bool dArray_isEmpty(DynamicArray *darray) {
    return darray->_size == 0;
}

/**
 * Function dArray_pushBack
 * Description :
 *      This function is used to insert an integer data to dynamic array.
 *      If the size of dynamic array after input data is greater than the capacity,
 *      then program will double the capacity of the dynamic array
 *      and reallocate memory for the dynamic array
 *
 * @param darray pointer to dynamic array to be added by the value
 * @param value data to be added to the dynamic array
 * */
void dArray_pushBack(DynamicArray *darray, int value) {
    if (darray->_size + 1 > darray->_capacity) {
        unsigned it;
        darray->_capacity *= 2;
        int *newArr = (int*) malloc(sizeof(int) * darray->_capacity);

        for (it=0; it < darray->_size; ++it)
            newArr[it] = darray->_arr[it];

        int *oldArray = darray->_arr;
        darray->_arr = newArr;
        free(oldArray);
    }
    darray->_arr[darray->_size++] = value;
}

/**
 * Function dArray_popBack
 * Description :
 *      This function is used to remove the last element of the dynamic array,
 *      by decrease the size of dynamic array, so the last element wont be accessible.
 *
 * @param darray pointer to dynamic array to be removed it's last element
 * */
void dArray_popBack(DynamicArray *darray) {
    if (!dArray_isEmpty(darray)) darray->_size--;
    else return;
}

/**
 * Function dArray_back
 * Description :
 *      This function is used to get the last element of the dynamic array.
 *
 * @param darray pointer to dynamic array to be gotten on it's last element
 * @return the last element of the dynamic array if it is not empty, else 0;
 * */
int dArray_back(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return darray->_arr[darray->_size-1];
    else return 0;
}

/**
 * Function dArray_front
 * Description :
 *      This function is used to get the first element of the dynamic array.
 *
 * @param darray pointer to dynamic array to be gotten on it's first element
 * @return the first element of the dynamic array if it is not empty, else 0;
 * */
int dArray_front(DynamicArray *darray) {
    if (!dArray_isEmpty(darray))
        return darray->_arr[0];
    else return 0;
}

/**
 * Function dArray_setAt
 * Description :
 *      This function is used to set a certain index of the dynamic array by some data
 *
 * @param darray pointer to dynamic array to be added by some data
 * @param index index of the dynamic array to be added by some value
 * @param value data to be added to the dynamic array at a certain index
 * */
void dArray_setAt(DynamicArray *darray, unsigned index, int value) {
    if (!dArray_isEmpty(darray)) {
        if (index >= darray->_size)
            darray->_arr[darray->_size-1] = value;
        else
            darray->_arr[index] = value;
    }
}

/**
 * Function dArray_getAt
 * Description :
 *      This function is used to get data of dynamic array at a certain index
 *
 * @param darray pointer to dynamic array to be gotten at a certain index
 * @param index index of the dynamic array to be gotten
 * @return data of a certain index of dynamic array or last element of it if it is not empty, else 0
 * */
int dArray_getAt(DynamicArray *darray, unsigned index) {
    if (!dArray_isEmpty(darray)) {
        if (index >= darray->_size)
            return darray->_arr[darray->_size-1];
        else
            return darray->_arr[index];
    }
    return 0;
}

/**
 * Function dArray_sum
 * Description :
 *      This function is used to sum up two data from certain index of the dynamic array
 *
 * @param darray pointer to dynamic array to
 * @param index1 index of dynamic array as first summation operand
 * @param index2 index of dynamic array as second summation operand
 * @return sum of two data from certain index of dynamic array, or 0 if any index is out of bound.
 * */
int dArray_sum(DynamicArray *darray, int index1, int index2) {
    if (!dArray_isEmpty(darray)) {
        if (index1 < darray->_size && index2 < darray->_size) {
            return darray->_arr[index1] + darray->_arr[index2];
        }
    }
    return 0;
}

/**
 * Funcion dArray_removeAt
 * Description :
 *      This function is used to remove a data from a certain index of dynamic array
 *
 * @param darray pointer to dynamic array to be removed on a certain index
 * @param index index of given dynamic array to be removed
 */
void dArray_removeAt(DynamicArray *darray, int index) {
    if(!dArray_isEmpty(darray)) {
        if(index < darray->_size) {
            for(int i = index; i+1 < darray->_size; i++) {
                darray->_arr[i] = darray->_arr[i+1];
            }
            darray->_size--;
        }
    }
}
