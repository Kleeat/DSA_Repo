typedef struct node
{
	int key;
	struct node* left;
	struct node* right;
} NODE;

NODE* SPLinsertNode(NODE* node, int key);
NODE* SPLsearchNode(NODE* node, int key);
NODE* SPLdeleteNode(NODE* node, int key);
int getDuplicates();