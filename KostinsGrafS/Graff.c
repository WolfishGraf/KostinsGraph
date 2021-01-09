#include "graf.h"
#define _CRT_SECURE_NO_WARNINGS 

void graph_menu() {
	struct graph* g = NULL;
	while (1) {
		int optionn = 0;
		printf("����:\n");
		printf("%d. ������� ����.\n", ++optionn);
		printf("%d. ������ ����.\n", ++optionn);
		printf("%d. ����� ����� � �����.\n", ++optionn);
		printf("%d. ���������� �������������� ���������� �����.\n", ++optionn);
		printf("%d. ����� ������������� ����� ����� (������������������).\n", ++optionn);
		printf("%d. ����� ������������ �����/����������� ������ (���� � �� �� �����).\n", ++optionn);
		printf("%d. ����� ���������� ���������� �� v0 �� �������� ��������� �������.\n", ++optionn);
		printf("%d. �����.\n", ++optionn);
		int option = 0;
		scanf("%d", &option);
		if (option == 1)graph_out(g);
		if (option == 2) { graph_delete(g); g = NULL; g = graph_input(); }
		if (option == 3)graph_find_loops(g);
		if (option == 4)graph_top_sort(g);
		if (option == 5)graph_find_chrome(g);
		if (option == 6)graph_find_flow(g);
		if (option == 7)graph_not_dejkstra(g);
		if (option == 8)return;
	}
}
char* visited = NULL;
void graph_not_dejkstra(struct graph* g) {
	printf("������� ����� ����������� �������\n");
	unsigned long long start = 0;
	scanf("%llu", &start);
	unsigned long long maxflow = 0;
	unsigned long long maxflown = 0;
	unsigned long long t = 0;
	visited = calloc(1, g->nnodes);
	for (unsigned long long i = 0; i < g->nnodes; i++) {
		t = flow_rec(g, start, i);
		if (t > maxflow) { maxflow = t; maxflown = i; }
	}
	free(visited);
	printf("������������ ���������� %llu �� ������� %llu\n", maxflow, maxflown);
}
char checkcolors(struct graph* g, char* colors) {
	for (unsigned long long i = 0; i < g->nnodes; i++) {
		for (unsigned long long j = 0; j < g->nnodes; j++) {
			if (!(g->arr[i][j]))continue;
			if (colors[i] == colors[j])return 0;
		}
	}
	return 1;
}
void increment(struct graph* g, char* colors, unsigned long long* ncolors) {
	char needtoincrement = 1;
	for (unsigned long long i = 0; ((i < g->nnodes) && (needtoincrement)); i++) {
		needtoincrement = 0;
		colors[i] += 1;
		if (colors[i] > (*ncolors)) {
			colors[i] = 1;
			needtoincrement = 1;
		}
	}
	if (needtoincrement) {
		*ncolors += 1;
		for (unsigned long long i = 0; i < g->nnodes; i++)
			colors[i] = 1;
	}

}

