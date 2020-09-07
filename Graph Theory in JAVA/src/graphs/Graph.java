package graphs;
import java.util.ArrayList;

public class Graph {
	/* define some private attributes */
	private int nbVertices;
	private int nbEdges;
	private boolean isDirected;
	
	/* define public methods */
	public Graph(int nbVertices, int nbEdges, boolean isDirected) {
		this.nbVertices = nbVertices;
		this.nbEdges = nbEdges;
		this.isDirected = isDirected;
	}
	
	// setters
	public void setNBVertices(int nbVertices) {
		this.nbVertices = nbVertices;
	}
	
	public void setNBEdges(int nbEdges) {
		this.nbEdges= nbEdges;
	}
	
	public void setGraphType(boolean isDirected) {
		this.isDirected = isDirected;
	}
	
	// getters
	public int getNBVertices() {
		return this.nbVertices;
	}
	
	public int getNBEdges() {
		return this.nbEdges;
	}
	
	public boolean getGraphType() {
		return this.isDirected;
	}
	
	public void display() {
		// implement in sub-class
	}
	
	public void addEdge(int u, int v, int w) {
		// implement in sub-class
	}
	
	public boolean isAdjacent(int u, int v) {
		boolean check = false;
		// implement in sub-class
		return check;
	}
	
	public ArrayList<Integer> getAdjacentVertices(int u){
		ArrayList<Integer> adjList = new ArrayList<Integer>();
		for(int v = 1; v <= this.nbVertices; v++) {
			if(this.isAdjacent(u, v))
				adjList.add((Integer)v);
		}
		return adjList;
	}
	
	public int getIndegree(int u) {
		int deg = 0;
		// implement in sub-class
		return deg;
	}
	
	public int getOutdegree(int u) {
		int deg = 0;
		// implement in sub-class
		return deg;
	}
	
	public int getDegree(int u) {
		return this.getAdjacentVertices(u).size();
	}
}
