#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <glib.h>
#include <math.h>

// The maximum number of edges a node can have
#define MAX_EDGES 10

typedef struct _Edge {
	int dest;
	double weight;
} Edge;

double* BellmanFord(GSList** adjacency, int numberOfVertices, int source)
{
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
				break;
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

// Finds the index of the minimum element in arr
int MinIndex(double* arr, int size)
{
	double min = DBL_MAX;
	int index;

	for (int i = 0; i < size; i++) {
		if (arr[i] < min) {
			min = arr[i];
			index = i;
		}
	}

	return index;
}

int main()
{
	int numberOfPlanets;
	int numberOfEdges;

	scanf("%d %d", &numberOfPlanets, &numberOfEdges);

	GSList** adjacency = malloc(numberOfPlanets * sizeof(*adjacency));
	for (int i = 0; i < numberOfPlanets; i++) {
		adjacency[i] = NULL;
	}

	for (int i = 0; i < numberOfEdges; i++) {
		int source;
		int dest;
		double weight;

		scanf("%d %d %lf", &source, &dest, &weight);
		Edge* edge = malloc(sizeof(*edge));
		edge->dest = dest - 1;
		edge->weight = weight;

		adjacency[source - 1] = g_slist_append(adjacency[source - 1], edge);
	}

	int startingPlanet;
	double startingWeight;
	scanf("%d %lf", &startingPlanet, &startingWeight);

	double* distances = BellmanFord(adjacency, numberOfPlanets, startingPlanet - 1);

	int min = MinIndex(distances, numberOfEdges);
	printf("%d->%lf\n", min + 1, pow(10, distances[min]));

	return 0;
}
