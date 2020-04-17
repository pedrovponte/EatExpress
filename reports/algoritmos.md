# Perspetiva de Implementação
 
## Caminho mais curto entre dois vértices
 
Em cada uma das fases de análise deliberadas pode-se seguramente realçar como problemática comum a do caminho mais curto entre dois vértices numa rede viária. Em particular, enquadram-se perfeitamente nesta problemática a necessidade de, aquando da realização de um pedido, determinar o percurso que permite proceder à sua entrega recorrendo ao trajeto de menor distância, o que implicará:
- determinar o percurso mais curto que está disponível para cada um dos estafetas alcançar o restaurante do qual o pedido foi solicitado
- calcular o trajeto de menor distância entre o restaurante e o ponto de entrega especificado pelo cliente
 
Assim, é pertinente analisar a variedade de algoritmos e alternativas de implementação disponíveis para o cálculo do caminho mais curto entre dois vértices. Só a realização desta análise prévia tornará possível perceber o impacto das vantagens e desvantagens de cada algoritmo e das suas variantes no contexto da temática a ser trabalhada.
Salienta-se, portanto, que nenhum algoritmo a ser considerado na fase de implementação deve ser, ainda numa fase experimental, tomado como solução ideal, pois a sua aplicabilidade está dependente da dimensão e tipologia dos grafos de entrada e de uma análise cuidada da sua eficiência temporal e espacial para cada caso.
 
###  Algoritmos considerados
 
#### Dijkstra Unidirecional
 
A primeira alternativa de solução que pretendemos testar no que diz respeito à eficiência temporal e aplicabilidade no contexto do problema passa essencialmente pela implementação de uma das múltiplas variantes do algoritmo de Dijkstra.
Este algoritmo ganancioso poderá ser vantajoso na medida em que procura a cada iteração obter o melhor resultado possível, em particular minimizar a distância percorrida. Para além disso é logicamente aplicável ao grafo que será utilizado como dado de entrada, já que este se trata de um grafo dirigido - cada aresta representa uma via unidirecional; e pesado - o peso de uma aresta representa uma distância.
A variante a implementar permite, recorrendo a uma fila de prioridades (heap com mínimo à cabeça) como estrutura auxiliar, obter a distância mínima desde o vértice de origem até todos os outros vértices do grafo, obtendo-se um tempo de execução de O((|V|+|E|) * log |V|). Este tempo resulta das |V| operações executadas na fila de prioridade (inserções/extrações), realizadas cada uma em tempo logarítmico e da utilização da operação "Decrease-Key" realizada no máximo uma vez por aresta e que é executada em tempo logarítmico para a fila de |V| elementos.
Note-se que, em todas as fases previamente definidas há necessidade de aplicar o algoritmo mais do que uma vez:
- considerando como vértice de origem a posição atual de cada um dos estafetas disponíveis para efetuar a entrega de um pedido
- assumindo que o vértice de origem é o restaurante no qual foi solicitada a entrega de um pedido
 
No entanto, o que se pretende realmente é utilizar o algoritmo de Dijkstra como base para encontrar o caminho mais curto entre dois pontos, pelo que se vai descobrir o caminho mais curto do vértice de origem para todos os outros terminando o algoritmo quando se for processar o vértice que procuramos, uma otimização que evita continuar a processar vértices quando já se descobriu o caminho pretendido.
Assim, como nas duas primeiras fases de implementação a escolha do estafeta a realizar o pedido depende exclusivamente da sua proximidade do restaurante do qual este foi solicitado, é necessário determinar, em primeiro lugar, o caminho mais curto para cada um dos estafetas se deslocar até ao restaurante, sendo o vértice de destino logicamente o restaurante. Seguidamente, aplica-se o algoritmo novamente para encontrar o percurso mais curto do restaurante à morada escolhida para o ato de entrega, usando o vértice de destino correspondente à morada indicada pelo cliente.
 
Espera-se, ao aplicar este algoritmo em alguns casos específicos, entre os quais mapas de estradas com poucos vértices e a distâncias curtas, obter tempos de execução razoáveis. No entanto, para trajetos longos e mapas de estradas complexos, a utilização do algoritmo de Dijkstra na sua variante unidirecional, gerará certamente tempos de execução demasiado longos, o que nos levará provavelmente a experimentar otimizações e algoritmos que permitam obter com maior eficácia temporal o caminho mais curto para entrega de um pedido.
 
#### Dijkstra Bidirecional
 
Uma das otimizações que se procura explorar com mais detalhe na fase de implementação para o algoritmo de Dijkstra, tendo em conta que o resultado esperado para a variante unidirecional não é o desejado, é a variante bidirecional. A execução alternada do algoritmo de Dijkstra no sentido do vértice de origem para o de destino e no sentido inverso poderá trazer vantagens no que diz respeito ao tempo de execução, esperando-se que este seja reduzido a metade em comparação com a variante do algoritmo que utiliza pesquisa unidirecional.
Esta melhoria deriva do facto de a área processada diminuir para metade , já que a pesquisa passa a ser executada nas duas direções, mantendo-se sempre a distância mais curta descoberta até ao momento e verificando-se ao processar uma aresta já processada previamente na direção oposta se foi descoberta uma distância menor.
Deste modo, a variante bidirecional do algoritmo de Dijkstra vai ser aplicada com o intuito de melhorar o tempo de cálculo do percurso mais curto entre estafeta e restaurante e, posteriormente, entre restaurante e local de entrega.
 
 
*(... pode-se indicar que na terceira fase se vai conjugar os algoritmos com certas restrições específicas do problemade de modo a não privilegiar apenas a distância do estafeta ao restaurante mas também a capacidade que este pode transportar e o tipo de veículo... )*
 
#### Algoritmo A*
 
O algoritmo A* será também objeto de estudo na fase de implementação não só por ser mais um algoritmo que permite calcular o caminho mais curto entre 2 vértices, mas essencialmente por a sua performance se diferenciar do algoritmo de Dijkstra pelo facto de recorrer a heurísticas para manipular os pesos das arestas e, assim afetar os nós que são expandidos.
Antes de mais, é essencial escolher cuidadosamente a heurística a utilizar pelo facto de esta ter um papel determinante no comportamento do algoritmo e nos resultados obtidos.
*(... a completar... )*
