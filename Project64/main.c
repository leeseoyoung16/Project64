#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_ELEMENT 200

typedef struct TreeNode
{
    char ch;
    int weight;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

typedef struct {
    TreeNode* ptree;
    char ch;
    int key;
}element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
}HeapType;

HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
    h->heap_size = 0;
}

void print_heap(HeapType* h) { //���� ���
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

void insert_max_heap(HeapType* h, element item) { //����
    int i;
    i = ++(h->heap_size);
    h->heap[i] = item;

    while ((i != 1) && (item.key > h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        h->heap[i / 2] = item;
        i /= 2;

    }

}


element delete_max_heap(HeapType* h) { //����
    int parent, child;
    element item;


    item = h->heap[1]; //�ֻ��� ���
    h->heap[1] = h->heap[(h->heap_size)--]; //�ֻ��� ��� ���� -> ������ ��带 �ֻ��� ���� ������Ʈ
    parent = 1;
    child = 2; //�ڽĳ��


    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
            child++;
        } //���� �ڽĺ��� ������ �ڽ��� ũ�� �ڽ� ������Ʈ
        if (h->heap[parent].key >= h->heap[child].key) break; //�θ� �ڽĳ�庸�� ũ�ų� ������ break

        element tmp = h->heap[parent]; //�θ� ��� �ű�
        h->heap[parent] = h->heap[child]; //�ڽĳ�尡 �� ũ�� �ڽ� ���� �θ� ��� ��ġ �ٲ�
        h->heap[child] = tmp;
        parent = child;
        child *= 2;

    }
    return item;
}

TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

void destroy_tree(TreeNode* root) {
    if (root == NULL) return;
    destory_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right);
}

void print_codes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1;
    }
}