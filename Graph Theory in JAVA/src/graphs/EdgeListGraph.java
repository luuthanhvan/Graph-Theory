package graphs;
import java.util.ArrayList;

class Edge{
	/* define some private attributes */
	private int u;
	private int v;
	private int w;
	
	/* define public methods */
	// setters
	public void setU(int u) {
		this.u = u;
	}
	
	public void setV(int v) {
		this.v = v;
	}
	
	public void setW(int w) {
		this.w = w;
	}
	
	// getters
	public int getU() {
		return this.u;
	}
	
	public int getV() {
		return this.v;
	}
	
	public int getW() {
		return this.w;
	}
}

public class EdgeListGraph extends Graph {
	/* define some private attributes */
	private ArrayList<Edge> edges;
	
	/* define public methods */
	public EdgeListGraph(int nbVertices, boolean isDirected) {
		super(nbVertices, 0, isDirected);
		edges = new ArrayList<Edge>();
	}
	
	@Override
	public void addEdge(int u, int v, int w) {
		int nbEdges = super.getNBEdges();
		Edge edge = new Edge();
		if(w != 0) {
			edge.setU(u);
			edge.setV(v);
			edge.setW(w);
		}
		else {
			edge.setU(u);
			edge.setV(v);
			edge.setW(0);
		}
		this.edges.add(edge);
		nbEdges++;
		super.setNBEdges(nbEdges);
	}
	
	@Override
	public void display() {
		for(int e = 0; e < this.edges.size(); e++) {
			System.out.println("(" + this.edges.get(e).getU() + ", " + this.edges.get(e).getV() + ") = " + this.edges.get(e).getW());
		}
	}
	
	@Override
	public boolean isAdjacent(int u, int v) {
		for(int e = 0; e < this.edges.size(); e++)
			if((this.edges.get(e).getU() == u && this.edges.get(e).getV() == v) || 
				(this.edges.get(e).getU() == v && this.edges.get(e).getV() == u))
				return true;
		return false;
	}
}
