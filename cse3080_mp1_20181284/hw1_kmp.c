#include <stdio.h>
#include <string.h>
#define MAX_STRING 10000000
#define MAX_PAT 3000
char str[MAX_STRING];
char pat[MAX_PAT];
int failure[MAX_PAT];
int arr_position[MAX_STRING];

int pmatch(char* string, char* pat);
void fail(char* pat);

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

	outFp = fopen("result_kmp.txt", "w");
	if (outFp == NULL) {
		printf("result_kmp.txt open error!\n");
		return 1;
	}


	fgets(str, MAX_STRING, inFp1);
	fgets(pat, MAX_PAT, inFp2);

	if (strlen(str) < strlen(pat)) {
		return -1;
	}

	fail(pat);
	count = pmatch(str, pat);

	fprintf(outFp, "%d\n", count);
	for (int k = 0; k < count; k++) {
		fprintf(outFp, "%d ", arr_position[k]);
	}
	fprintf(outFp, "\n");

	fclose(inFp1);
	fclose(inFp2);
	fclose(outFp);

	return 0;
}

int pmatch(char* string, char* pat) {
	int i = 0, j = 0;
	int count = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while (i < lens) {
		while (i < lens && j < lenp) {
			if (string[i] == pat[j]) {
				i++;
				j++;
			}
			else if (j == 0) {
				i++;
			}
			else {
				j = failure[j - 1] + 1;
			}
		}
		if (j == lenp) {
			arr_position[count] = i-lenp;
			count++;
			i = i - lenp +1;
			j = 0;
		}
	}
	return count;
}

void fail(char* pat) {
	int i, n = strlen(pat);
	failure[0] = -1;
	for (int j = 1; j < n; j++) {
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0)) {
			i = failure[i];
		}
		if (pat[j] == pat[i + 1]) {
			failure[j] = i + 1;
		}
		else {
			failure[j] = -1;
		}
	}
}