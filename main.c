#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h> // clock()
#include <unistd.h> // sleep()

typedef struct Especime {
  char dna;
  char tipo[20];
} Especime;

typedef struct Resultado {
  char letraEncontrada;
  int posI;
  int posJ;
} Resultado;

// Prototipação
char* getDNAFromFile(char[]);
int checkDNA(char[]);
Resultado diagonalPrincipal(int subMatrixDim, char[subMatrixDim][subMatrixDim]);
Resultado diagonalSecundaria(int subMatrixDim, char[subMatrixDim][subMatrixDim]);
int checkDiagonais(int dim, int, char[][dim], int, int, int, int);
void printMatrix(char[]);
Resultado checkRows(int dim, char[dim][dim]);
Resultado checkCols(int dim, char[dim][dim]);
int isSimian(char[]);

int main(void) {
  double time = 0.0;
  clock_t begin = clock();
  
  // Interpreta as informações do arquivo e atribui à variável dnaStr
  char *dnaStr = getDNAFromFile("inputDNA.txt");

  // Verifica se o DNA do arquivo é válido
  if (checkDNA(dnaStr)) {
    // Cria o registro e atribui o DNA
    
    Especime *especime = malloc(strlen(dnaStr));
    strcpy(&especime->dna, dnaStr);

    // Exibe no console a sequência DNA em forma de matriz
    // printf("%s\n", &especime->dna);
    printMatrix(&especime->dna);

    // Chama as funções que verificam sequências de 4 moléculas iguais nas linhas, colunas e diagonais
    if (isSimian(&especime->dna)) {
      strcpy(especime->tipo, "simio");
    } else {
      strcpy(especime->tipo, "humano");
    }
    
    printf("Eh um %s\n", especime->tipo);
    free(especime);
  } 
  
  else {
    printf("O DNA inserido eh invalido");
  }

  clock_t end = clock();
  time += (double)(end - begin) / CLOCKS_PER_SEC;
  
   printf("Tempo de execucao: %fs\n", time);
  return 0;
}

char* getDNAFromFile(char path[]) {
  // Função que interpreta as informações do arquivo path[] e constrói um char[] contendo toda a sequência DNA. Cada caracter do arquivo é separado por um ' ', e o char[] resultante contém apenas os caracteres sem o espaçamento
  
  FILE *file = fopen(path, "r");

  // Verifica se o arquivo existe
  if (file == NULL) {
    printf("O arquivo de entrada nao existe");
    exit(-1);
  }

  char *firstRow = malloc(8);

  int dimensions, k = 0;

  // Lê a primeira linha para determinar o tamanho da linha e da coluna
  fgets(firstRow, 8, file);

  // Converte o número de char para int
  dimensions = atoi(firstRow);
  free(firstRow); // Libera a memória usada pela variável

  char *currentRow = (char*) malloc((dimensions * 2) * sizeof(char*));
  char *dna = malloc((dimensions * dimensions));

  for (int i = 0; i < dimensions; i++) {
    fgets(currentRow, dimensions * dimensions, file);
    for (int j = 0; j < (dimensions * 2 - 1); j++) {
      if (currentRow[j] != ' ') {
        // Concatena o caracter atual à string dna
        dna[k] = currentRow[j];
        k++;
      }
    }
  }

  fclose(file);

  return dna;
}

int checkDNA(char dna[]) {
  // Função que percorre o vetor dna[] e determina se o mesmo corresponde à uma sequência de dna válida. Considerando que para ser válida deve seguir o parâmetro de que haja somente moléculas A, G, C ou T, e nenhuma outra.
  
  char validMolecules[4] = "AGCT";
  for (int i = 0; i < strlen(dna); i++) {
    int diffMolecule = 0;
    for (int m = 0; m < strlen(validMolecules); m++) {
      if (dna[i] == validMolecules[m]) {
        break;
      } else {
        diffMolecule++;
      }
    }

    if (diffMolecule == 4) {
      // A molécula em questão é diferentes das 4 moléculas válidas de validMolecules[], logo, a sequência é inválida.
      return 0;
    } else {
      diffMolecule = 0;
    }
  }

  // Sequência válida
  return 1;
}

Resultado diagonalPrincipal(int subMatrixDim, char 
subMatrix[subMatrixDim][subMatrixDim]) {
  Resultado resultado;
  int i, cont;
  cont = 0;
  
  for (i = 0; i < subMatrixDim; i++) {
    if (subMatrix[i][i] == subMatrix[i + 1][i + 1]) {
      cont++;
      if(cont == (subMatrixDim-1)) {
        resultado.letraEncontrada = subMatrix[i][i];
        resultado.posI = i;
        resultado.posJ = i;
        return resultado;
      }
    } else {
      cont = 0;
    }
  }
  resultado.letraEncontrada = ' ';
  resultado.posI = -1;
  resultado.posJ = -1;
  return resultado;
}

Resultado diagonalSecundaria(int subMatrixDim, char 
subMatrix[subMatrixDim][subMatrixDim]) {
  Resultado resultado;
  int i, cont = 0;
  for (i = 0; i < subMatrixDim; i++) {
    if (subMatrix[i][subMatrixDim - 1 - i] == subMatrix[i + 1][subMatrixDim - 1 - (i + 1)]) {
      if(i != subMatrixDim-1) {
        cont++;
        if(cont == (subMatrixDim - 1)) {
          resultado.letraEncontrada = subMatrix[i][subMatrixDim-1-i];
          resultado.posI = i;
          resultado.posJ = subMatrixDim-1-i;
          return resultado;
        }
      }
    } else {
      cont = 0;
    }
  }
  resultado.letraEncontrada = ' ';
  resultado.posI = -1;
  resultado.posJ = -1;
  return resultado;
}

