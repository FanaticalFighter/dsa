#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

int main()
{
	// Get the parameters for the game
	int numberOfPlayers;
	int numberOfPassesPerRound;
	printf("Please enter the number of players and the number of passes per round\n");
	scanf("%d %d", &numberOfPlayers, &numberOfPassesPerRound);

	// Build the queue with the players
	GQueue* players = g_queue_new();
	int i;
	for (i = 0; i < numberOfPlayers; i++)
	{
		int* playerNumber = malloc(sizeof (*playerNumber));
		*playerNumber = i;
		g_queue_push_tail(players, playerNumber);
	}

	// Simulate a game
	while (g_queue_get_length(players) > 1) {
		// Pass the potato around for numberOfPassesPerRound
		for (i = 0; i < numberOfPassesPerRound; i++) {
			g_queue_push_tail(players, g_queue_pop_head(players));
		}

		// Remove the person with the potato from the game
		g_free(g_queue_pop_head(players));
	}

	// Show the winning position from the simulation
	int* finalPlayer = g_queue_pop_head(players);
	printf("The winning strategy is to be at the %dth position\n", *finalPlayer);
	g_free(finalPlayer);

	return 0;
}
