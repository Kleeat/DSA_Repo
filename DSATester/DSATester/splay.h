typedef struct node
{
	int key;
	struct node* left;
	struct node* right;
} NODE;

NODE* insertNode(NODE* node, int key);
NODE* searchNode(NODE* node, int key);
NODE* deleteNode(NODE* node, int key);
int getDuplicates();
char included[5] = "Splay";