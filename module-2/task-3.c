/**
 * Udin Trading
 * Source : https://www.hackerrank.com/contests/sdf-m2/challenges/udin-trading
 *
 * @author Fajar Zuhri Hadiyanto
 * @version 1.0
 * @since April 14th 2021
 * */

// IMPORT PACKAGE
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * Node of tree element
 * */
typedef struct bstnode_t {
    unsigned long long key;
    struct bstnode_t \
        *left, *right;
    int nLeft, nRight;
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
int find(BST* tree, unsigned long long key);

/**
 * This function is used as a main console app
 * */
int main() {

    int nQuery, query, index;
    unsigned long long value, target;
    char mode[5];

    // PREPARE THE TREE
    BST tree;
    tree_init(&tree);

    // GET THE NUMBER OF QUERIES
    scanf("%d", &nQuery);

    // REPEAT FOR THE NUMBER OF QUERIES
    for(int i = 0; i < nQuery; i++){

        // GET THE QUERY
        scanf("%d", &query);

        // IF QUERY IS 1 ...
        if(query == 1) {

            // ... INSERT VALUE TO THE TREE
            scanf("%llu", &value);
            insert(&tree, value);

        }
        // ELSE ...
        else {

            // GET THE TARGET VALUE AND ORDER MODE (ASC OR DESC)
            scanf("%llu\n", &target);
            scanf("%s", mode);

            // FIND THE INDEX
            index = find(&tree, target);

            // IF INDEX IS NOT -1 (FOUND) ...
            if(index != -1) {

                // ... DISPLAY THAT INDEX BASED ON ORDER MODE
                printf("%d\n", strcmp(mode, "ASC") == 0 ? index : tree._size + 1 - index);

            }
            // ELSE ...
            else {

                // ... DISPLAY CERTAIN MESSAGE
                printf("Ngga ada mamang\n");
            }
        }
    }

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
    node->nLeft = 0;
    node->nRight = 0;
    node->left = NULL;
    node->right = NULL;

    if(temp == NULL) {
        tree->_root = node;
    } else {
        while (data < temp->key ? temp->left != NULL : temp->right != NULL) {
            if(data < temp->key) {
                temp->nLeft++;
                temp = temp->left;
            }
            else {
                temp->nRight++;
                temp = temp->right;
            }
        }

        if (data < temp->key) {
            temp->left = node;
            temp->nLeft++;
        }
        else {
            temp->right = node;
            temp->nRight++;
        }
    }
    tree->_size++;
}

/**
 * This function is used to find index of certain node
 *
 * @param tree tree
 * @param key key to be found in the given tree
 * @returns index of the given key if key is exist in the tree, else -1
 * */
int find(BST* tree, unsigned long long key) {
    if(tree->_root) {
        BSTNode *temp = tree->_root;
        int index = tree->_root->nLeft + 1;
        while(key < temp->key ? temp->left != NULL : key > temp->key ? temp->right != NULL : true) {
            if (key < temp->key) {
                temp = temp->left;
                index -= (temp->nRight + 1);
            } else if(key > temp->key) {
                temp = temp->right;
                index += (temp->nLeft + 1);
            } else {
                return index;
            }
        }
    }
    return -1;
}
