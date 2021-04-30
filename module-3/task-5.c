/**
 * Arkan tukang edit
 * Source : https://www.hackerrank.com/contests/sdf-m3-2021/challenges/arkan-tukang-edit
 *
 * @author Abdur Rochman
 * @editor Fajar Zuhri Hadiyanto
 * @version 1.1
 * @since April 30th 2021
 * */

// IMPORT PACKAGES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Node of avl tree
 * */
typedef struct AVLNode_t
{
    int data;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;

/**
 * Avl tree
 * */
typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
}AVL;

// PROTOTYPING
void avl_init(AVL *avl);
int _max(int a,int b);
int _getHeight(AVLNode* node);
int _getBalanceFactor(AVLNode* node);
AVLNode* _rightRotate(AVLNode* pivotNode);
AVLNode* _leftRotate(AVLNode* pivotNode);
AVLNode* _leftCaseRotate(AVLNode* node);
AVLNode* _rightCaseRotate(AVLNode* node);
AVLNode* _leftRightCaseRotate(AVLNode* node);
AVLNode* _rightLeftCaseRotate(AVLNode* node);
AVLNode* _avl_createNode(int value);
AVLNode* _search(AVLNode *root, int value);
AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value);
bool avl_find(AVL *avl, int value);
void avl_insert(AVL *avl,int value);
bool isPrime(int num);
int nextPrime(int num);
void preorder(AVLNode *temp);

/**
 * This function is used as main console application
 * */
int main() {
    // PREPARE THE TREE
    AVL tree;
    avl_init(&tree);

    // GET THE NUMBER
    int value;
    scanf("%d", &value);

    // SET THE INITIAL PRIME NUMBER TO THE LOWEST PRIME NUMBER
    int prime = 2;

    // WHILE PRIME NUMBER IS NOT GREATER THAN THE GIVEN NUMBER
    while(prime <= value) {

        // IF VALUE IS DIVISIBLE BY CURRENT PRIME NUMBER
        if (value % prime == 0) {

            // INSERT BOTH THE GIVEN NUMBER AND THE CURRENT PRIME NUMBER
            avl_insert(&tree, value);
            avl_insert(&tree, prime);

            // DIVIDE THE GIVEN NUMBER BY CURRENT PRIME NUMBER
            value /= prime;
        } else {
            // ELSE, GET THE NEXT PRIME NUMBER
            prime = nextPrime(prime);
        }
    }

    // PRINT ALL NODE VALUE PREORDEREDLY
    preorder(tree._root);

    return 0;
}

/**
 * This function is used to initialize the avl tree
 *
 * @param avl pointer to the avl tree to be initialized
 * */
void avl_init(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}

/**
 * This function is used to get maximum value of two integers
 *
 * @param a first integer
 * @param b second integer
 * @return maximum integer
 * */
int _max(int a,int b){
    return (a > b)? a : b;
}

/**
 * This function is used to get the height of the node respect to the lowest leaf
 *
 * @param node pointer to node to be looked for the height
 * @return height of the node
 * */
int _getHeight(AVLNode* node){
    if(node==NULL)
        return 0;
    return node->height;
}

/**
 * This function is used to get the difference between
 * left child height and right child height of the node
 *
 * @param node pointer to the parent node
 * @return height difference
 * */
int _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

/**
 * This function is used to rotate the avl tree to the right based on the pivot node
 *
 * @param pivotNode pointer to the pivot node
 * @return pointer to current node that replace pivot node
 * */
AVLNode* _rightRotate(AVLNode* pivotNode){

    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                           _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                            _getHeight(newParrent->right))+1;

    return newParrent;
}

/**
 * This function is used to rotate the avl tree to the left based on the pivot node
 *
 * @param pivotNode pointer to the pivot node
 * @return pointer to current node that replace pivot node
 * */
AVLNode* _leftRotate(AVLNode* pivotNode){

    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                           _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                            _getHeight(newParrent->right))+1;

    return newParrent;
}

/**
 * This function is used to rotate the avl tree in case left skewed
 *
 * @param pivotNode pointer to the pivot node
 * @return pointer to current node that replace pivot node
 * */
AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}

/**
 * This function is used to rotate the avl tree in case right skewed
 *
 * @param pivotNode pointer to the pivot node
 * @return pointer to current node that replace pivot node
 * */
AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}

/**
 * This function is used to rotate the avl tree to the left, then to the right
 *
 * @param node pointer to the pivot node
 * @return pointer to current node that replace pivot node
 * */
AVLNode* _leftRightCaseRotate(AVLNode* node){
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}

/**
 * This function is used to rotate the avl tree to the right, then to the left
 *
 * @param node pointer to the pivot node
 * @return pointer to current node that replace pivot node
 * */
AVLNode* _rightLeftCaseRotate(AVLNode* node){
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}

/**
 * This function is used to create new node of avl tree
 *
 * @param value value of the new node
 * @return pointer of the new node
 * */
AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/**
 * This function is used to search node
 *
 * @param root root node of the avl tree
 * @param value value to be searched
 * @return pointer to the node
 * */
AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
    }
    return root;
}

/**
 * This function is utility that used to insert new node to the the avl tree
 *
 * @param avl pointer to the avl tree
 * @param node pointer to temporary node
 * @param value value to be inserted to the avl tree
 * @return pointer to node
 * */
AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value){

    if(node==NULL)
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value);
    else if(value > node->data)
        node->right = _insert_AVL(avl,node->right,value);

    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right));

    int balanceFactor=_getBalanceFactor(node);

    if(balanceFactor > 1 && value < node->left->data)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value > node->left->data)
        return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value > node->right->data)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value < node->right->data)
        return _rightLeftCaseRotate(node);

    return node;
}

/**
 * This function is used to find some value in the avl tree
 *
 * @param avl pointer to the avl tree
 * @param value value to be found
 * @return true if value is found in the avl tree, else false
 * */
bool avl_find(AVL *avl, int value) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL)
        return false;

    if (temp->data == value)
        return true;
    else
        return false;
}

/**
 * This function is used to insert new node to the the avl tree
 *
 * @param avl pointer to the avl tree
 * @param value value to be inserted to the avl tree
 * */
void avl_insert(AVL *avl,int value){
    if(!avl_find(avl,value)){
        avl->_root = _insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }
}

/**
 * This function is used to check if a number is prime number or not
 *
 * @param num number to be checked for the prime number status
 * @return true if the number is a prime number, else false
 * */
bool isPrime(int num) {
    if (num == 1) return false;
    if (num == 2) return true;

    for (int i = 2; i < (int) sqrt(num) + 1; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

/**
 * This function is used to get the next prime number of the given number
 *
 * @param num number to be looked for the next prime number
 * @return number which is the next prime number of the given number
 * */
int nextPrime(int num) {
    num++;
    if (num > 2) {
        while(!isPrime(num)) {
            num += (1 + (num % 2));
        }
        return num;
    } else {
        return num + 1;
    }
}

/**
 * This function is used to traverse and print all node value of the tree preorderedly
 *
 * @param temp temporary traverser node
 * */
void preorder(AVLNode *temp) {
    if (temp) {
        printf("%d ", temp->data);
        preorder(temp->left);
        preorder(temp->right);
    }
}



