#include "stdio.h"
#include "stdlib.h"

void poisk(int *coll, int y)
{
  int bol = 0;
  for (int uky = 0; uky < y; uky++)
  {
    if (coll[uky] > bol) {
      bol = coll[uky];
    }
  }
  for (int uky = 0; uky < y; uky++)
  {
    if (coll[uky] == bol) {
      printf("%d ", uky);
    }
  }
}

void massiv(int** graph, int x, int y) {
  int* coll = (int*) calloc(sizeof(int), y);
  if (coll == NULL) {
    printf("Error\n");
    exit(1);
  }

  for (int j = 0; j < y; j++) {
    for (int i = 0; i < x; i++) {
      if (graph[j][i] == 1) {
        ++coll[j];
      }
    }
  }
  poisk(coll, y);
}

void paint_gr(int** graph, int x, int y) {
  FILE* output = fopen("out.dot", "w");
  int fir;
  int flversh;
  int* soed = (int*) calloc(sizeof(int), y);
  if (soed == NULL) {
    printf("Error\n");
    exit(1);
  }
  fprintf(output, "graph {\n");
  for (int i = 0; i < x; i++) {
    flversh = 0;
    for (int j = 0; j < y; j++) {
      if (graph[j][i] == 1) {
        if (flversh > 0) {
          fprintf(output, " -- %d", j);
        }
        else {
          fprintf(output, "%d", j);
          fir = j;
        }
        ++soed[j];
        ++flversh;
      }
    }
    if (flversh > 2) {
      printf("Incorrect matrix\n");
      exit(1);
    }
    if (flversh == 1) {
      fprintf(output, " -- %d", fir);
    }
    if (flversh > 0) {
      fprintf(output, " [label = %d]\n", i);
    }
  }
  for (int j = 0; j < y; j++) {
    if (soed[j] == 0) {
      fprintf(output, "%d\n", j);
    }
  }
  fprintf(output, "}");
  fclose(output);
  system("dot -T png out.dot -o picture.png && sxiv picture.png");
}

int main(void)
{
  FILE* input = fopen("incend.txt", "r");

  int** graph;
  char c;
  int x, y;

  fscanf(input ,"%d %d", &y, &x);

  graph = (int**) malloc(sizeof(int*)*y);
  if (graph == NULL) {
    printf("Error\n");
    exit(1);
  }
  for (int i = 0; i < y; i++) {
    graph[i] = (int*)malloc(sizeof(int)*x);
    if (graph[i] == NULL) {
      printf("Error\n");
      exit(1);
    }
  }

  while (c != '\n') {
    c = fgetc(input);
  }

  int ukx = 0;
  int uky = 0;
  while ((c = fgetc(input)) != EOF) {
    if ((uky >= y) || (ukx > x)) {
      printf("Incorrect data\n");
      exit(1);
    }
    switch (c) {
      case '1':
        graph[uky][ukx] = 1;
        ++ukx;
        break;
      case '0':
        graph[uky][ukx] = 0;
        ++ukx;
        break;
      case ' ':
        continue;
        break;
      case '\n':
        if (ukx < x) {
          printf("Incorrect data\n");
          exit(1);
        }
        ukx = 0;
        ++uky;
        break;
      default:
        printf("Incorrect symbol\n");
        exit(1);
        break;
    }
  }
  fclose(input);

  paint_gr(graph, x, y);

  massiv(graph, x, y);

  printf("\n");

  return 0;
}
