#define MAX_ELEMENTS 100

typedef struct{
	int Elements[MAX_ELEMENTS];
	int size;
} List;

void make_null(List *L){
	L->size = 0;
}

void push_back(List *L, int x){
	L->Elements[L->size] = x;
	++L->size;
}

int element_at(List *L, int i){
	return L->Elements[i-1];
}

int Size(List *L){
	return L->size;
}
