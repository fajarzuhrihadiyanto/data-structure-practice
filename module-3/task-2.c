/**
 * Petak Umpet
 * Source : https://www.hackerrank.com/contests/sdf-m3-2021/challenges/petak-umpet
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
void letsFindOut(AVLNode *current, AVLNode *temp, int target, int sum, bool *isFind, bool isTurning);

/**
 * This function is used as main console application
 * */
int main() {
    // PREPARE THE TREE
    AVL tree;
    avl_init(&tree);

    // GET THE NUMBER OF QUERIES
    int nQuery;
    scanf("%d", &nQuery);

    // REPEAT FOR THE NUMBER OF QUERIES
    for (int i = 0; i < nQuery; ++i) {

        // GET THE QUERY AND VALUE
        int query, value;
        scanf("%d %d", &query, &value);

        if (query == 1) {
            // IF THE QUERY IS 1, THEN INSERT VALUE TO THE TREE
            avl_insert(&tree, value);
        } else {
            // IF THE QUERY IS 2 ...

            // INITIALIZE THE POSSIBILITY TO FALSE
            bool isFind = false;

            if (tree._size <= 1) {
                // IF SIZE OF THE TREE IS LOWER OR EQUAL TO 1, JUST SKIP
            } else if (avl_find(&tree, value)) {
                // IF THE VALUE IS FOUND ON THE TREE AND THE SIZE IS GREATER THAN 1
                // THAT IS ABSOLUTELY POSSIBLE TO FIND THE NEEDED PATH
                isFind = true;
            } else {
                // ELSE, JUST FIND OUT WITH THE UTILITY FUNCTION
                letsFindOut(tree._root, tree._root, value, 0, &isFind, false);
            }

            if (!isFind) {
                // IF THE PATH IS NOT FOUND, PRINT A CERTAIN MESSAGE
                printf("Yahh Petot kAbur :(\n");
            } else {
                // ELSE, ALSO PRINT A CERTAIN MESSAGE
                printf("HehE Boy, AkAn KutemUkan kaU Petot\n");
            }
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
 * This function is used to find if there is any possible path
 * that satisfy some rules defined in the task description.
 * This function will change the value of isFind variable defined
 * outside this function depends if the needed path is found or not.
 *
 * @param current temporary node that move as one of the end path
 * @param temp another temporary node that move as another end path
 * @param target target value as a sum of the path node
 * @param sum current sum of the node in a certain path
 * @param isFind pointer to boolean value that define the possibility of the needed path
 * @param isTurning parameter to recognize if the path is turning from a certain pivot node to the opposite child
 * */
void letsFindOut(AVLNode *current, AVLNode *temp, int target, int sum, bool *isFind, bool isTurning) {
    if (target == sum) {
        *isFind = true;
    } else if (!isTurning) {
        if (current) {
            if ((current->left || current->right)
                || (temp->left && temp->right)) {

                sum += current->data;
                if (sum == target) {
                    *isFind = true;
                    return;
                }

                if (sum > target) return;

                if (!(*isFind)) letsFindOut(current->left, temp, target, sum, isFind, false);
                if (!(*isFind)) letsFindOut(current->right, temp, target, sum, isFind, false);

                if (temp->data > current->data) {
                    if (!(*isFind)) letsFindOut(current, temp->right, target, sum, isFind, true);
                } else if (temp->data < current->data) {
                    if (!(*isFind)) letsFindOut(current, temp->left, target, sum, isFind, true);
                }

                if (!(*isFind)) letsFindOut(current->left, current->left, target, 0, isFind, false);
                if (!(*isFind)) letsFindOut(current->right, current->right, target, 0, isFind, false);
            }
        }
    } else {
        if (temp) {
            if ((current->left || current->right)
                || (temp->left || temp->right)) {

                sum += temp->data;

                if (sum == target) {
                    *isFind = true;
                    return;
                }

                if (sum > target) return;

                if (!(*isFind)) letsFindOut(current, temp->left, target, sum, isFind, true);
                if (!(*isFind)) letsFindOut(current, temp->right, target, sum, isFind, true);
            }
        }
    }
}
