# Laboratório 2

## Estratégia de escalonamento de threads

Cada matriz é, internamente, um array de floats. Assim, o elemento na linha _i_ coluna _j_ da matriz _M_ é acessado por `M[dim*i + j]`, onde _dim_ é a dimensão (largura e altura) da matriz (considerando apenas matrizes quadradas). Por sua vez, se utilizarmos um índice _k_ para percorrer o vetor _M_, temos a relação `M[k] = M[k/dim][k%dim]`.

Essa relação entre a representação bisimensional de matrizes (`M[i][j]`) e sua implementação (`M[k]`) é importante para compreendermos a divisão de subtarefas pelas threas: na multiplicação de matrizes `A * B = C` a thread de índice _id_ será responsável por calcular o elemento `C[id + n*dim]` para `n = 0, 1, ...`.

O argumento passado a cada thread é um struct que acabou contendo apenas um campo: _id_ (número inteiro). As demais informações utilizadas por cada thread são variáveis globais, afim de evitar duplicatas de dados.

## Detalhes de implementação

É recomendado compilar o programa usando Make. Existem duas opções:

1. `make` ou `make build`: compila um executável **matrix** que inicializa as matrizes com valores aleatórios entre `MAX = 100` e `MIN = -100`. Com esta opção, o executável mostra na tela apenas os tempos de duração de cada etapa. A compilação recebe optimização (flag `-O3`).
2. `make debug`: Com esta opção, o executável inicializa as matrizes de entrada com todos os elementos iguais a 1 (afim de facilitar a verificação da corretude do programa). Além disso, o executável exibe as matrizes de entrada e saída, além de avisar quando ocorre criação de threads e qual elemento da matriz de saída está sendo calculado por qual thread. Por fim, com esta opção, o programa não recebe flag de optimização.

# Resultados

O script `runtests.sh` é usado para executar o programa **matrix** (compilado com `make build`) cinco vezes para cada combinação de dimensão e número de threads. As dimensões usadas foram 500, 1000 e 2000. Os números de threads usados foram 1, 2 e 4. O script coloca a saída dessas execuções num arquivo de texto chamado `output`.

Fechei todos os programas do meu computador, exceto dois terminais: um para executar `runtests.sh`, e o outro para observar o estado do arquivo `output` usando o programa `tail`. Um exemplo de `output` é incluido no repositório.

Segue abaixo duas tabelas mostrando a aceleração (![equation](https://latex.codecogs.com/gif.latex?%5Cinline%20T_%7Bseq%7D/T_%7Bconc%7D)) obtida ao usar-se duas e quatro threads. Considerei, das 5 execuções para cada combinação de parâmetros, apenas a mais rápida.

| Dimensão | Tempo com 1 thread | Tempo com 2 threads | Aceleração      |
| -------- | ------------------ | ------------------- | --------------- |
| 500      | 1.162550           | 0.094736            | 12.2714701908\* |
| 1000     | 7.202354           | 3.682679            | 1.95573765729   |
| 2000     | 62.472828          | 32.545589           | 1.9195482374    |

| Dimensão | Tempo com 1 thread | Tempo com 4 threads | Aceleração      |
| -------- | ------------------ | ------------------- | --------------- |
| 500      | 1.162550           | 0.089437            | 12,9985352818\* |
| 1000     | 7.202354           | 3.682679            | 1.95573765729   |
| 2000     | 62.472828          | 32.545589           | 1.9195482374    |

