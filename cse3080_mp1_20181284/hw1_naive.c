#include <stdio.h>
#include <string.h>

#define MAX_STRING 10000000
#define MAX_PAT 3000
char str[MAX_STRING];
char pat[MAX_PAT];
int arr_start[MAX_STRING];

int nfind(char* string, char* pat);

int main() {
	FILE* inFp1, * inFp2, * outFp;
	int count;
	inFp1 = fopen("string.txt", "r");
	if (inFp1 == NULL) {
		printf("The string file does not exist.\n");
		return 1;
	}
	inFp2 = fopen("pattern.txt", "r");
	if (inFp2 == NULL) {
		printf("The pattern file does not exist.\n");
		return 1;
	}
	outFp = fopen("result_naive.txt", "w");
	if (outFp == NULL) {
		printf("result_naive.txt open error!\n");
		return 1;
	}
	fgets(str, MAX_STRING, inFp1);
	fgets(pat, MAX_PAT, inFp2);

	if (strlen(str) < strlen(pat)) {
		return -1;
	}
	count = nfind(str, pat);

	fprintf(outFp, "%d\n", count);
	for (int k = 0; k < count; k++) {
		fprintf(outFp, "%d ", arr_start[k]);
	}
	fprintf(outFp, "\n");

	fclose(inFp1);
	fclose(inFp2);
	fclose(outFp);

	return 0;
}

int nfind(char* string, char* pat) {
	int i, j = 0;
	int start = 0;
	int lasts = strlen(string) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;
	int count = 0;
	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		if (string[endmatch] == pat[lastp]) {
			for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++);
		}
		if (j == lastp) {
			arr_start[count] = start;
			count++;
		}
	}

	return count;
}