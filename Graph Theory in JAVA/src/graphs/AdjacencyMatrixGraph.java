package graphs;
import java.util.ArrayList;

public class AdjacencyMatrixGraph extends Graph{
	/* define some private attributes */
	private int matrix[][];
	
	/* define public methods */
	// constructor
	public AdjacencyMatrixGraph(int nbVertices, int nbEdges, boolean isDirected) {
		super(nbVertices, nbEdges, isDirected);
		matrix = new int[nbVertices+1][nbVertices+1];
		for(int u = 1; u <= nbVertices; u++) {
			for(int v = 1; v <= nbVertices; v++) {
				this.matrix[u][v] = 0;
			}
		}
	}
	
	@Override
	public void display() {
		int nbVertices = super.getNBVertices();
		for(int u = 1; u <= nbVertices; u++) {
			for(int v = 1; v <= nbVertices; v++) {
				System.out.print(this.matrix[u][v] + " ");
			}
			System.out.println();
		}
	}
	
	@Override
	public void addEdge(int u, int v, int w) {
		boolean isDirected = super.getGraphType();
		if(isDirected) {
			if(w != 0) {
				this.matrix[u][v] = w;
			}
			else {
				this.matrix[u][v] = 1;
			}
		}
		else {
			if(w != 0) {
				this.matrix[u][v] = w;
				this.matrix[v][u] = w;
			}
			else {
				this.matrix[u][v] = 1;
				this.matrix[v][u] = 1;
			}
		}
	}
	
	@Override
	public boolean isAdjacent(int u, int v) {
		return this.matrix[u][v] != 0;
	}
	
	@Override
	public ArrayList<Integer> getAdjacentVertices(int u){
		ArrayList<Integer> adjList = new ArrayList<Integer>();
		int nbVertices = super.getNBVertices();
		for(int v = 1; v <= nbVertices; v++) {
			if(this.isAdjacent(u, v))
				adjList.add((Integer)v);
		}
		return adjList;
	}
	
	@Override
	public int getIndegree(int u) {
		int deg = 0;
		int nbVertices = super.getNBVertices();
		for(int v = 1; v <= nbVertices; v++)
			if(this.isAdjacent(v, u))
				deg++;
		return deg;
	}
	
	@Override
	public int getOutdegree(int u) {
		int deg = 0;
		int nbVertices = super.getNBVertices();
		for(int v = 1; v <= nbVertices; v++)
			if(this.isAdjacent(u, v))
				deg++;
		return deg;
	}
}
