/**
 * Daun Muda si Cantok
 * Source : https://www.hackerrank.com/contests/sdf-m2/challenges/daun-muda-si-cantok
 *
 * @author Fajar Zuhri Hadiyanto
 * @version 1.0
 * @since April 14th 2021
 * */

// IMPORT PACKAGES
#include <stdio.h>
#include <stdlib.h>

/**
 * Node of tree element
 * */
typedef struct bstnode_t {
    unsigned long long key;
    struct bstnode_t \
        *left, *right;
} BSTNode;

/**
 * Tree element
 * */
typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

// PROTOTYPING
void tree_init(BST* tree);
void insert(BST* tree, unsigned long long data);
void __preorder(BSTNode *root, unsigned long long *num);

/**
 * This function is used as a main console app
 * */
int main() {

    int nQuery;
    unsigned long long num = 0, value;

    // PREPARE THE TREE
    BST tree;
    tree_init(&tree);

    // GET THE NUMBER OF QUERY
    scanf("%d", &nQuery);

    // REPEAT FOR THE NUMBER OF QUERY
    for(int i = 0; i < nQuery; i++){

        // GET THE VALUE OF NODE
        scanf("%llu", &value);

        // INSERT NODE TO THE TREE
        insert(&tree, value);
    }

    // PREORDER TRAVERSING
    __preorder(tree._root, &num);

    // DISPLAY SUM OF ALL VALUE OF LEAF NODE
    printf("%llu", num);

    return 0;
}

/**
 * This function is used to initialize the tree
 *
 * @param tree tree to be initialized
 */
void tree_init(BST* tree) {
    tree->_root = NULL;
    tree->_size = 0;
}

/**
 * This function is used to insert node to a tree.
 *
 * @param tree tree
 * @param data value to be added to a tree
 * */
void insert(BST* tree, unsigned long long data) {

    BSTNode* temp = tree->_root;

    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->key = data;
    node->left = NULL;
    node->right = NULL;

    if(temp == NULL) {
        tree->_root = node;
    } else {
        while (data < temp->key ? temp->left != NULL : temp->right != NULL ) {
            if(data < temp->key) {
                temp = temp->left;
            }
            else if (data > temp->key){
                temp = temp->right;
            } else {
                break;
            }
        }

        if (data < temp->key) {
            temp->left = node;
            tree->_size++;
        }
        else if (data > temp->key){
            temp->right = node;
            tree->_size++;
        }
    }
}

/**
 * This function is used to traverse the tree and
 * get all values of the leaf node using preorder
 *
 * @param root root of the tree
 * @param num address of variable to contain sum of the value of leaf node
 * */
void __preorder(BSTNode *root, unsigned long long *num) {
    if (root) {
        if(root->left == NULL && root->right == NULL) {
            *num += root->key;
        }
        __preorder(root->left, num);
        __preorder(root->right, num);
    }
}
