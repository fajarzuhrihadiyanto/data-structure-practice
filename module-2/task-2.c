/**
 * Kosimp dan Keluarga Santoso
 * Source : https://www.hackerrank.com/contests/sdf-m2/challenges/kosimp-dan-keluarga-santoso
 *
 * @author Fajar Zuhri Hadiyanto
 * @version 1.0
 * @since April 14th 2021
 * */

// IMPORT PACKAGES
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * Node of tree element
 * */
typedef struct bstnode_t {
    char key[21];
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
void insert(BST* tree, char data[]);
void find_child(BSTNode *root, char value[]);
void find_parent(BSTNode *root, char value[]);

/**
 * This function is used as a main console app
 * */
int main() {

    int nElems, nQuery;
    char name[21], query[10];

    // PREPARE THE TREE
    BST tree;
    tree_init(&tree);

    // GET THE NUMBER OF ELEMENTS AND QUERIES
    scanf("%d %d", &nElems, &nQuery);

    // INSERT ALL TREE ELEMENTS
    for(int i = 0; i < nElems; i++) {
        scanf("%s", name);
        insert(&tree, name);
    }

    // REPEAT FOR THE NUMBER OF QUERIES
    for(int i = 0; i < nQuery; i++) {

        // INSERT QUERY AND NAME
        scanf("%s", query);
        scanf("%s", name);

        // IF QUERY IS "anak" ...
        if(strcmp(query, "anak") == 0) {

            // ... THEN FIND THE CHILDREN OF THE GIVEN NAME
            find_child(tree._root, name);
        } else {

            // ... ELSE CHECK IF THE GIVEN NAME IS THE ROOT NODE
            if(strcmp(name, tree._root->key) == 0) {

                // IF YES, DISPLAY THE MESSAGE
                printf("Aku adalah sesepuh keluarga Santoso\n");

            } else {

                // IF NOT, FIND THE PARENT OF THE GIVEN NAME
                find_parent(tree._root, name);
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
void insert(BST* tree, char data[]) {

    BSTNode* temp = tree->_root;

    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    strcpy(node->key, data);
    node->left = NULL;
    node->right = NULL;

    if(temp == NULL) {
        tree->_root = node;
    } else {
        while (strcmp(data, temp->key) >= 0 ? temp->left != NULL : temp->right != NULL) {
            if(strcmp(data, temp->key) >= 0) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }

        if (strcmp(data, temp->key) >= 0) temp->left = node;
        else temp->right = node;
    }
    tree->_size++;
}

/**
 * This function is used to find child of certain name
 * then display them if found
 *
 * @param root root node of a tree
 * @param value name to be looked for its children
 * */
void find_child(BSTNode *root, char value[]) {
    if(root != NULL) {
        while (strcmp(value, root->key) > 0 ? root->left != NULL : strcmp(value, root->key) < 0 ? root->right != NULL : true) {
            if (strcmp(value, root->key) > 0) {
                root = root->left;
            } else if (strcmp(value, root->key) < 0) {
                root = root->right;
            } else {
                if(!(root->right) && !(root->left)) {
                    printf("diManakah Anak-aNakkuu ;(\n");
                } else {
                    printf("%s %s\n", root->left ? root->left->key : "-", root->right ? root->right->key : "-");
                }
                return;
            }
        }
    }
}

/**
 * This function is used to find child of certain name
 * then display them if found
 *
 * @param root root node of a tree
 * @param value name to be looked for its parent
 * */
void find_parent(BSTNode *root, char value[]) {
    BSTNode *child1 = root->left;
    BSTNode *child2 = root->right;

    while(strcmp(value, root->key) > 0 ? child1 != NULL : child2 != NULL) {
        if(strcmp(value, root->key) > 0) {

            if(strcmp(value, child1->key) == 0) {
                printf("%s\n", root->key);
                break;
            }

            root = root->left;
            child2 = child1 ? child1->right : NULL;
            child1 = child1 ? child1->left : NULL;
        } else if (strcmp(value, root->key) < 0) {
            if(strcmp(value, child2->key) == 0) {
                printf("%s\n", root->key);
                break;
            }
            root = root->right;
            child1 = child2 ? child2->left : NULL;
            child2 = child2 ? child2->right : NULL;
        }
    }
}