unsigned long long flow_rec(struct graph* g, unsigned long long start, unsigned long long finish) {
	//	printf("start %llu finish %llu\n",start,finish);
	unsigned long long max = 0;
	if (start == finish)return 0;
	visited[start] = 1;
	for (unsigned long long i = 0; i < g->nnodes; i++) {
		if (g->arr[start][i])if (!visited[i])if (max < ((g->arr[start][i]) + flow_rec(g, i, finish))) { max = ((g->arr[start][i]) + flow_rec(g, i, finish)); }
	}
	visited[start] = 0;
	return max;
}
void graph_find_flow(struct graph* g) {
	unsigned long long start = 0;
	unsigned long long finish = 0;
	char flag = 0;
	for (unsigned long long i = 0; i < g->nnodes; i++) {
		flag = 0;
		for (unsigned long long j = 0; j < g->nnodes; j++) {
			if (g->arr[j][i]) { flag = 1; break; }
		}
		if (!flag) { start = i; break; }
	}
	for (unsigned long long i = 0; i < g->nnodes; i++) {
		flag = 0;
		for (unsigned long long j = 0; j < g->nnodes; j++) {
			if (g->arr[i][j]) { flag = 1; break; }
		}
		if (!flag) { finish = i; break; }
	}
	visited = calloc(1, g->nnodes);
	unsigned long long maxflow = flow_rec(g, start, finish);
	free(visited);
	printf("\n�����: %llu\n", maxflow);
}
void graph_find_chrome(struct graph* g) {
	char* colors = calloc(sizeof(char), g->nnodes);
	for (unsigned long long i = 0; i < g->nnodes; i++)
		colors[i] = 1;
	unsigned long long ncolors = 1;
	while (!checkcolors(g, colors)) {
		increment(g, colors, &ncolors);
	}
	printf("���������� %llu �������\n", ncolors);
	printf("�����:\n");
	for (unsigned long long i = 0; i < g->nnodes; i++)
		printf("%d ", colors[i]);
	printf("\n");
}
void graph_top_sort(struct graph* g) {
	char flag = 0;
	if (!g)return;
	printf("��������������� �������:\n");
	char* marks = NULL;
	marks = calloc(sizeof(unsigned long long), g->nnodes);
	unsigned long long nmarks = 0;
	unsigned long long oldnmarks = 1;
	while (nmarks != g->nnodes) {
		oldnmarks = nmarks;
		for (unsigned long long i = 0; i < g->nnodes; i++) {
			flag = 0;
			if (marks[i]) { continue; }
			for (unsigned long long j = 0; j < g->nnodes; j++) {
				if (g->arr[j][i])if (!marks[j]) { flag = 1; break; }
			}
			if (!flag) {
				printf("%llu ", i);
				marks[i] = 1;
				nmarks += 1;
				break;
			}
		}
		if (nmarks == oldnmarks)printf("� ����� ���� �����, ���������� ����������\n");
	}
	printf("\n");
	free(marks);
}
struct graph* graph_new(unsigned long nnodes) {
	struct graph* t = calloc(sizeof(struct graph), 1);
	t->nnodes = nnodes;
	t->arr = calloc(sizeof(unsigned long long*), nnodes);
	for (unsigned long long i = 0; i < nnodes; i++) {
		t->arr[i] = calloc(sizeof(unsigned long long), nnodes);
		for (unsigned long long j = 0; j < nnodes; j++) {
			t->arr[i][j] = 0;
		}
	}
	return t;
}
void graph_generate_random(struct graph* g) {
	time_t t;
	srand((unsigned)time(&t));
	for (unsigned long long i = 0; i < (g->nnodes); i++)
		for (unsigned long long j = 0; j < (g->nnodes); j++) {
			g->arr[i][j] = (unsigned long long)(rand() % 100);
			if (rand() % 2 - 1)g->arr[i][j] = 0;

		}
	unsigned long long i = 0;
	while ((i < g->nnodes) && (i < g->nnodes)) {
		g->arr[i][i] = 0;
		i += 1;
	}
}
struct graph* graph_input() {
	unsigned long long n = 0;
	printf("������� ���-�� ������ � �����\n");
	scanf("%llu", &n);
	struct graph* g = graph_new(n);
	printf("������� ������ ����� �����. 1 - �� ������, 2 - ������� ���������:\n");
	int way = 0;
	scanf("%d", &way);
	if (way == 1) {
		printf("���� ���������������? 1-��, 2-���\n");
		int direct = 0;
		scanf("%d", &direct);
		printf("������� ����� ����� �� ������ �� ������ � ������� ���� �����(��, ��, ���) ����������� ��������. �� ��������� ����� ������� -1. ������� ���������� � 0\n");
		unsigned long long from = 0, to = 0, weight = 0;
		char s[30];
		while (1) {
			fgets(s, 30, stdin);
			if (s[0] == '-')return g;
			sscanf(s, "%llu %llu %llu", &from, &to, &weight);
			g->arr[from][to] = weight;
			if (direct == 2)g->arr[to][from] = weight;
		}
	}
	if (way == 2) {
		for (unsigned long long i = 0; i < n; i++) {
			for (unsigned long long j = 0; j < n; j++) {
				scanf("%llu", &(g->arr[i][j]));

			}
		}
		printf("\n");
		return g;
	}
}
static unsigned long long rec(struct graph* g, unsigned long long* path, unsigned long long npath) {
	unsigned long long loops = 0;
	if (npath > 1)
		if (path[0] == path[npath - 1]) {
			for (unsigned long long i = 0; i < npath; i++) {
				printf("%llu ", path[i]);
			}
			printf("\n");
			free(path);
			return 1;
		}
	for (unsigned long long i = 1; i < npath - 1; i++) {
		if (path[i] == path[npath - 1])return 0;
	}
	for (unsigned long long i = 0; i < g->nnodes; i++) {
		if (!(g->arr[path[npath - 1]][i]))continue;
		unsigned long long* path_copy = malloc(sizeof(unsigned long long) * (npath + 1));
		memcpy(path_copy, path, sizeof(unsigned long long) * npath);
		path_copy[npath] = i;
		loops += rec(g, path_copy, npath + 1);
	}
	free(path);
	return loops;
}

void graph_find_loops(struct graph* g) {
	if (!g) { printf("���� �� �����.\n"); return; }
	printf("Loops:\n");
	unsigned long long totalloops = 0;
	for (unsigned long long i = 0; i < (g->nnodes); i++) {
		{
			unsigned long long* path = malloc(sizeof(unsigned long long));
			path[0] = i;
			totalloops += rec(g, path, 1);
		}
	}
	printf("Total loops: %llu\n", totalloops);
}
void graph_out(struct graph* g) {
	if (!g) { printf("���� �� �����.\n"); return; }
	for (unsigned long long i = 0; i < g->nnodes; i++) {
		for (unsigned long long j = 0; j < g->nnodes; j++)
			printf("%3llu", g->arr[i][j]);
		printf("\n");
	}
	printf("---------------------------\n");
	for (unsigned long long i = 0; i < g->nnodes; i++) {
		char flag;
		flag = 0;
		for (unsigned long long j = 0; j < g->nnodes; j++) {
			if (g->arr[i][j])
				if (flag)
					printf("   +--->%d\n", j);
				else {
					printf("%2d-T--->%d\n", i, j);
					flag = 1;
				}
		}
	}

}
void graph_delete(struct graph* g) {
	if (!g)return;
	for (unsigned long long i = 0; i < g->nnodes; i++)
		free(g->arr[i]);
	free(g->arr);
	g->nnodes = 0;
}