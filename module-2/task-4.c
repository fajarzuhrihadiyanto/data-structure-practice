/**
 * Bantu Holen
 * Source : https://www.hackerrank.com/contests/sdf-m2/challenges/bantu-holen
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
#include <math.h>

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
void decToHex(char* result, int num);
void trace(BSTNode *root, int key, bool *find);

/**
 * This function is used as a main console app
 * */
int main(){

    int data, clue;
    bool find = false;

    // PREPARE THE TREE
    BST tree;
    tree_init(&tree);

    // GET THE DATASETS
    for(scanf("%d", &data); data != -1; scanf("%d", &data)) {
        insert(&tree, data);
    }

    char charClue[6];
    gets(charClue);

    // WHILE GET THE CLUE LINE ...
    while(gets(charClue) && charClue[0] != '\0'){

        // CONVERT CLUE TO INTEGER
        clue = atoi(charClue);

        // IF CLUE IS THE ROOT OF THE TREE ...
        if(clue == tree._root->key) {

            // ... THEN DISPLAY CERTAIN MESSAGE
            if(find) printf("\n");
            printf("Clue nya ga guna\n");

        }
        // ELSE ...
        else {

            // ... TRACE THE CLUE IN THE TREE
            trace(tree._root, clue, &find);
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
        while (data < temp->key ? temp->left != NULL : data > temp->key ? temp->right != NULL : false) {
            if(data < temp->key) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }

        if (data < temp->key) {
            temp->left = node;
            tree->_size++;
        }
        else if(data > temp->key) {
            temp->right = node;
            tree->_size++;
        }
    }
}

/**
 * This function is used to convert decimal number
 * to hexadecimal number every 2 digit
 *
 * @param result address of result
 * @param num number to be converted
 * */
void decToHex(char* result, int num) {
    if(num == 10000) {
        strcpy(result, "a00");
        return;
    }

    char temp[6];
    int numPart, len, quotient, mod;
    sprintf(temp, "%d", num);
    len = strlen(temp);

    for(int i = num; i >= 10; i %= (int) pow(10, len)) {
        len -= 2;
        numPart = i / (int) pow(10, len);
        quotient = numPart / 16;
        mod = numPart % 16;
        if(quotient > 0) {
            char x[2];
            sprintf(x, "%d", quotient);
            strcpy(result + strlen(result), x);
        }

        if(mod < 10) {
            char x[2];
            sprintf(x, "%d", mod);
            strcpy(result + strlen(result), x);
        } else {
            if(mod == 10) {
                strcat(result, "a");
            } else if(mod == 11) {
                strcat(result, "b");
            } else if(mod == 12) {
                strcat(result, "c");
            } else if(mod == 13) {
                strcat(result, "d");
            } else if(mod == 14) {
                strcat(result, "e");
            } else {
                strcat(result, "f");
            }
        }
    }

    if (len > 0){
        char x[2];
        sprintf(x, "%d", num % 10);
        strcpy(result + strlen(result), x);
    }
}

/**
 * This function is used to find key in the tree
 * and display converted parent upward
 *
 * @param root root node of the tree
 * @param key key to be found
 * @param find flag to indicate of the given key is found or not
 * */
void trace(BSTNode *root, int key, bool *find) {
    if(root) {
        if(root->key > key) {
            trace(root->left, key, find);
        } else if(root->key < key) {
            trace(root->right, key, find);
        } else {
            *find = true;
            return;
        }

        if(root->key != key && *find){
            char res[6] = "";
            decToHex(res, root->key);
            printf("%s", res);
        }
    } else {
        if(*find) printf("\n");
        *find = false;
        printf("Clue nya ga guna\n");
        return;
    }

}
