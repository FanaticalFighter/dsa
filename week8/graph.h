#include <glib.h>
#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>

// An edge in a graph
typedef struct _Edge {
	int dest;
	double weight;
} Edge;

void PrintEdge(int source, Edge* edge)
{
	printf("%d--%1.1lf-->%d\n", source, edge->weight, edge->dest);
}

// A structure representing a graph
typedef struct _Graph {
	GSList** adjacency;
	int vertices;
} Graph;

Graph* CreateGraph(int numberOfVertices)
{
	Graph* newGraph = malloc(sizeof(*newGraph));
	newGraph->vertices = numberOfVertices;
	newGraph->adjacency = malloc(numberOfVertices * sizeof(*(newGraph->adjacency)));
	for(int i = 0; i < numberOfVertices; i++) {
		newGraph->adjacency[i] = NULL;
	}

	return newGraph;
}

void AddEdge(Graph* graph, int source, int dest, double weight)
{
	Edge* newEdge = malloc(sizeof(*newEdge));
	newEdge->dest = dest;
	newEdge->weight = weight;
	graph->adjacency[source] = g_slist_prepend(graph->adjacency[source], newEdge);
}

void DeleteEdge(Graph* graph, int source, int dest)
{
	GSList* edgesIt = graph->adjacency[source];
	if (edgesIt == NULL) {
		return;
	}

	while (edgesIt->next != NULL) {
		edgesIt = g_slist_next(edgesIt);
	}

	graph->adjacency[source] = g_slist_delete_link(graph->adjacency[source], edgesIt);
}

int Degree(Graph* graph, int vertex)
{
	return g_slist_length(graph->adjacency[vertex]);
}

GSList* Neighbours(Graph* graph, int vertex)
{
	GSList* neighbours = NULL;
	GSList* it = graph->adjacency[vertex];
	while (it != NULL) {
		int* neighbour = malloc(sizeof(*neighbour));
		*neighbour = ((Edge*) it->data)->dest;

		neighbours = g_slist_prepend(neighbours, neighbour);
		it = g_slist_next(it);
	}

	return neighbours;
}

// Finds the minimum distance position in distances, ignoring the elements which
// have already been processed
int MinDistance(double* distances, gboolean* processed, int size)
{
	int min = INT_MAX;
	int minPosition;

	for (int i = 0; i < size; i++) {
		if (!processed[i] && distances[i] < min) {
			min = distances[i];
			minPosition = i;
		}
	}

	return minPosition;
}

// Finds the distances to all paths defined by the graph defined by the given
// adjacency list, from source
double* Dijkstra(Graph* graph, int source)
{
	GSList** adjacency = graph->adjacency;
	int numberOfNodes = graph->vertices;

	// All distances are initially infinty and nothing has been processed
	double* distances = malloc(numberOfNodes * sizeof(*distances));
	gboolean* processed = malloc(numberOfNodes * sizeof(*processed));
	for (int i = 0; i < numberOfNodes; i++) {
		distances[i] = DBL_MAX;
		processed[i] = FALSE;
	}
	distances[source] = 0;

	// Find least distance element, and relax connected edges if needed
	// Do this until all edges have been processed
	for (int i = 0; i < numberOfNodes; i++) {
		int minVertex = MinDistance(distances, processed, numberOfNodes);
		processed[minVertex] = TRUE;

		GSList* edgesIt = adjacency[minVertex];
		while(edgesIt != NULL) {
			Edge* e = (Edge*) edgesIt->data;
			if (!processed[e->dest] && distances[e->dest] > distances[minVertex] + e->weight) {
				distances[e->dest] = distances[minVertex] + e->weight;
			}

			edgesIt = g_slist_next(edgesIt);
		}
	}

	return distances;
}


double* BellmanFord(Graph* graph, int source)
{
	GSList** adjacency = graph->adjacency;
	int numberOfVertices = graph->vertices;

	// Stores the distances for each vertex
	double* distances = malloc(numberOfVertices * sizeof(*adjacency));

	for (int i = 0; i < numberOfVertices; i++) {
		distances[i] = DBL_MAX;
	}
	distances[source] = 0;

	for (int i = 0; i < numberOfVertices - 1; i++) {
		for (int j = 0; j < numberOfVertices; j++) {
			// If the distance is the maximum possible, there's no use to examine this now
			if(distances[j] == DBL_MAX) {
				continue;
			}

			// Relax all connected edges if needed
			GSList* edgesIt = adjacency[j];
			while(edgesIt != NULL) {
				Edge* e = (Edge*) edgesIt->data;
				if (distances[e->dest] > distances[j] + e->weight) {
					distances[e->dest] = distances[j] + e->weight;
				}

				edgesIt = g_slist_next(edgesIt);
			}
		}
	}

	return distances;
}

GSList* DFS(Graph* graph, int startingNode)
{
	gboolean* visited = calloc(graph->vertices, sizeof(*visited));
	GSList* DFS = NULL;

	Stack stack = StackNew();
	int* startingNodeDyn = malloc(sizeof(*startingNodeDyn));
	*startingNodeDyn = startingNode;
	StackPush(&stack, startingNodeDyn);

	while (!StackIsEmpty(stack)) {
		int* v = StackPop(&stack);

		if(visited[*v]) {
			continue;
		}

		GSList* neighbours = Neighbours(graph, *v);
		GSList* it = neighbours;
		while (it != NULL) {
			int* neighbouringVertex = (int*) it->data;
			if (!visited[*neighbouringVertex]) {
				StackPush(&stack, neighbouringVertex);
			}
			it = g_slist_next(it);
		}

		visited[*v] = TRUE;
		DFS = g_slist_prepend(DFS, v);
	}

	DFS = g_slist_reverse(DFS);

	return DFS;
}

