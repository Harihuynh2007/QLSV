#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct MonHoc {
    char MAMH[11];
    char TENMH[51];
    int STCLT;
    int STCTH;
};

struct NodeAVL {
    MonHoc data;
    NodeAVL* left;
    NodeAVL* right;
    int height;
};

typedef NodeAVL* AVLTree;

// Ham quan ly cay AVL
NodeAVL* SearchAVL(AVLTree root, const char* key);
AVLTree InsertAVL(AVLTree root, MonHoc data);
AVLTree DeleteAVL(AVLTree root, const char* key);
void UpdateAVL(AVLTree root, const char* key, MonHoc newData);
void InorderTraversal(AVLTree root, void (*visit)(MonHoc));
void FreeAVL(AVLTree &root);
int CountNodes(AVLTree root);

// Ham ho tro
int Height(NodeAVL* node);
int Max(int a, int b);
NodeAVL* RotateRight(NodeAVL* y);
NodeAVL* RotateLeft(NodeAVL* x);
int GetBalance(NodeAVL* node);
NodeAVL* MinValueNode(NodeAVL* node);

#endif // AVLTREE_H