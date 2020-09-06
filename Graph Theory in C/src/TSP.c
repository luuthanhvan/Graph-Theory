#include <stdio.h>
#include <math.h>
#define MAXN 20
#define MAXIMUM 999999
typedef float pointType;
typedef float elementType;

typedef struct{
	int u, v;
	elementType w;
} Edge;

typedef struct{
	int parent[MAXN];
	Edge edges[MAXN];
	int n, m;
} Graph;

void init_graph(Graph *G, int n){
	G->n = n;
	G->m = 0;
}

void add_edge(Graph *G, int x, int y, elementType w){
	G->edges[G->m].u = x;
	G->edges[G->m].v = y;
	G->edges[G->m].w = w;
	++G->m;
}

int degree(Graph *G, int x){
	int y, deg = 0;
	for(y = 0; y < G->m; ++y)
		if(G->edges[y].u == x || G->edges[y].v == x)
			++deg;
	return deg;
}

typedef struct{
	pointType x, y;
} Point;

typedef struct{
	int n; // number of points
	int size; // size of array
	Point points[MAXN];
} listOfPoint;

void make_null(listOfPoint *P, int n){
	P->n = n;
	P->size = 0;
}

void input_pointList(listOfPoint *P, pointType x, pointType y){
	P->points[P->size].x = x;
	P->points[P->size].y = y;
	++P->size;
}

// tinh khoang cach giua 2 diem
pointType calculate_length(Point A, Point B){
	return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

// tinh tat ca cac khoang cach tu 1 dinh hien tai den cac dinh con lai
// sau do them cung vao do thi
void input_graph(Graph *G, listOfPoint *P){
	int i, j;
	elementType p;
	for(i = 1; i < G->n; ++i){
		for(j = i+1; j <= G->n; ++j){
			p = calculate_length(P->points[i-1],P->points[j-1]);
			add_edge(G,i,j,p);
		}
	}
}

void swap(Edge *edge1, Edge *edge2){
	Edge tmp;
	tmp = *edge1;
	*edge1 = *edge2;
	*edge2 = tmp;
}

void sort(Graph *G){
	int i, j;
	for(i = 0; i < G->m-1; ++i)
		for(j = i+1; j < G->m; ++j)
			if(G->edges[j].w < G->edges[i].w)
				swap(&G->edges[i], &G->edges[j]);
}

int findRoot(Graph *G, int u){
	while(u != G->parent[u])
		u = G->parent[u];
	return u;
}

void TSP(Graph *G, Graph *T){
	int i, j, u, v, u1, v1, e, root_u, root_v;
	elementType w, w1, sum = 0.0;
	init_graph(T,G->n);
	sort(G);
	for(u = 1; u <= G->n; ++u)
		G->parent[u] = u;
	for(e = 0; e < G->m; ++e){
		u = G->edges[e].u;
		v = G->edges[e].v;
		w = G->edges[e].w;
		root_u = findRoot(G,u);
		root_v = findRoot(G,v);
		if(root_u != root_v)
			if(degree(T,u) < 2 && degree(T,v) < 2)
			{
				add_edge(T,u,v,w);
				sum += w;
				G->parent[root_v] = root_u;
			}
	}
// duyet qua tat cac cung cua do thi G 1 lan nua
	for(e = 0; e < G->m; ++e){
		u = G->edges[e].u;
		v = G->edges[e].v;
		w = G->edges[e].w;
		if(degree(T,u) == 1 && degree(T,v) == 1){ // tim dinh co bac bang 1 trong T
			add_edge(T,u,v,w); // them cung de tao thanh chu trinh
			sum += w;
			break;
		}
	}
//	for(e = 1; e <= T->n; ++e)
//		printf("deg(%d) = %d\n", e, degree(T,e));
	printf("%.2f\n", sum);
	for(e = 0; e < T->m; ++e)
		printf("%d %d\n", T->edges[e].u, T->edges[e].v);
}


int main(){
	Graph G, T;
	int n, p, i, j;
	pointType x, y;
	listOfPoint P;
	freopen("../data/point.txt", "r", stdin);
	scanf("%d", &n);
	make_null(&P,n);
	for(p = 1; p <= n; ++p){
		scanf("%f%f", &x, &y);
		input_pointList(&P,x,y);
	}
	
	init_graph(&G,n);
	input_graph(&G,&P);
	TSP(&G,&T);
	
	close(stdin);
	return 0;
}