GSList* BFS(Graph* graph, int startingNode)
{
	gboolean* visited = calloc(graph->vertices, sizeof(*visited));
	GSList* BFS = NULL;

	int* startingNodeDyn = malloc(sizeof(*startingNodeDyn));
	*startingNodeDyn = startingNode;

	GQueue* queue = g_queue_new();
	g_queue_push_tail(queue, startingNodeDyn);

	while (g_queue_get_length(queue) > 0) {
		int* v = g_queue_pop_head(queue);

		if(visited[*v]) {
			continue;
		}

		GSList* neighbours = Neighbours(graph, *v);
		GSList* it = neighbours;
		while (it != NULL) {
			int* neighbouringVertex = (int*) it->data;
			if (!visited[*neighbouringVertex]) {
				g_queue_push_tail(queue, neighbouringVertex);
			}
			it = g_slist_next(it);
		}

		visited[*v] = TRUE;
		BFS = g_slist_prepend(BFS, v);
	}

	BFS = g_slist_reverse(BFS);

	return BFS;
}

Graph* Prim(Graph* graph, int source)
{
	GSList** adjacency = graph->adjacency;
	int numberOfNodes = graph->vertices;

	double* distances = malloc(numberOfNodes * sizeof(*distances));
	int* prev = malloc(numberOfNodes * sizeof(*prev));
	gboolean* processed = malloc(numberOfNodes * sizeof(*processed));
	for (int i = 0; i < numberOfNodes; i++) {
		distances[i] = DBL_MAX;
		processed[i] = FALSE;
		prev[i] = i;
	}
	distances[source] = 0;

	for (int i = 0; i < numberOfNodes; i++) {
		int minVertex = MinDistance(distances, processed, numberOfNodes);
		processed[minVertex] = TRUE;

		GSList* edgesIt = adjacency[minVertex];
		while(edgesIt != NULL) {
			Edge* e = (Edge*) edgesIt->data;
			if (!processed[e->dest] && distances[e->dest] > e->weight) {
				distances[e->dest] = e->weight;
				prev[e->dest] = minVertex;
			}

			edgesIt = g_slist_next(edgesIt);
		}
	}

	Graph* mst = CreateGraph(graph->vertices);
	for (int i = 0; i < graph->vertices; i++) {
		if (i != prev[i]) {
			AddEdge(mst, prev[i], i, distances[i]);
		}
	}

	return mst;
}

typedef struct _DoubleEdge {
	int source;
	int dest;

	double weight;
} DoubleEdge;

gint EdgeCompareFunction(gconstpointer a, gconstpointer b)
{
	DoubleEdge* aEdge = (DoubleEdge*) a;
	DoubleEdge* bEdge = (DoubleEdge*) b;
	return aEdge->weight > bEdge->weight;
}

Graph* Kruskal(Graph* graph, int source)
{
	GSList* edges = NULL;
	for (int i = 0; i < graph->vertices; i++) {
		GSList* edgesIt = graph->adjacency[i];
		while(edgesIt != NULL) {
			Edge* e = (Edge*) edgesIt->data;

			DoubleEdge* de = malloc(sizeof(*de));
			de->source = i;
			de->dest = e->dest;
			de->weight = e->weight;

			edges = g_slist_prepend(edges, de);

			edgesIt = g_slist_next(edgesIt);
		}
	}

	edges = g_slist_sort(edges, &EdgeCompareFunction);

	Graph* mst = CreateGraph(graph->vertices);
	int* sets = malloc(graph->vertices * sizeof(*sets));
	for (int i = 0; i < graph->vertices; i++) {
		sets[i] = i;
	}

	int chosen = 0;
	while (edges != NULL && chosen < graph->vertices - 1) {
		DoubleEdge* e = (DoubleEdge*) edges->data;
		if (sets[e->source] != sets[e->dest]) {
			AddEdge(mst, e->source, e->dest, e->weight);
			sets[e->dest] = sets[e->source];
			chosen++;
		}

		edges = g_slist_next(edges);
	}

	return mst;
}

void PrintGraph(Graph* graph)
{
	printf("Vertices: ");
	for(int i = 0; i < graph->vertices; i++) {
		printf("%d ", i);
	}
	printf("\n");

	printf("Edges:\n");
	for(int i = 0; i < graph->vertices; i++) {
		GSList* edges = graph->adjacency[i];
		while (edges != NULL) {
			Edge* edge = (Edge*) edges->data;
			PrintEdge(i, edge);
			edges = g_slist_next(edges);
		}
	}
	printf("\n");
}

void PrintDoubleArray(double* arr, int length)
{
	for(int i = 0; i < length; i++) {
		printf("%d: %lf\n", i, arr[i]);
	}
}

void PrintIntGSList(GSList* arr)
{
	while (arr != NULL) {
		printf("%d ", * (int*) arr->data);
		arr = g_slist_next(arr);
	}
	printf("\n");
}

Graph* ReadGraphFromFile(char* filename)
{
	FILE* f = fopen(filename, "r");

	int n;
	fscanf(f, "%d", &n);
	Graph* g = CreateGraph(n);

	int source, dest;
	double weight;
	while (fscanf(f, "%d %d %lf", &source, &dest, &weight) == 3) {
		AddEdge(g, source, dest, weight);
	}

	return g;
}
