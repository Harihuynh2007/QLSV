#include "AVLTree.h"
#include "MonHoc.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <new>


int Height(NodeAVL* node) {
    return node ? node->height : 0;
}

int Max(int a, int b) {
    return (a > b) ? a : b;
}

NodeAVL* RotateRight(NodeAVL* y) {
    NodeAVL* x = y->left;
    NodeAVL* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = Max(Height(y->left), Height(y->right)) + 1;
    x->height = Max(Height(x->left), Height(x->right)) + 1;

    return x;
}

NodeAVL* RotateLeft(NodeAVL* x) {
    NodeAVL* y = x->right;
    NodeAVL* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = Max(Height(x->left), Height(x->right)) + 1;
    y->height = Max(Height(y->left), Height(y->right)) + 1;

    return y;
}

int GetBalance(NodeAVL* node) {
    return node ? Height(node->left) - Height(node->right) : 0;
}

NodeAVL* MinValueNode(NodeAVL* node) {
    NodeAVL* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}


NodeAVL* SearchAVL(AVLTree root, const char* key) {
    if (root == NULL || strcmp(root->data.MAMH, key) == 0)
        return root;

    if (strcmp(key, root->data.MAMH) < 0)
        return SearchAVL(root->left, key);
    return SearchAVL(root->right, key);
}


AVLTree InsertAVL(AVLTree root, MonHoc data) {
    if (root == NULL) {
        NodeAVL* newNode = new (std::nothrow) NodeAVL;
        if (newNode == NULL) {
            std::cerr << "Loi: Khong du bo nho de them node!\n";
            return NULL;
        }
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (strcmp(data.MAMH, root->data.MAMH) < 0)
        root->left = InsertAVL(root->left, data);
    else if (strcmp(data.MAMH, root->data.MAMH) > 0)
        root->right = InsertAVL(root->right, data);
    else {
        std::cerr << "Loi: Ma mon hoc '" << data.MAMH << "' da ton tai!\n";
        return root;
    }

    root->height = 1 + Max(Height(root->left), Height(root->right));

    int balance = GetBalance(root);

    if (balance > 1 && strcmp(data.MAMH, root->left->data.MAMH) < 0)
        return RotateRight(root);

    if (balance < -1 && strcmp(data.MAMH, root->right->data.MAMH) > 0)
        return RotateLeft(root);

    if (balance > 1 && strcmp(data.MAMH, root->left->data.MAMH) > 0) {
        root->left = RotateLeft(root->left);
        return RotateRight(root);
    }

    if (balance < -1 && strcmp(data.MAMH, root->right->data.MAMH) < 0) {
        root->right = RotateRight(root->right);
        return RotateLeft(root);
    }

    return root;
}


AVLTree DeleteAVL(AVLTree root, const char* key) {
    if (root == NULL) return root;

    if (strcmp(key, root->data.MAMH) < 0)
        root->left = DeleteAVL(root->left, key);
    else if (strcmp(key, root->data.MAMH) > 0)
        root->right = DeleteAVL(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            NodeAVL* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            delete temp;
        } else {
            NodeAVL* temp = MinValueNode(root->right);
            root->data = temp->data;
            root->right = DeleteAVL(root->right, temp->data.MAMH);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + Max(Height(root->left), Height(root->right));

    int balance = GetBalance(root);

    if (balance > 1 && GetBalance(root->left) >= 0)
        return RotateRight(root);

    if (balance > 1 && GetBalance(root->left) < 0) {
        root->left = RotateLeft(root->left);
        return RotateRight(root);
    }

    if (balance < -1 && GetBalance(root->right) <= 0)
        return RotateLeft(root);

    if (balance < -1 && GetBalance(root->right) > 0) {
        root->right = RotateRight(root->right);
        return RotateLeft(root);
    }

    return root;
}


void UpdateAVL(AVLTree root, const char* key, MonHoc newData) {
    NodeAVL* node = SearchAVL(root, key);
    if (node != NULL) {
        strcpy(node->data.TENMH, newData.TENMH);
        node->data.STCLT = newData.STCLT;
        node->data.STCTH = newData.STCTH;
        std::cout << "Da cap nhat mon hoc '" << key << "'.\n";
    } else {
        std::cerr << "Loi: Khong tim thay mon hoc '" << key << "'.\n";
    }
}


void InorderTraversal(AVLTree root, std::function<void(MonHoc)> visit) {
    if (root != NULL) {
        InorderTraversal(root->left, visit);
        visit(root->data);
        InorderTraversal(root->right, visit);
    }
}


void FreeAVL(AVLTree &root) {
    if (root != NULL) {
        FreeAVL(root->left);
        FreeAVL(root->right);
        delete root;
        root = NULL;
    }
}


int CountNodes(AVLTree root) {
    if (root == NULL) return 0;
    return 1 + CountNodes(root->left) + CountNodes(root->right);
}