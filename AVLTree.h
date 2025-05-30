#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <functional> 

#include "MonHoc.h"

struct NodeAVL {
    MonHoc data;
    NodeAVL* left;
    NodeAVL* right;
    int height;
};

typedef NodeAVL* AVLTree;


NodeAVL* SearchAVL(AVLTree root, const char* key);
AVLTree InsertAVL(AVLTree root, MonHoc data);
AVLTree DeleteAVL(AVLTree root, const char* key);
void UpdateAVL(AVLTree root, const char* key, MonHoc newData);
void InorderTraversal(AVLTree root, std::function<void(MonHoc)> visit); // Sử dụng std::function
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