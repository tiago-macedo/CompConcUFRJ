# Laboratório 3

O programa **pi** calcula pi realizando o somatório da série _1/(2*n - 1)_ para _n_ de 1 a _N_. Um dos somatórios é realizado sequencialmente, enquanto o outro é realizado concorrentemente. O usuáio passa a quantidade de termos da soma, _N_, e a quantidade de threads a serem criadas na parte concorrente do programa, como parâmetros de linha de comando.


## Estratégia de concorrência

Cada thread soma  os termos de *n\_threads* em *n_threads* (a quantidade de threads presentes). Assim, havendo 4 threads, a primeira somará os termos de índices 1, 5, 9...; a segunda somará os de índices 2, 6, 10...; e por aí vai. Cada thread retorna, para o fluxo principal do programa, o resultado de seu somatório. O fluxo principal, por fim, soma o valor de retorno de cada thread.


## Esratégias de precisão

Como todas as threads processam tanto os termos de grande magnitude (no começo do somatório) quando os de pequena magnitude (no fim do somatório), seus resultados não posuem grande diferença de magnitude entre si. Isso evita perda de precisão ao realizarmos o somatório final dos valores de saída das threads, já que isso ocorre quando tentamos somar ou subtrair valores de grade e pequena magnitudes.


## Metodologia de teste

Usando `make`, compilei o executável **pi** sem flags de otimização. O script `runtests.sh` executa o programa com uma série de combinações diferentes de parâmetros de entrada, cinco vezes para cada combinação, colocando o resultado no arquivo `output`. Executei o script em uma janela de terminal, sem deixar mais nada aberto. Segue, abaixo, os resultados resumidos destes testes, levando em consideração apenas as execuções mais rápidas de cada combinação de parâmetros.


## Resultados

| N (termos)     | threads | T<sub>seq</sub>    | diff<sub>seq</sub> | T<sub>conc</sub>   | diff<sub>conc</sub> | aceleração    |
| -------------- | ------- | ------------------ | ------------------ | ------------------ | ------------------- | ------------- |
| 10<sup>3</sup> | 2       | 0.000013678996766s | 9.999998e-04       | 0.000323293003021s | 9.999998e-04        | 0.0423114532  |
| 10<sup>3</sup> | 4       | 0.000010978998034s | 9.999998e-04       | 0.000331250004820s | 9.999998e-04        | 0.03314414453 |
| 10<sup>5</sup> | 2       | 0.001130182004999s | 1.000000e-05       | 0.000808404001873s | 1.000000e-05        | 1.39804108142 |
| 10<sup>5</sup> | 4       | 0.000602796993917s | 1.000000e-05       | 0.000526101997821s | 1.000000e-05        | 1.1457797089  |
| 10<sup>7</sup> | 2       | 0.061804675999156s | 1.000000e-07       | 0.033135419995233s | 1.000000e-07        | 1.86521480663 |
| 10<sup>7</sup> | 4       | 0.060013909998816s | 1.000000e-07       | 0.015868028000114s | 1.000000e-07        | 3.78206479081 |
| 10<sup>9</sup> | 2       | 5.656502956997429s | 9.999979e-10       | 2.841934793999826s | 9.999580e-10        | 1.99037042262 |
| 10<sup>9</sup> | 4       | 5.652695350996510s | 9.999979e-10       | 1.506822136005212s | 9.999978e-10        | 3.75140185157 |

Onde:

-   **diff<sub>seq</sub>** e **diff<sub>conc</sub>** são os erros totais nos valores de Pi calculados pelas partes sequecial e concorrente do programa, comparados à macro `M_PI` da livraria `math.h`.