package algorithms;

import graphs.AdjacencyMatrixGraph;
import java.util.Stack;
import java.util.ArrayList;

public class DepthFirstSearch {
	private int[] visited;
	
	public void dfs(AdjacencyMatrixGraph graph, int vertex) {
		Stack<Integer> stack = new Stack<Integer>();
		int nbVertices = graph.getNBVertices();
		visited = new int[nbVertices+1];
		
		for(int i = 1; i <= nbVertices; i++) {
			visited[i] = 0;
		}
		stack.push((Integer)vertex);
		
		while(!stack.empty()) {
			int u = stack.pop();
			
			if(visited[u] == 1)
				continue;
			
			visited[u] = 1;
			System.out.println("Visit " + u);
			
			ArrayList<Integer> adjList = graph.getAdjacentVertices(u);
			for(int v = 0; v < adjList.size(); v++) {
				stack.push(adjList.get(v));
			}
		}
	}
}
