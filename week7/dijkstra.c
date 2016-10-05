#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <glib.h>

typedef struct _Edge {
	int dest;
	double weight;
} Edge;

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

double* FindShortestPaths(GSList** adjacency, int numberOfNodes, int source)
{
	double* distances = malloc(numberOfNodes * sizeof(*distances));
	gboolean* processed = malloc(numberOfNodes * sizeof(*processed));
	for (int i = 0; i < numberOfNodes; i++) {
		distances[i] = DBL_MAX;
		processed[i] = FALSE;
	}
	distances[source] = 0;

	for (int i = 0; i < numberOfNodes; i++) {
		int minVertex = MinDistance(distances, processed, numberOfNodes);
		processed[minVertex] = TRUE;

		GSList* edgesIt = adjacency[i];
		while(edgesIt != NULL) {
			Edge* e = (Edge*) edgesIt->data;
			if (!processed[e->dest] && distances[e->dest] > distances[i] + e->weight) {
				distances[e->dest] = distances[i] + e->weight;
			}

			edgesIt = g_slist_next(edgesIt);
		}
	}

	return distances;
}

int main()
{
	int numberOfHostels;
	int numberOfEdges;

	scanf("%d %d", &numberOfHostels, &numberOfEdges);

	GSList** adjacency = malloc(numberOfHostels * sizeof(*adjacency));
	for (int i = 0; i < numberOfHostels; i++) {
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

	int startingHostel;
	int numberOfHostelsWhereCSIsPlayed;
	scanf("%d %d", &startingHostel, &numberOfHostelsWhereCSIsPlayed);

	int* hostelsWhereCSIsPlayed = malloc (numberOfHostelsWhereCSIsPlayed * sizeof(*hostelsWhereCSIsPlayed));
	for (int i = 0; i < numberOfHostelsWhereCSIsPlayed; i++) {
		scanf("%d", &hostelsWhereCSIsPlayed[i]);
	}

	double* distances = FindShortestPaths(adjacency, numberOfHostels, startingHostel - 1);

	for (int i = 0; i < numberOfHostelsWhereCSIsPlayed; i++) {
		printf("%d -> %lf\n", hostelsWhereCSIsPlayed[i], distances[hostelsWhereCSIsPlayed[i] - 1]);
	}

	return 0;
}
