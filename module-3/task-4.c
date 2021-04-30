/**
 * Kosimp dan Tugas Magang
 * Source : https://www.hackerrank.com/contests/sdf-m3-2021/challenges/kosimp-dan-tugas-magang
 *
 * @author Abdur Rochman
 * @editor Fajar Zuhri Hadiyanto
 * @version 1.1
 * @since April 30th 2021
 * */

// IMPORT PACKAGES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Node of avl tree
 * */
typedef struct AVLNode_t
{
    char *data;
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
AVLNode* _avl_createNode(char *value);
AVLNode* _search(AVLNode *root, char *value);
AVLNode* _insert_AVL(AVL *avl,AVLNode* node,char *value);
bool avl_find(AVL *avl, char *value);
void avl_insert(AVL *avl, char *value);
void inorder(AVLNode *temp, int *index);
void inorder2(AVLNode *temp, int *index);

/**
 * This function is used as main console application
 * */
int main() {
    char name[20001];

    // PREPARE THE TREE
    AVL tree;
    avl_init(&tree);

    // WHILE STILL GET AN INPUT (NOT EOF)
    while(gets(name) && name[0] != EOF){

        // BORROW MEMORY TO SPLIT UP NAMES IN ONE LINE
        char *text = (char*) malloc(20 * sizeof(char));
        memset(text, '\0', sizeof(char) * 20);

        // VAR j FOR NAME INDEX
        int j = 0;

        // REPEAT FOR EVERY CHARACTER IN THE LINE
        for (int i = 0; i < strlen(name); ++i) {

            // IF THE CHARACTER IS NOT EMPTY ...
            if (name[i] != ' ' && name[i] != '\000') {
                // ASSIGN THE CHARACTER WITH SPECIFIC
                // INDEX INTO TEMPORARY VARIABLE
                *(text + j) = name[i];
                j++;
            }
            // ELSE, CHECK IF INDEX IS NOT 0 AND THE TEXT IS NOT EMPTY
            else if (j != 0 && *text != '\0') {
                // THEN, INSERT THE NAME INTO THE TREE
                avl_insert(&tree, text);

                // THEN, RESET THE TEMPORARY VARIABLE AND THE INDEX
                memset(text, '\0', sizeof(char) * 20);
                j = 0;
            }
        }

        if (*text != '\0') {
            // INSERT THE LAST WORD FROM THE LINE
            avl_insert(&tree, text);

            // THEN, RESET THE TEMPORARY VARIABLE
            memset(text, '\0', sizeof(char) * 20);
        }
    }

    // INITIALIZE THE INDEX TO 1
    int index = 1;

    // PRINT THE TREE NODE ORDEREDLY
    // WITH A SPECIFIC FORMAT
    inorder(tree._root, &index);
    inorder2(tree._root, &index);
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
AVLNode* _avl_createNode(char *value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = (char *) malloc(20 * sizeof(char));
    memcpy(newNode->data, value, 20 * sizeof(char));
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
AVLNode* _search(AVLNode *root, char *value) {
    while (root != NULL) {
        if (strcmp(value, root->data) < 0)
            root = root->left;
        else if (strcmp(value, root->data) > 0)
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
AVLNode* _insert_AVL(AVL *avl,AVLNode* node,char *value){

    if(node==NULL)
        return _avl_createNode(value);
    if(strcmp(value, node->data) < 0)
        node->left = _insert_AVL(avl,node->left,value);
    else if(strcmp(value, node->data) > 0)
        node->right = _insert_AVL(avl,node->right,value);

    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right));

    int balanceFactor=_getBalanceFactor(node);

    if(balanceFactor > 1 && strcmp(value, node->left->data) < 0)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && strcmp(value, node->left->data) > 0)
        return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && strcmp(value, node->right->data) > 0)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && strcmp(value, node->right->data) < 0)
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
bool avl_find(AVL *avl, char *value) {
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
void avl_insert(AVL *avl,char *value){
    if(!avl_find(avl,value)){
        avl->_root = _insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }
}

/**
 * This function is used to print all tree values orderedly
 * with a certain format.
 *
 * @param temp temporary node
 * @param index pointer to int for indexing
 * */
void inorder(AVLNode *temp, int *index) {
    if (temp) {
        inorder(temp->left, index);
        printf("%d. %s\n", (*index)++, temp->data);
        inorder(temp->right, index);
    }
}

/**
 * This function is used to print all tree values orderedly
 * with a certain format.
 *
 * @param temp temporary node
 * @param index pointer to int for indexing
 * */
void inorder2(AVLNode *temp, int *index) {
    if (temp) {
        inorder2(temp->left, index);
        printf("%s", temp->data);
        if ((*index)-- != 1) printf("_");
        inorder2(temp->right, index);
    }
}
