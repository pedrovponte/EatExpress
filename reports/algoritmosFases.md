# Perspetiva de Implementação

## Caminho mais curto entre dois vértices

Em cada uma das fases de análise deliberadas pode-se seguramente realçar como problemática comum a resolução do problema do caminho mais curto entre dois vértices numa rede viária, particularmente o cálculo do percurso de menor distância entre um restaurante e um ponto de entrega aquando da realização de um pedido.

Por este motivo, é pertinente analisar a variedade de algoritmos e alternativas de implementação disponíveis. Só a realização desta análise prévia tornará possível perceber o impacto que as vantagens e desvantagens associadas à implementação de cada algoritmo e a cada uma das suas variantes terá no contexto da temática a ser trabalhada.  

###  Algoritmos considerados

#### Dijkstra Unidirecional

A primeira alternativa de solução que pretendemos testar no que diz respeito à eficiência temporal e aplicabilidade no contexto do problema passa essencialmente pela implementação de uma das múltiplas variantes do algoritmo de Dijkstra.
Este algoritmo ganancioso poderá ser vantajoso na medida em que procura a cada iteração obter o melhor resultado possível, em particular minimizar a distância percorrida. Para além disso é logicamente aplicável ao grafo que será utilizado como dado de entrada, já que este se trata de um grafo dirigido - cada aresta representa uma via unidirecional; e pesado - o peso de uma aresta representa uma distância.
A variante a implementar permite, recorrendo a uma fila de prioridades (heap com mínimo à cabeça) como estrutura auxiliar, obter a distância mínima desde o vértice de origem, neste caso o restaurante, até todos os outros vértices do grafo, obtendo-se um tempo de execução de O((|V|+|E|) * log |V|). Este tempo resulta das |V| operações executadas na fila de prioridade (inserções/extrações), realizadas cada uma em tempo logarítmico e da utilização da operação "Decrese-Key" realizada no máximo uma vez por aresta e que é executada em tempo logarítmico para a fila de |V| elementos.

No entanto, o que se pretende realmente é utilizar o algoritmo de Dijkstra como base para encontrar o caminho mais curto entre dois pontos, pelo que se vai descobrir o caminho mais curto do restaurante para todos os outros terminando o algoritmo quando se for processar o vértice correspondente à morada de entrega do pedido, uma otimização que evita continuar a processar vértices quando já se descobriu o caminho pretendido.
Espera-se, ao aplicar este algoritmo em alguns casos específicos, entre os quais mapas de estradas com poucos vértices e a distâncias curtas, obter tempos de execução razoáveis. No entanto, para trajetos longos e mapas de estradas complexos, a utilização do algoritmo de Dijkstra na sua variante unidirecional, gerará certamente tempos de execução demasiado longos, o que nos levará provavelmente a experimentar otimizações e algoritmos que permitam obter o caminho mais curto entre o restaurante e o ponto de entrega de um pedido com maior eficácia temporal.

#### Dijkstra Bidirecional

Uma das otimizações que se procura explorar com mais detalhe na fase de implementação para o algoritmo de Dijkstra, tendo em conta que o resultado esperado para a variante unidirecional não é o desejado, é a variante bidirecional. A execução do algoritmo de Dijkstra no sentido do vértice de origem - restaurante; para o de destino - ponto de entrega do pedido; e no sentido inverso poderá trazer vantagens no que diz respeito ao tempo de execução, esperando-se que este seja reduzido a metade em comparação com a variante do algoritmo que utiliza pesquisa unidirecional.
Esta melhoria deriva do facto de a área processada diminuir para metade , já que a pesquisa passa a ser executada nas duas direções, mantendo-se sempre a distância mais curta descoberta até ao momento e verificando-se ao processar uma aresta já processada previamente na direção oposta se foi descoberta uma distância menor.

#### Algoritmo A*

O algoritmo A* será também objeto de estudo na fase de implementação não só por ser mais um algoritmo que permite calcular o caminho mais curto entre 2 vértices, mas essencialmente por a sua performance se diferenciar do algoritmo de Dijkstra pelo facto de recorrer a heurísticas para manipular os pesos das arestas e, assim afetar os nós que são expandidos.
Antes de mais, é essencial escolher cuidadosamente a heurística a utilizar pelo facto de esta ter um papel determinante no comportamento do algoritmo e nos resultados obtidos.
...