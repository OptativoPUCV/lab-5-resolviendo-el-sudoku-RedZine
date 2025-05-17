#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

  // Primero verificamos filas 
  
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      int num = n->sudo[i][j];
      if (num != 0){
        for (int k = 0; k < 9; k++){
          if (k != j && n->sudo[i][k] == num) return 0;
        }
      }
    }
  }

  // Ahora Columnas:

  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      int num = n->sudo[j][i];
      if (num != 0){
        for (int k = 0; k < 9; k++){
          if (k != j && n->sudo[k][i] == num) return 0;
        }
      }
    }
  }

  // Ahora submatrices 3x3:

  for (int i = 0; i < 3; i++){
    for (int j = 0 ; j < 3 ; j++){
      int FilaInicial = i * 3;
      int ColumnaInicial = j * 3;

      for (int k = 0 ; k < 9 ; k++){
        int fila = FilaInicial + (k/3);
        int col = ColumnaInicial + (k%3);
        int num = n->sudo[fila][col];
        if (num != 0){
          for (int m = 0; m < 9 ; m++){
            int a = FilaInicial + (m/3);
            int b = ColumnaInicial + (m%3);
            if ((a != fila || b != col) && n->sudo[a][b] == num) return 0;
          }
        }
      }
    }
  }
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();

    for (int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){
        if (n->sudo[i][j] == 0){
          for (int num = 1; num <= 9; num++){
            Node* NuevoNodo = copy(n);
            NuevoNodo->sudo[i][j] = num;

            if (is_valid(NuevoNodo)) pushBack(list, NuevoNodo);
            else free(NuevoNodo);
          }
          return list;
        }
      }
    }
    return list; // Retornamos la lista con los nodos adyacentes :p
}



int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/