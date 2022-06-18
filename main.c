#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char *getDnaFromFile(char path[]) {
  FILE *file = fopen(path, "r");

  // Verifica se o arquivo existe
  if(file == NULL) {
    printf("O arquivo de entrada não existe");
    exit(-1);
  }

  char *currentRow = malloc(20);
  
  int ROW, COL;

  // Lê a primeira linha para determinar o tamanho da linha e da coluna
  fgets(currentRow, 16, file);

  // Converte o número de char para int
  ROW = atoi(&currentRow[0]);
  COL = atoi(&currentRow[2]);

  char *dna = malloc(128);
  
  for(int i = 0; i < ROW; i++) {
    fgets(currentRow, 64, file);
    for(int j = 0; j < (COL*2 - 1); j++) {
      if(currentRow[j] != ' ') {
        // Concatena o caracter atual à string dna
        strncat(dna, &currentRow[j], 1);
      }
    }
  }
  
  fclose(file);
  
  return dna;
}

int checkDna(char dna[]) {
  char validMolecules[4] = "AGCT";
  for(int i = 0; i < strlen(dna); i++) {
    int diffMolecule = 0;
    for(int m = 0; m < strlen(validMolecules); m++) {
      if(dna[i] == validMolecules[m]) {
        break;
      } else {
        diffMolecule++;
      }
    }

    if(diffMolecule == 8){
      return 0;
    } else {
      diffMolecule = 0;
    }
  }
  
  return 1;
}

char **strToMatrixDNA(char *dnaString){
  char **matrix = malloc(512);

  int dimension = sqrt(strlen(dnaString));
  int cont = 0;
  
  for(int i = 0; i < 6; i++) {
    for(int j = 0; j < 6; j++) {
      printf("%i %i\n", i, j);
      matrix[i][j] = 'A';
      printf("cont: %i\n", cont);
      cont++;
    } 
  }
  printf("Terminei o for\n");
  return matrix;
}

void printCharMatrix(int dim, char matrix[dim][dim]) {
  for(int i = 0; i < 6; i++) {
    for(int j = 0; j < 6; j++) {
      printf("%c ", matrix[i][j]);
    }
    printf("\n");
  }
}

int checkSequence(int dim, char matrix[dim][dim]) {
  int cont = 0;
  int i, j;
  
  // Checando repetições nas linhas
  for(i = 0; i < dim; i++) {
    for(j = 0; j < dim; j++) {
      if(j!=(dim-1)) {
        if(matrix[i][j] == matrix[i][j+1]){
          cont++;
          if(cont == 4) {
            printf("Achei sequência de %c na linha %i\n", matrix[i][j], i);
            // return 1;
          }
          
        } else {
          cont = 0;
        }
      }
    } 
  }

  // Checando repetições nas colunas
  for(j = 0; j < dim; j++) {
    for(i = 0; i < dim; i++) {
      if(i != (dim-1)) {
        if(matrix[i][j] == matrix[i+1][j]){
          cont++;
          if(cont == 4) {
            printf("Achei sequência de %c na coluna %i\n", matrix[i][j], j);
            // return 1;
          }
          
        } else {
          cont = 0;
        }
      }
    } 
  }

  // Checando repetições na diagonal sentido inferior esquerdo para superior direito
  // A FAZER
  
  return 0;
}

int isSimian(char dna[]) {
  int dimension = sqrt(strlen(dna));
  char matrix[dimension][dimension];
  int cont = 0;
  
  // Transformando em matriz
  for(int i = 0; i < dimension; i++) {
    for(int j = 0; j < dimension; j++) {
      matrix[i][j] = dna[cont];
      cont++;
    } 
  }

  // Verificação de combinação nas linhas
  checkSequence(dimension, matrix);

  printCharMatrix(dimension, matrix);
  return 1;
}

int main(void) {
  char *dnaStr = getDnaFromFile("inputDNA.txt");

  printf("%s\n\n", dnaStr);

  // Ver depois se dá para transformar em uma função, pois a função strToMatrixDNA não funciona
  
  if(checkDna(dnaStr)) {
    if(isSimian(dnaStr)) {
      printf("É um símio");
    }
    
      
  } else {
    printf("O DNA inserido é inválido");
  }
  return 0;
}