int checkDiagonais(int dim, int subMatrixDim, char matrix[dim][dim], int iI, int iF, int jI, int jF) {
  // Função que cria uma submatriz subMatrixDim de dimensões quadradas dim, que percorrerá a matriz matrix[dim][dim] em busca de sequências nas diagonais principais e secundárias. A submatriz percorrerá a matriz de acordo com os valores de iI (i inicial), iF (i final), jI (j inicial) e jF (j final). Caso não encontre sequência na submatriz atual, a função se auto-chama recursivamente, com valores diferentes de iI, iF, jI e jF até encontrar sequência, ou chegar no final da matriz.

  int result;
  int i, j;
  char subMatrixDNA[subMatrixDim][subMatrixDim];
  int contI, contJ;

  contI = contJ = 0; // Contadores relativos à submatriz atual

  for (i = iI; i < iF; i++, contI++) {
    for (j = jI; j < jF; j++, contJ++) {
      subMatrixDNA[contI][contJ] = matrix[i][j];
    }
    contJ = 0;
  }

  int contDiagP = 0;
  int contDiagS = 0;

  Resultado resultDiagonalPrincipal = diagonalPrincipal(subMatrixDim, subMatrixDNA);
  if(resultDiagonalPrincipal.letraEncontrada != ' ') {
    printf("Sequencia de %c na diagonal principal\nPosição final [%i, %i] \n", resultDiagonalPrincipal.letraEncontrada, i, j);
    return 1;
  }

  Resultado resultDiagonalSecundaria = diagonalSecundaria(subMatrixDim, subMatrixDNA);
  if(resultDiagonalSecundaria.letraEncontrada != ' ') {
    printf("Sequencia de %c na diagonal secundária\nPosição final [%i, %i] \n", resultDiagonalSecundaria.letraEncontrada, i-1, jI);
    return 1;
  }

  // Se ambos chegaram até o final
  if (iF == dim && jF == dim) {
    return 0;
  }

  if (iF <= dim && jF <= dim) {
    if (jF == dim) {
      result = checkDiagonais(dim, subMatrixDim, matrix, iI + 1, iF + 1, 0, 4);
    } else if (iF <= dim) {
      result = checkDiagonais(dim, subMatrixDim, matrix, iI, iF, jI + 1, jF + 1);
    }
  }

  // Verifica o resultado da função chamada para retornar o resultado final
  if(result == 1) {
    return 1;
  } else {
    return 0;
  }
}

void printMatrix(char dna[]) {
  // Função que, dada a sequência de DNA dna[], transforma na matriz matrix[dimension][dimension] e exibe no console os valores de dna[] em forma de tabela e separados por um espaço.
  int dimension = sqrt(strlen(dna));
  char matrix[dimension][dimension];

  int cont = 0;
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      matrix[i][j] = dna[cont];
      cont++;
    }
  }

  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      printf("%c ", matrix[i][j]);
    }
    printf("\n");
  }
}

Resultado checkRows(int dim, char matrix[dim][dim]) {
  // Checando repetições nas linhas
  Resultado resultado;
  int i, j, cont;
  cont = 0;
  
  for (i = 0; i < dim; i++) {
    for (j = 0; j < dim; j++) {
      if (j != (dim - 1)) {
        if (matrix[i][j] == matrix[i][j + 1]) {
          cont++;
          if (cont == 3) {
            resultado.letraEncontrada = matrix[i][j];
            resultado.posI = i;
            resultado.posJ = j;
            return resultado;
          }
        } else {
          cont = 0;
        }
      }
    }
  }
  resultado.letraEncontrada = ' ';
  resultado.posI = -1;
  resultado.posJ = -1;
  return resultado;
}

Resultado checkCols(int dim, char matrix[dim][dim]) {
  // Checando repetições nas linhas
  Resultado resultado;
  int i, j, cont;
  cont = 0;
  
  for (j = 0; j < dim; j++) {
    for (i = 0; i < dim; i++) {
      if (i != (dim - 1)) {
        if (matrix[i][j] == matrix[i + 1][j]) {
          cont++;
          if (cont == 3) {
            resultado.letraEncontrada = matrix[i][j];
            resultado.posI = i;
            resultado.posJ = j;
            return resultado;
          }

        } else {
          cont = 0;
        }
      }
    }
  }
  resultado.letraEncontrada = ' ';
  resultado.posI = -1;
  resultado.posJ = -1;
  return resultado;
}

int isSimian(char dna[]) {
  // Função que une as funções que verificam linhas, colunas, diagonais principais e secundárias para determinar se a sequência de DNA dna[] corresponde à uma sequência de um símio.
  
  int dimension = sqrt(strlen(dna));
  char matrix[dimension][dimension];
  int cont = 0;

  // Transforma dna[] em matrix[][]
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      matrix[i][j] = dna[cont];
      cont++;
    }
  }

  Resultado resultRows = checkRows(dimension, matrix);
  if (resultRows.letraEncontrada != ' ') {
    // Achou na linha
    printf("Sequencia de %c na linha %i\n", resultRows.letraEncontrada, resultRows.posI);
    return 1;
  }
  
  Resultado resultCols = checkCols(dimension, matrix);
  if(resultCols.letraEncontrada != ' ') {
    // Achou na coluna
    printf("Sequencia de %c na coluna %i\n", resultCols.letraEncontrada, resultCols.posJ);
    return 1;
  }
  
  if(checkDiagonais(dimension, 4, matrix, 0, 4, 0, 4)) {
    // Achou nas diagonais
    return 1; 
  }
  // Não é um símio
  return 0;
}


