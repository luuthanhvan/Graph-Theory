#define MAX_ELEMENTS 100

typedef struct{
	int front, rear;
	int data[MAX_ELEMENTS];
} Queue;

void initQueue(Queue *Q){
	Q->front = 0;
	Q->rear = -1;
}

void push(Queue *Q, int x){
	++Q->rear;
	Q->data[Q->rear] = x;
}

int top(Queue Q){
	return Q.data[Q.front];
}

void pop(Queue *Q){
	Q->front++;
}

int empty(Queue Q){
	return Q.front > Q.rear;
}
