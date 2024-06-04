#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdio>

#pragma warning(disable: 4996)

int main() {
	FILE* f = fopen("hello.txt", "r");
	char c;
	double number;
	int n = fscanf(f, "%c", &c);
	fclose(f);

	printf("word = %c, n = %d", c, n);


	return 0;
}