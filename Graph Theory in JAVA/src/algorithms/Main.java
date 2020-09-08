package algorithms;
import java.util.Scanner;
import graphs.AdjacencyMatrixGraph;

public class Main {
	public static void main(String[] args) {
		// Testing DFS and BFS algorithm
		AdjacencyMatrixGraph graph = new AdjacencyMatrixGraph(8, 13, false);
		graph.addEdge(1, 2, 0);
		graph.addEdge(2, 3, 0);
		graph.addEdge(3, 1, 0);
		graph.addEdge(4, 2, 0);
		graph.addEdge(4, 3, 0);
		graph.addEdge(4, 5, 0);
		graph.addEdge(5, 4, 0);
		graph.addEdge(5, 6, 0);
		graph.addEdge(6, 3, 0);
		graph.addEdge(6, 7, 0);
		graph.addEdge(7, 6, 0);
		graph.addEdge(8, 5, 0);
		graph.addEdge(8, 7, 0);
		
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter a vertex to start: ");
		int vertex = sc.nextInt(); // get user input
		/*
		DepthFirstSearch run = new DepthFirstSearch();
		run.dfs(graph, vertex);
		*/
		BreadthFirstSearch run = new BreadthFirstSearch();
		run.bfs(graph, vertex);
		
		sc.close();
	}

}
