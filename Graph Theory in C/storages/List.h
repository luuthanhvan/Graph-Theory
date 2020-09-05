#define MAX_ELEMENTS 100

typedef struct{
	int elements[MAX_ELEMENTS];
	int size;
} List;

void initList(List *L){
	L->size = 0;
}

void add(List *L, int x){
	L->elements[L->size++] = x;
}

int getElementAt(List L, int pos){
	return L.elements[pos-1];
}

int getSize(List L){
	return L.size;
}
