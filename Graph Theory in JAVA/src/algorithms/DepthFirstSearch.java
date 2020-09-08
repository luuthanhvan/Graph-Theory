package algorithms;

import graphs.AdjacencyMatrixGraph;
import java.util.Stack;
import java.util.ArrayList;

public class DepthFirstSearch {
	private int[] visited;
	
	public void dfs(AdjacencyMatrixGraph graph, int vertex) {
		Stack<Integer> stack = new Stack<Integer>(); // create an empty Stack
		int nbVertices = graph.getNBVertices();
		
		// create a visited array with nbVertices+1 (because we skipped the first index of the array)
		visited = new int[nbVertices+1];
		
		// initializing all elements in visited[] is zero
		for(int i = 1; i <= nbVertices; i++) {
			visited[i] = 0;
		}
		
		// push the start vertex into Stack
		stack.push((Integer)vertex);
		
		// while stack does not empty
		while(!stack.empty()) {
			int u = stack.pop(); // get the vertex at the top of Stack
			
			// if this vertex visited
			if(visited[u] == 1)
				continue; // ignore it
			
			// else visited this vertex
			visited[u] = 1;
			System.out.println("Visit " + u);
			
			// get all adjacent vertices
			ArrayList<Integer> adjList = graph.getAdjacentVertices(u);
			
			// traversing all adjacent vertices
			for(int v = 0; v < adjList.size(); v++) {
				stack.push(adjList.get(v));  // push each vertex into Stack
			}
		}
	}
}
