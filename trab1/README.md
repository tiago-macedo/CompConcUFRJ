# SC: Pesquisar em todos os arquivos

O programa que resolvi fazer para este trabalho pesquisa por uma série de caracteres em todos os arquivos no diretório passado, e em todos os subdiretórios deste.

Esta não foi uma boa escolha. Eu subestimei dramaticamente a quantidade de trabalho que esse programa iria requerer, e, como resultado, apesar de ter dedicadomuitas horas por dia e muitos dias a este projeto, não poderei entregá-lo completo.

O programa em si funciona. Eu até mesmo resolvi os vazamentos de memória. Para informação sobre como utilizá-lo, rode `./sc -h`. É possível escolher a quantidade de threads e o subdiretório no qual realizar a pesquisa.

## Estratégia de concorrência:

Inicialmente, cada thread é responsável por escanear alguns dos arquivos contidos pelo diretório raiz (de onde a busca começa). Especificamente, cada thread avança de `nthreads` em `nthreads` pelo array de arquivos. Em seguida, começa a parte recursiva.

O processo de entrar nos subdiretórios e escanear seus arquivos acontece por meio de uma função recursiva (`recSearch()`). É elaborada uma lista de subdiretórios do diretório raiz, e cada thread é responsável por rodar `recSearch()` nos subdiretórios que lhe foram escalonados. A repartição acontece de forma semelhante à repartição de arquivos.

Não há risco de condição de corrida pois cada thread "toma para si" uma subárvore diferente do diretório raiz. Além disso, o programa não segue links, afim de evitar links circulares.

## Como compilar:

- `make` compila o executável normalmente.
- `make debug` compila o executável para debugação por GDB.
- `make clean` deleta o executável.

## Problemas:

- Por algum motivo, o programa sofre falha de segmentação ao ser executado de fora de seu próprio diretório (`./trabalho1/sc abcde`). Não sei o que está causando esse bug, não tenho mais cabeça para programar por hoje, e a data final de entrega é hoje.
- O programa não mostra mais de um "match" por arquivo -- se você pesquisar por "elefante" e um arquivo conter essa palavra duas vezes, apenas a primeira será mostrada.
- É possível que algumas threads não sejam utilizadas, caso você peça para usar, por exemplo, 4 threads em uma pasta que só tem duas subpastas.
- A documentação, apesar de não ser a pior do mundo, não está perfeita, e está em Inglês -- é difícil pensar em Português e progamar em Inglês!
- Eu não fiz o relatório de ganho de velocidade.

Independentemente desses problemas -- admitidamente grandes -- eu me orgulho do resultado. Pretendo continuar desenvolvendo esse programa, debugando-o e adicionando mais opções, já que eu me vejo utilizando-o no dia-a-dia.
