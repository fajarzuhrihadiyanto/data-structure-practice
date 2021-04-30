/**
 * Hitung Kolom
 * Source : https://www.hackerrank.com/contests/sdf-m3-2021/challenges/hitung-kolom
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
void inorder(AVLNode *temp, int *result);

/**
 * This function is used as main console application
 * */
int main() {
    int nQuery, value;
    char query[10];

    // PREPARE THE TREE
    AVL tree;
    avl_init(&tree);

    // GET THE NUMBER OF QUERIES
    scanf("%d", &nQuery);

    // SET THE RESULT MEMORY AND IT'S SIZE, AND ALSO MIDDLE INDEX OF RESULT ARRAY
    int *result = (int*) malloc(nQuery * sizeof(int));
    int midIndex = nQuery/2;

    // REPEAT FOR THE NUMBER OF QUERIES
    for(int i = 0; i < nQuery; i++) {

        // GET THE QUERY
        scanf("%s", query);

        if (strcmp(query, "insert") == 0) {

            // IF QUERY IS "insert", GET THE VALUE TO BE INSERTED TO THE TREE
            scanf("%d", &value);
            avl_insert(&tree, value);
        } else {

            // IF QUERY IS "print"...

            // SET ALL VALUES OF RESULT TO -1
            memset(result, -1, nQuery * sizeof(int));

            // THEN, GET THE SUM OF EACH COLUMN
            // WITH THE ROOT IN THE MIDDLE COLUMN/INDEX
            inorder(tree._root, result + midIndex);

            // THEN FIND THE NON -1 VALUE OF THE RESULT TO BE DISPLAYED
            for (int i = 0; i < nQuery; ++i) {
                if (*(result + i) != -1) {
                    printf("%d ", *(result + i));
                }
            }
            printf("\n");
        }
    }

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
 * This function is used to set value of each column
 * of the tree to sum of corresponding node
 *
 * @param temp pointer to temporary root node
 * @param result pointer to result value
 * @since 1.1
 * */
void inorder(AVLNode *temp, int *result) {
    if (temp) {
        inorder(temp->left, result-1);
        *result = *result == -1 ? *result + temp->data + 1 : *result + temp->data;
        inorder(temp->right, result+1);
    }
}
