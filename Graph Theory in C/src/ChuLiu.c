#include <stdio.h>
#define MAXIT 10
#define MAXN 20
#define INFINITY 99999999

// bieu dien do thi G
typedef struct{
	int u, v, w, link;
} Edge;

typedef struct{
	Edge edges[MAXN];
	int n, m;
} Graph;

// bieu dien do thi H
typedef struct{
	int n;
	int weight[MAXN];
	int parent[MAXN];
	int link[MAXN];
} Tree;

// khoi tao G
void init_graph(Graph *G, int n){
	G->n = n;
	G->m = 0;
}

void add_edge(Graph *G, int x, int y, int w, int link){
	G->edges[G->m].u = x;
	G->edges[G->m].v = y;
	G->edges[G->m].w = w;
	G->edges[G->m].link = link;
	++G->m;
}

// khoi tao H
void init_tree(Tree *T, int n){
	int i;
	T->n = n;
	for(i = 1; i <= n; ++i){
		T->parent[i] = -1;
		T->weight[i] = INFINITY;
		T->link[i] = -1;
	}
}

// xay dung do thi xap xi Ht tu Gt
void buildH(Graph *G, int root, Tree *H){
	int e, u, v, w, link;
	init_tree(H,G->n);
	for(e = 0; e < G->m; ++e){
		u = G->edges[e].u;
		v = G->edges[e].v;
		w = G->edges[e].w;
		link = G->edges[e].link;
		if(w < H->weight[v]){
			H->parent[v] = u;
			H->weight[v] = w;
			H->link[v] = link;
		}
	}
	H->parent[root] = -1;
	H->weight[root] = 0;
}

// tim chu trinh trong do thi H
int id[MAXN]; // luu ten moi cho cac dinh

int find_cycles(Tree *H, int root){
	int color[MAXN];
	int i, j, u, v, no = 0;
	// khoi tao
	for(i = 1; i <= H->n; ++i){
		id[i] = -1;
		color[i] = -1;
	}
	// duyet qua tung dinh, lan theo parent cua no
	for(i = 1; i <= H->n; i++){
		u = i;
		while(root != u && id[u] == -1 && color[u] != i){
			color[u] = i;
			u =	 H->parent[u];
		}
		// chua chu trinh
		if(color[u] == i){
			++no;
			v = H->parent[u];
			while(v != u){
				id[v] = no; // gan ten moi cho dinh v
				v = H->parent[v];
			}
			id[u] = no;
		}
	}
	return no; // tra ve so chu trinh tim duoc trong do thi H
}

void contract(Graph *G, Tree *H, int no, Graph *G1){
	init_graph(G1,no);
	int e, u, v, w;
	for(e = 0; e < G->m; ++e){
		u = G->edges[e].u;
		v = G->edges[e].v;
		w = G->edges[e].w;
		if(id[u] != id[v])
			add_edge(G1,id[u],id[v],w - H->weight[v], e);
	}
}

void expand(Tree *H, Graph *G1, Tree *H1){
	int i;
	for(i = 1; i <= H->n; ++i){
		if(H->parent[i] != -1){ 
			// lay cung tuong ung Gt-1
			Edge pe = G1->edges[H->link[i]];
			// doi cha cua pe.v thanh pe.u
			H1->parent[pe.v] = pe.u;
			H1->weight[pe.v] += H->weight[i];
			H1->link[pe.v] = pe.link;
		}
	}
}

void chuliu(Graph *G0, int s, Tree *T){
	Graph G[MAXIT];
	Tree H[MAXIT];
	int i, j, k, t, root;
	
	t = 0;
	root = s;
	G[0] = *G0; // gan tra tri cua do thi G0 cho do thi G tai vi tri co chi so = 0
// pha co
	while(1){
		// xay dung do thi xap xi
		buildH(&G[t], root, &H[t]);
		int no = find_cycles(&H[t], root);
		if(no == 0) // kiem tra do thi neu khong chua chu trinh thi ket thuc
			break;
		// dat ten moi cho cac dinh khong nam trong chu trinh
		for(i = 1; i <= H[t].n; ++i){
			if(id[i] == -1)
				id[i] = ++no;
		}
		// co do thi
		contract(&G[t], &H[t], no, &G[t+1]);
		root = id[root]; // goc moi
		++t; // so lan co do thi
	}
// pha gian
	for(k = t; k > 0; --k)
		expand(&H[k], &G[k-1], &H[k-1]);
// ket qua la H0
	*T = H[0];
}

int check_strong_connected(Graph *G, Tree *H){
	int check, i;
	chuliu(G,1,H);
	check = 1;
	for(i = 1; i < H->n; ++i)
		if(H->parent[i+1] != i)
			check = 0;
	return check;
}

int main(){
	Graph G;
	Tree H;
	int n, m, e, u, v, w, i;
	freopen("../data/chuliu.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G,n);
	for(e = 0; e < m; ++e){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G,u,v,w,-1);
	}
	if(check_strong_connected(&G,&H))
		printf("strong connected\n");
	else
		printf("unconnected\n");

//	for(i = 1; i <= H.n; ++i)
//		printf("%d\n", H.link[i]);

//	for(i = 1; i <= n; ++i)
//		printf("id[%d] = %d\n", i, id[i]);

	for(i = 1; i <= n; ++i)
		printf("parent[%d] = %d\tweight[%d] = %d\n", i, H.parent[i], i, H.weight[i]);
//	for(e = 0; e < m; ++e)
//		printf("%d %d %d %d\n", G.edges[e].u, G.edges[e].v, G.edges[e].w, G.edges[e].link);

	close(stdin);
	return 0;
}
