
#ifndef GRAF_H
#define GRAF_H
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct graph {
	unsigned long long** arr;
	unsigned long long nnodes;
};
unsigned long long flow_rec(struct graph* g, unsigned long long start, unsigned long long finish);
void graph_not_dejkstra(struct graph* g);
void graph_menu();
void sort_rec(struct graph* g, unsigned long long this, unsigned long long* seq, unsigned long long* seqc);
void graph_top_sort(struct graph* g);
void graph_find_chrome(struct graph* g);
void graph_find_flow(struct graph* g);
struct graph* graph_input();
struct graph* graph_new(unsigned long nnodes);
void graph_generate_random(struct graph* g);
void graph_out(struct graph* g);
void graph_delete(struct graph* g);
void graph_find_loops(struct graph* g);
#endif