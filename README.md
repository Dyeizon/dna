# Símios
Trabalho final da disciplina de Algoritmos<br>
<b>Aluno</b>: Dyeizon Procopiuk da Silva<br>

## Instruções de uso

### Entrada de dados
O algoritmo recebe uma matriz quadrada a partir de uma arquivo `.txt` chamado `inputDNA.txt` que corresponda ao seguinte modelo: <br>

X <br>
A T G C G A A<br>
C G A T G C G<br>
T A C T G T G<br>
A G A C G G G<br>
C A C C C A T<br>
T C A C T G C<br>
A A G A A G A<br>
<br>
Sendo: <br>
`X (int)` a quantidade de linhas e colunas da matriz <br>
E as próximas X linhas seguintes contendo a matriz quadrada a ser analisada, sendo cada elemento do tipo `char` e separados por um espaço entre cada elemento, e uma quebra de linha entre cada linha. <br>

Um arquivo modelo pode ser encontrado nos arquivos do repositório, nele contém uma matriz quadrada 25x25 já testada, e que consta como "símio" por conter uma repetição em uma das diagonais principais.

### Saída de dados
O algoritmo informa ao usuário sobre o tipo de espécie do DNA analisado (humano ou símio). Caso seja símio, o algoritmo também informa ao usuário o local em que a repetição de bases nitrogenadas foi encontrada. <br>
OBS: No main há uma pedaço de código comentado que exibe no console a matriz, caso desejar, pode retirar o comentário para visualizar melhor.<br>
