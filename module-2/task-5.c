/**
 * DAS 1
 * Source : https://www.hackerrank.com/contests/sdf-m2/challenges/das-1
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
    int key;
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
int find(BSTNode* root, int key);
void insert(BST* tree, int data);
void __inorder(BSTNode *root, int *num, int target);

/**
 * This function is used as a main console app
 * */
int main() {

    int nQuery, value, index = 1, target;

    // PREPARE THE TREE
    BST tree;
    tree_init(&tree);

    // GET THE NUMBER OF QUERIES
    scanf("%d", &nQuery);

    // INSERT ELEMENT TO THE TREE
    for(int i = 0; i < nQuery; i++){
        scanf("%d", &value);
        insert(&tree, value);
    }

    // GET THE TARGET INDEX
    scanf("%d", &target);

    // TRAVERSE THE TREE
    __inorder(tree._root, &index, target);

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
 * This function is used to find element in a tree
 *
 * @param root root to be looked for it's element
 * @param key key value to be looked for
 * @return level of the found key
 * */
int find(BSTNode* root, int key) {
    int level = 0;

    if (root != NULL) {
        while (key < root->key ? root->left != NULL : key == root->key || root->right != NULL) {
            level++;

            if (key < root->key) {
                root = root->left;
            } else if (key > root->key) {
                root = root->right;
            } else if (find(root->right, key) != -1) {
                root = root->right;
            } else {
                return level;
            }
        }
    }
    return -1;
}

/**
 * This function is used to insert node to a tree.
 *
 * @param root root node of a tree
 * @param data value to be added to a tree
 * */
void insert(BST* tree, int data) {

    BSTNode* temp = tree->_root;

    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->key = data;
    node->left = NULL;
    node->right = NULL;

    if(temp == NULL) {
        tree->_root = node;
    } else {
        while (data < temp->key ? temp->left != NULL : temp->right != NULL) {
            if(data < temp->key) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }

        if (data < temp->key) temp->left = node;
        else temp->right = node;
    }
    tree->_size++;
}

/**
 * This function is used to get certain value in the tree
 * with the given index, with inorder traversal method
 *
 * @param root root node of the tree
 * @param num address of iteration index variable
 * @param target target index
 * */
void __inorder(BSTNode *root, int *num, int target) {
    if (root && *num != -1) {
        __inorder(root->left, num, target);
        if(*num == target) {
            printf("%d\n", root->key);
            *num = -1;
            return;
        } else if(*num != -1) {
            (*num)++;
        }
        __inorder(root->right, num, target);
    }
}
