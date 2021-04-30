/**
 * Kosimp dan Umur Keluarga Santoso
 * Source : https://www.hackerrank.com/contests/sdf-m3-2021/challenges/kosimp-dan-umur-keluarga-santoso
 *
 * @author Abdur Rochman
 * @editor Fajar Zuhri Hadiyanto
 * @version 1.1
 * @since April 30th 2021
 * */

// IMPORT PACKAGES
#include <stdio.h>
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
void find(AVLNode *node, int target, bool *flag, int *sum);

/**
 * This function is used as main console application
 * */
int main() {
    // PREPARE THE TREE
    AVL tree;
    avl_init(&tree);

    // GET THE NUMBER OF FAMILY MEMBERS AND THE NUMBER OF QUERIES
    int nFam, nQuery;
    scanf("%d %d", &nFam, &nQuery);

    // INSERT ALL FAMILY MEMBER
    for (int i = 0; i < nFam; ++i) {
        int value;
        scanf("%d", &value);

        avl_insert(&tree, value);
    }

    // REPEAT FOR THE NUMBER OF QUERIES
    for (int i = 0; i < nQuery; i++) {

        // GET THE VALUE
        int value;
        scanf("%d", &value);

        // IF THE GIVEN VALUE IS THE ROOT OF THE TREE
        if (tree._root->data == value) {
            // JUST PRINT A CERTAIN MESSAGE
            printf("Aku adalah Kepala Keluarga Santoso\n");
            continue;
        }

        // INITIALIZE SUM TO 0, AND FOUND STATUS TO FALSE
        int sum = 0;
        bool isFind = false;

        // FIND THE PARENT OF THE VALUE
        // AND IT'S SIBLING IN THE TREE
        find(tree._root, value, &isFind, &sum);

        // IF THE SUM STILL 0
        if (sum == 0) {
            // THEN PRINT A CERTAIN VALUE
            printf("Aku Bukan Anggota Keluarga Santoso\n");
        } else {
            // ELSE, PRINT THE SUM VALUE
            printf("%d\n", sum);
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
 * This function is used to find a parent of target and it's sibling
 * then sum up their values, if the parent does not have a sibling
 * then just get the value of the parent
 *
 * @param node temporary tracer node to get the target node
 * @param target target value to be looked for the parent and it's sibling
 * @param flag pointer to some flag that help program to determine which behaviour to act
 * @param sum pointer to sum value
 * */
void find(AVLNode *node, int target, bool *flag, int *sum) {
    if (node) {

        if (!(*flag) && *sum == 0)
            if (target < node->data)
                find(node->left, target, flag, sum);

        if (!(*flag) && *sum == 0)
            if (target > node->data)
                find(node->right, target, flag, sum);

        if (!(*flag) && *sum > 0) return;

        if (*flag && *sum > 0) {
            if (*sum == node->left->data && node->right) {
                *sum -= node->right->data;
                *sum *= *sum > 0 ? 1 : -1;
            }
            if (*sum == node->right->data && node->left) {
                *sum -= node->left->data;
                *sum *= *sum > 0 ? 1 : -1;
            }
            *flag = false;
            return;
        }

        if (*flag) {
            *sum += node->data;
            return;
        }

        if (node->data == target) *flag = true;

        return;
    }
}