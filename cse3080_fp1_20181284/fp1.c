#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct _Edge {
	int x;
	int y;
	int weight;
}Edge;
int n = 0;
Edge* heap;
Edge* T;


int p = 0; //the number of edges s.t included in T
int* parent;
int ver_num;
int edge_num;

void insert_min_heap(Edge item, int* n);
Edge delete_min_heap(int* n);
int Find(int index);


int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("usage: ./fp1 input_filename");

		return 0;
	}
	clock_t start, end;

	start = clock();
	FILE* fp;
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("The input file does not exist.");

		return 0;
	}
	FILE* outfile;
	outfile = fopen("fp1_result.txt", "w");

	
	int i;
	int total_cost= 0;
	Edge temp;
	
	fscanf(fp, "%d", &ver_num);
	fscanf(fp, "%d", &edge_num);
	Edge* edge = (Edge*)malloc(sizeof(Edge)*edge_num);
	parent = (int*)malloc(sizeof(int) * ver_num);
	heap = (Edge*)malloc(sizeof(Edge)*edge_num+1);
	T = (Edge*)malloc(sizeof(Edge) * edge_num);


	for (i = 0; i < ver_num; i++) {
		parent[i] = -1;
	}
	
	for (i = 0; i < edge_num; i++) {
		fscanf(fp, "%d", &edge[i].x);
		if (edge[i].x > ver_num) { // edge 점 체크
			printf("input file format error(vertex)!\n");
			return 0;
		}
		fscanf(fp, "%d", &edge[i].y);
		if (edge[i].y > ver_num) { //edge 점 체크
			printf("input file format error(vertex)!\n");
			return 0;
		}
		fscanf(fp, "%d", &edge[i].weight);
	}
	
	for (i = 0; i < edge_num; i++) { //weight에 따라 내림차순으로 min heap 만들기
		insert_min_heap(edge[i], &n);
	}
	
	while (p < ver_num - 1 && n != 0) {
		T[++p] = delete_min_heap(&n);
		if (parent[T[p].x] != -1 && Find(T[p].y) == Find(T[p].x)) {
			p--;
			continue;
		}
		fprintf(outfile, "%d %d %d\n", T[p].x, T[p].y, T[p].weight);
		total_cost += T[p].weight;
		if (parent[T[p].x] == -1) {
			parent[T[p].y] = T[p].x;
		}
		else {
			parent[T[p].y] = parent[T[p].x];
		}

	}
	fprintf(outfile, "%d\n", total_cost);
	if (p < ver_num - 1) { //not connected
		fprintf(outfile, "DISCONNECTED\n");
	}
	else { //connected
		fprintf(outfile, "CONNECTED\n");
	}

	fclose(fp);
	fclose(outfile);
	end = clock();
	printf("output written to fp1_result.txt.\n");
	printf("running time: %f seconds\n", (float)(end - start)/CLOCKS_PER_SEC);
	
	return 0;
}

void insert_min_heap(Edge item, int* n) {
	int i;
	i = ++(*n); //heap은 1부터 시작
	while ((i != 1) && (item.weight < heap[i / 2].weight)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

Edge delete_min_heap(int* n) {
	int parent, child;
	Edge item, temp;
	if ((*n) == 0) {
		fprintf(stderr, "The heap is empty");
		exit(1);
	}

	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= *n) {
		if ((child < *n) && (heap[child].weight > heap[child + 1].weight)) {
			child++;
		}
		if (temp.weight <= heap[child].weight) {
			break;
		}
		heap[parent] = heap[child]; //위 아래 자리 바꾸기
		parent = child; //parent라는 매개체도 child쪽으로 내려옴
		child *= 2; //child도 한칸 내려감
	}
	heap[parent] = temp;
	return item;
}

int Find(int index) {
	if(parent[index] == -1){
		return index;
	}
	parent[index] = Find(parent[index]);
	return parent[index];
}