#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct TreeNode {
    char ch;
    int weight;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* ptree;
    char ch;
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

HeapType* create() { //생성함수
    HeapType* h = (HeapType*)malloc(sizeof(HeapType));
    h->heap_size = 0;
    return h;
}

void print_heap(HeapType* h) { //과정 출력
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

void insert_min_heap(HeapType* h, element item) {//삽입함수
    int i;
    i = ++(h->heap_size);

    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
    print_heap(h);
}

element delete_min_heap(HeapType* h) { //삭제함수
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];

    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key)) {
            child++;
        }
        if (temp.key <= h->heap[child].key) break;

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }

    h->heap[parent] = temp;
    return item;
    print_heap(h);
}

TreeNode* make_tree(TreeNode* left, TreeNode* right) { //이진 트리 생성 함수
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

void destroy_tree(TreeNode* root) { //트리 제거 함수
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

int is_leaf(TreeNode* root) { //단말노드 확인
    return !(root->left) && !(root->right);
}

void print_array(int codes[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", codes[i]);
    }
}

void print_codes(TreeNode* root, int codes[], int top) { //이진 코드 출력
    if (root->left) { //왼쪽 자식 노드가 있는 경우
        codes[top] = 1; //1
        print_codes(root->left, codes, top + 1);
    }

    if (root->right) { //오른쪽 자식이 있는 경우 
        codes[top] = 0; //0
        print_codes(root->right, codes, top + 1);
    }

    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        print_array(codes, top); //이진 코드 출력
        printf("\n");
    }
}

void huffman_tree(int freq[], char ch_list[], int n) { //허프만 코드 생성 함수
    int i;
    TreeNode* node, * x;
    HeapType* heap;
    element e, e1, e2;
    int codes[100];
    int top = 0;

    heap = create();

    for (i = 0; i < n; i++) {
        node = make_tree(NULL, NULL);
        e.ch = node->ch = ch_list[i];
        e.key = node->weight = freq[i];
        e.ptree = node;
        insert_min_heap(heap, e);
    }
    for (i = 1; i < n; i++) {
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);

        x = make_tree(e1.ptree, e2.ptree);
        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;
        printf("///%d + %d -> %d\n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);
    }

    e = delete_min_heap(heap);
    print_codes(e.ptree, codes, top);
    destroy_tree(e.ptree);
    free(heap);
}

int main() {
    char ch_list[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int freq[] = { 10, 15, 12, 3, 4, 13, 1 };
    huffman_tree(freq, ch_list, 7);
    return 0;
}
