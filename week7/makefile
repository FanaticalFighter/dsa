all:
	gcc `pkg-config --libs --cflags glib-2.0` bellmanford.c -o bf
	gcc `pkg-config --libs --cflags glib-2.0`  dijkstra.c -o di

clean:
	rm bf di
