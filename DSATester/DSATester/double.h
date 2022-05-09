typedef struct {
	int key;
	char data[10];
} PAIR;
PAIR* initTable(PAIR* table);
void addElement(int key, char data[], PAIR* table);
void removeElement(int key, PAIR* table);
int searchElement(int key, PAIR* table);
int getHashDuplicates();
