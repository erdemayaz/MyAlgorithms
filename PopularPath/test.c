#include "popularpath.h"

int main () {
	// vertex number is variable which graph has vertex count
	// togetherness count is variable which path result of togetherness count
	int vertex_number = 10;
	int togetherness_count = 3;
	
	// 2D graph is adjacency for vertex directed connections together
	int graph[10][10] = {
	{0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
	{0, 1, 0, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 1, 0, 1, 0, 0, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
	{0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
	{0, 0, 0, 0, 1, 1, 0, 0, 0, 1}
	};
	
	// all_paths structe is a container that holds results
	all_paths *res = find_popular_path(graph, vertex_number, togetherness_count);
	
	// popular_path_count gives max count for most popular path as integer
	int max_count = popular_path_count(res);
	
	// popular_path gives most popular path as path structure
	path *max = (path*) popular_path(res);
	printf("\n%d --> ", max_count);
	
	// display_vertexes is helper in order to you can to display path
	display_vertexes(max);
	
	return 0;
}
