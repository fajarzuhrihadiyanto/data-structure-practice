/**
 * Salin Salinan Kuy!
 * Source : https://www.hackerrank.com/contests/sdf-m2/challenges/salin-salinan-kuy
 *
 * @author Fajar Zuhri Hadiyanto
 * @version 1.0
 * @since April 14th 2021
 * */

// IMPORT PACKAGES
#include <stdio.h>
#include <string.h>
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
void insert(BST* tree, int data);
void __inorder(BSTNode *root, int *num, int target);
void __postorder(BSTNode *root, int *num, int target);
void __preorder(BSTNode *root, int *num, int target);

/**
 * This function is used as a main console app
 * */
int main() {

    int nQuery, query, value, index;
    char mode[10];

    // PREPARE THE TREE
    BST tree;
    tree_init(&tree);

    // GET THE NUMBER OF QUERIES
    scanf("%d", &nQuery);

    // REPEAT FOR THE NUMBER OF QUERIES
    for(int i = 0; i < nQuery; i++){

        // GET THE QUERY
        scanf("%d", &query);

        // IF THE QUERY IS 1 ...
        if(query == 1) {

            // ... THEN INSERT VALUE TO THE TREE
            scanf("%d", &value);
            insert(&tree, value);

        }
        // ELSE ...
        else {

            // ... GET TRAVERSING MODE AND TARGET INDEX
            scanf("%s", mode);
            scanf("%d", &value);

            // INITIALIZE INDEX
            index = 1;

            // EXECUTE CORRESPONDING TRAVERSING FUNCTION
            if(strcmp(mode, "inorder") == 0) {
                __inorder(tree._root, &index, value);
            } else if(strcmp(mode, "preorder") == 0) {
                __preorder(tree._root, &index, value);
            } else {
                __postorder(tree._root, &index, value);
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

/**
 * This function is used to get certain value in the tree
 * with the given index, with postorder traversal method
 *
 * @param root root node of the tree
 * @param num address of iteration index variable
 * @param target target index
 * */
void __postorder(BSTNode *root, int *num, int target) {
    if (root && *num != -1) {
        __postorder(root->left, num, target);
        __postorder(root->right, num, target);
        if(*num == target) {
            printf("%d\n", root->key);
            *num = -1;
            return;
        } else if(*num != -1) {
            (*num)++;
        }
    }
}

/**
 * This function is used to get certain value in the tree
 * with the given index, with preorder traversal method
 *
 * @param root root node of the tree
 * @param num address of iteration index variable
 * @param target target index
 * */
void __preorder(BSTNode *root, int *num, int target) {
    if (root && *num != -1) {
        if(*num == target) {
            printf("%d\n", root->key);
            *num = -1;
            return;
        } else if(*num != -1) {
            (*num)++;
        }
        __preorder(root->left, num, target);
        __preorder(root->right, num, target);
    }
}
