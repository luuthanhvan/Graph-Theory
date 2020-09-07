package graphs;
import java.util.ArrayList;

public class TestGraphs {
	public static void main(String[] args) {
		AdjacencyMatrixGraph graph = new AdjacencyMatrixGraph(4, 5, false);
		graph.addEdge(1, 2, 0);
		graph.addEdge(1, 3, 0);
		graph.addEdge(2, 3, 0);
		graph.addEdge(2, 4, 0);
		graph.addEdge(3, 4, 0);
		ArrayList<Integer> adjList = graph.getAdjacentVertices(1);
		for(int i = 0; i < adjList.size(); i++) {
			System.out.println(adjList.get(i));
		}
		graph.display();
	}
}
