#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

struct DLink {
	struct DLink* prev;
	int data;
	struct DLink* next;
};
typedef struct DLink* listPointer;

void print_forward(listPointer list);
void print_reverse(listPointer list);

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("usage: ./hw2 input_filename");

		return 0;
	}

	int n;
	listPointer head, cur, newnode, delnode;

	head = (listPointer)malloc(sizeof(struct DLink));
	head->data = INT_MIN;
	head->next = head;
	head->prev = head;

	cur = head;

	FILE* fp;
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("The input file does not exist.");

		return 0;
	}

	char command[10];
	while (fscanf(fp, "%s", command) != EOF) {
		if (strcmp(command, "INSERT") == 0) {
			fscanf(fp, "%d", &n);
			newnode = (listPointer)malloc(sizeof(struct DLink));
			newnode->data = n;
			newnode->next = NULL;
			newnode->prev = NULL;

			while (cur->data < newnode->data && cur->next != head) {
				cur = cur->next;
			}
			if (cur->data == newnode->data) {
				cur = head;
				continue;
			}
			if (cur->next == head) {
				if (cur->data < newnode->data) {
					cur->next = newnode;
					newnode->prev = cur;
					newnode->next = head;
					head->prev = newnode;
					cur = head;
				}
				else {
					cur->prev->next = newnode;
					newnode->prev = cur->prev;
					cur->prev = newnode;
					newnode->next = cur;
					cur = head;
				}
			}
			else {
				cur->prev->next = newnode;
				newnode->prev = cur->prev;
				cur->prev = newnode;
				newnode->next = cur;
				cur = head;
			}

			newnode = NULL;
			free(newnode);
		}
		else if (strcmp(command, "DELETE") == 0) {
			fscanf(fp, "%d", &n);
			if (cur->next != head) {
				while (cur->data != n && cur->next != head) {
					cur = cur->next;
				}
				if (cur->next != head) {
					delnode = cur;
					cur->prev->next = cur->next;
					cur->next->prev = cur->prev;
					cur = head;
					free(delnode);
				}
				else {
					cur = head;
				}
			}
		}
		else if (strcmp(command, "ASCEND") == 0) {
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			cur = cur->next;
			head->next = head;
			head->prev = head;
			print_forward(cur);
			head->next = cur;
			head->prev = cur->prev;
			cur->prev->next = head;
			cur->prev = head;
			cur = head;
		}
		else if (strcmp(command, "DESCEND") == 0) {
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			cur = cur->next;
			head->next = head;
			head->prev = head;
			print_reverse(cur);
			head->next = cur;
			head->prev = cur->prev;
			cur->prev->next = head;
			cur->prev = head;
			cur = head;
		}
	}
}

void print_forward(listPointer list) {
	listPointer curr;
	FILE* outfile;

	outfile = fopen("hw2_result.txt", "a");
	if (list) {
		curr = list;
		while (1) {
			fprintf(outfile, "%d ", curr->data);
			printf("%d ", curr->data);
			curr = curr->next;
			if (curr == list) break;
		}
	}
	fprintf(outfile, "\n");
	printf("\n");
	fclose(outfile);
}

void print_reverse(listPointer list) {
	listPointer curr;
	FILE* outfile;

	outfile = fopen("hw2_result.txt", "a");
	if (list) {
		curr = list->prev;

		while (curr != list) {
			fprintf(outfile, "%d ", curr->data);
			printf("%d ", curr->data);
			curr = curr->prev;
		}
		fprintf(outfile, "%d ", curr->data);
		printf("%d ", curr->data);
	}
	fprintf(outfile, "\n");
	printf("\n");
	fclose(outfile);
}