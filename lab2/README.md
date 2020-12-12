# Laboratório 2

## Estratégia de escalonamento de threads

Cada matriz é, internamente, um array de floats. Assim, o elemento na linha _i_ coluna _j_ da matriz _M_ é acessado por `M[dim*i + j]`, onde _dim_ é a dimensão (largura e altura) da matriz (considerando apenas matrizes quadradas). Por sua vez, se utilizarmos um índice _k_ para percorrer o vetor _M_, temos a relação `M[k] = M[k/dim][k%dim]`.

Essa relação entre a representação bisimensional de matrizes (`M[i][j]`) e sua implementação (`M[k]`) é importante para compreendermos a divisão de subtarefas pelas threas: na multiplicação de matrizes `A * B = C` a thread de índice _id_ será responsável por calcular o elemento `C[id + n*dim]` para `n = 0, 1, ...`.
