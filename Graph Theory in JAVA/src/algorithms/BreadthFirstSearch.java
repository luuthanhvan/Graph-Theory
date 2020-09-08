package algorithms;

import graphs.AdjacencyMatrixGraph;
import java.util.Queue;
import java.util.LinkedList;
import java.util.ArrayList;

public class BreadthFirstSearch {
	private int[] visited;
	
	public void bfs(AdjacencyMatrixGraph graph, int vertex) {
		 Queue<Integer> queue = new LinkedList<Integer>(); // create an empty Queue
		 int nbVertices = graph.getNBVertices();
			
		// create a visited array with nbVertices+1 (because we skipped the first index of the array)
		visited = new int[nbVertices+1];
		
		// initializing all elements in visited[] is zero
		for(int i = 1; i <= nbVertices; i++) {
			visited[i] = 0;
		}
		
		// push the start vertex into Queue
		queue.add((Integer)vertex);
		visited[vertex] = 1; // visited this vertex
		
		// while Queue does not empty
		while(!queue.isEmpty()) {
			// get the vertex at the top of Queue
			int u = queue.poll();
			
			System.out.println("Visit " + u);
			
			// get all adjacent vertices
			ArrayList<Integer> adjList = graph.getAdjacentVertices(u);
			
			// traversing all adjacent vertices
			for(int i = 0; i < adjList.size(); i++) {
				int v = adjList.get(i);
				// if there is a vertex v do not visit
				if(visited[v] == 0) {
					visited[v] = 1; // visited v
					queue.add((Integer)v); // push v into Queue
				}
			}
		}
	}
}
