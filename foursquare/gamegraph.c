#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "foursquare.h"

typedef struct Node {
	struct Game *game;
	struct Node *parent;
	struct Node **children;
} Node;

typedef struct PSubTree {
	Node root;
	int nodes; /// number of nodes in this subtree
	int levels;
} Graph;

int writeToDisk(Graph g)
int readFromFile(File *fp, Graph *g)

