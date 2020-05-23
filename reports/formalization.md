# 2. Formalização

## 2.1 Problematização

Em primeiro lugar, convém dividir todas as questões relativas aos vários componentes da aplicação. 

O que se pretende com esta análise é garantir a máxima eficiência na implementação de um algoritmo que permita criar e gerir, de forma rápida e precisa, as rotas dos estafetas de entrega de comida, entre as localizações dos restaurantes e as localizações dos clientes que efetuaram os pedidos. 

Não serão equacionadas as implementações da interface da aplicação, ao nível do utilizador, nem serão alvo de análise todos os aspetos não relacionados com grafos, ou algoritmos não abordados.

Assim sendo, o problema reduzir-se-á a encontrar os caminhos mais curtos entre pontos/vértices, num mapa de atuação pré-escolhido, e, por fim, tendo em conta as diversas variantes do problema, definir rotas que permitam navegar pelos percursos, percorrendo a menor distância possível.

## 2.2 Estratificação

A estratégia a seguir, para a resolução deste problema, sugere a divisão do conceito em fases de análise, de implementação e de deliberação. No entanto, como pré-estabelecida tomamos a ideia de que um estafeta em trabalho, antes de receber a sua rota, pode estar localizado num qualquer ponto do mapa. Esta e a generalização de que existirão sempre, no mínimo, um restaurante e uma localização de um cliente como pontos integrantes da rota, serão o ponto de partida para a análise que se segue.

Convém definir, também, o perfil do estafeta, enquanto entidade que se move pelo percurso estabelecido, com características próprias que serão definidas pelo meio de transporte em que se desloca e pela capacidade máxima que pode transportar. Estas condicionantes influenciarão a escolha da rota e serão tidas em conta, antes de o estafeta iniciar a entrega dos pedidos. 
É imperativo realçar também que, em qualquer percurso, o levantamento dos pedidos nos restaurantes terá de ser efetuado antes da sua entrega aos clientes, por uma questão de fiabilidade e praticabilidade real da situação.

Outro aspeto importante é a existência de zonas de desconectividade, nos mapas - a existência de obstáculos à circulação, particularmente, a ocorrência de obras na via pública, que pode inviabilizar o acesso a certas moradas e restaurantes, ao tornar zonas inacessíveis. Também isto será tido em conta, aquando da esquematização dos algoritmos.

Numa última nota, destaca-se a possível predeterminação de todos os restaurantes e estafetas registados na plataforma. Este detalhe será substancialmente importante para a adoção de determinados algoritmos, sobretudo se se impuser, ou não, com base na estratégia a utilizar, um pré-processamento dos dados, em particular, a cada novo registo, de uma destas entidades, na plataforma.

#### 2.2.1 Fase I

Na sua simplicidade, consideramos a existência de apenas um estafeta, que realiza, sequencialmente, os percursos que lhe são impostos. Nesta fase, de modo a focar a análise na essência do problema, será considerado um meio de transporte qualquer e desvalorizada a capacidade de transporte. Na sua medida, o único funcionário terá rotas na qual concretizará o levantamento de pedidos, nos restaurantes, e a sua entrega, na morada dos clientes. Será, portanto, considerado o caso atómico de um estafeta que entrega apenas um pedido, entre um restaurante e a morada de um cliente.

#### 2.2.2 Fase II

Nesta fase, serão considerados vários estafetas que utilizam o mesmo meio de transporte e para os quais é delineado um percurso. Aqui, estaremos perante a distribuição simultânea de pedidos, com a avaliação de todas as condicionantes relacionadas com o problema, nesta fase. 
Os pedidos estarão, logicamente, organizados numa escala temporal, ficando encarregue por um dado pedido o estafeta que se encontre mais perto do restaurante a ele associado.

#### 2.2.3 Fase III

Esta fase coincidirá com a implementação de variados meios de transporte, o que poderá corresponder à utilização de diferentes mapas, para atender às características das múltiplas entidades que entregarão os pedidos e, em simultâneo, às características das diversas vias. Será igualmente imprescindível ter em conta a capacidade máxima que cada estafeta pode transportar, pois a dimensão da encomenda passa a ser determinante na atribuição dos pedidos. 
Assim, nesta fase, a atribuição de um pedido a um estafeta fica a depender não só da sua proximidade ao restaurante, mas também das características próprias do meio de transporte por ele utilizado, preferindo-se os meios mais rápidos para encomendas que impliquem deslocações maiores e atribuindo as encomendas de maior dimensão aos estafetas com maior capacidade de transporte.

Para agilizar todo o processo, tendo em conta os múltiplos fatores envolvidos na seleção de um estafeta para a realização de um pedido, optar-se-á, numa pré-seleção, por excluir estafetas que não tenham capacidade para o transportar. Seguidamente, como não se pretende ocupar estafetas com encomendas de dimensão muito inferior à sua capacidade máxima de transporte, por poderem ser necessários para os pedidos seguintes, terá que se avaliar, simultaneamente, a capacidade máxima de transporte de cada estafeta e a sua distância ao restaurante. Para isso, será atribuído um peso de 50% a cada um destes fatores, aquando da escolha entre estafetas para a realização de um pedido. 
Para além disso, ao avaliar a possibilidade de escolha dos estafetas, será necessário definir uma distância máxima para aqueles que se desloquem a pé, ou de bicicleta, já que a utilização destes meios de transporte para longas distâncias, apesar de não se refletir na distância total percorrida, resultaria, em situações reais, num tempo de entrega extremamente longo.

Por fim, consideraremos também a possibilidade de um pedido englobar vários restaurantes. Mais uma vez, isto implicará escolher, em primeiro lugar, os estafetas elegíveis, com base na sua disponibilidade para transportar a dimensão do pedido. Posteriormente, delinear-se-á a melhor opção de percurso para cada estafeta recolher o pedido dos vários restaurantes e entregá-lo ao cliente, considerando todas as restrições descritas anteriormente, no que diz respeito à capacidade, distância e tipo de transporte utilizado.
 
#### 2.2.4 Fase IV

Aqui, entrará em consideração a existência de vários obstáculos nas vias, identificados em cima, o que levará a uma seleção mais restritiva do percurso e do tipo de estafeta encarregue de determinado pedido. Além disso, o tratamento dos grafos poderá sofrer alterações, sobretudo ao nível do pré-processamento.

## 2.3 Dados de Entrada

Os dados a recolher, antes da execução de qualquer dos algoritmos, para os percursos de cada um dos estafetas, são generalizáveis na seguinte lista:

* Grafo $G (V, E)$, dirigido, representando o mapa de vias (poderemos estar perante múltiplos grafos como opção para vários tipos de veículo), a percorrer pelos estafetas, onde estão localizados, como parte integrante, os pontos de recolha e entrega dos pedidos.
  * Cada vértice $v \in V$ terá os seguintes atributos:
    * Uma lista de arestas $Adj(v) \in E$, que partam desse vértice;
    * Um $id$, identificativo;
    * Um par de coordenadas $coords$, representando a localização real do respetivo ponto.
  * Cada aresta $e(v,u) \in E$, que parta de um dado vértice $v$ será caracterizada por:
    * Um vértice $u \in V$ de destino;
    * Um peso $weight$ associado, relacionado com o seu comprimento real, expresso numa medida de comprimento espacial;
    * Um estado $state$, que representará a transitabilidade da via;
    * Um campo $name$, sem valor expressivo, servindo de identificador.
<!---->
* Conjunto de pontos $R$, representando os restaurantes registados na plataforma:
  * Restaurante $r \in R$ com atributos:
    * O seu $id$, único, identificativo;
    * A referência para o vértice $v$ do grafo, que representa a sua posição.
<!---->
* Conjunto de estafetas $Employees$:
  * Estafeta $employee \in Employees$, com a informação sobre:
    * A sua posição inicial/no momento, $s$, $s \in V$;
    * A sua capacidade máxima de transporte, $maxCargo$;
    * O seu meio de transporte, $type$;
    * A sua disponibilidade, $ready$, para iniciar uma nova tarefa;
    * A sua velocidade média, $avgSpeed$, para permitir a apresentação do tempo estimado de entrega.
<!---->
* Lista ordenada de Pedidos $P$:
  * Pedido $p \in P$ com a informação detalhada sobre:
    * Data e Hora, $time$, em que foi realizado;
    * Lista, $checkPoints$, de pontos/vértices que façam, obrigatoriamente, parte do percurso (referência apenas aos restaurantes e localização dos clientes);
    * Carga total, $cargo$, ocupada pelos itens que o constituem.

Estes dados poderão fazer parte de um pré-processamento existente, consoante o algoritmo escolhido e o problema a resolver. Se esses cálculos iniciais existirem, no caso de um algoritmo que estabeleça as distâncias mínimas entre cada par de vértices, seguir-se-á, então, a inevitável instanciação dos pedidos, com a sua organização em tarefas e a requisição de estafetas para as realizar, terminando no cálculo do caminho final a ser percorrido pelos mesmos. 

## 2.4 Dados de Saída

Tendo sido o grafo analisado, tratado e traduzido numa das várias formas plausíveis de representação, poderá ser retornado, como dado de saída.
O importante, realmente, aqui, é a entrega das tarefas aos estafetas, o que resultará nos seguintes dados:

* Conjunto de tarefas $Tasks$:
  * Tarefa $task \in Tasks$, com informação sobre:
    * A lista completa e ordenada dos vértices consecutivos, $path$, por onde passará o estafeta;
    * O pedido $P$, que faz parte da tarefa;
    * O estafeta $employee$, encarregue da sua realização;
    * A distância total, $totalDistance$, a percorrer pelo estafeta;
    * o tempo estimado $estimatedTime$ para a entrega, com base na velocidade média do $employee$ e na distância a percorrer.

O que se segue, nomeadamente, o ato de percorrer o caminho, com a identificação dos pontos já visitados, da entrega dos pedidos, do cálculo da distância percorrida, é um tanto independente desta análise algorítmica inicial, mas poderá ser, eventualmente, alvo de estudo e reflexão, para interpretação de resultados.

## 2.5 Restrições

A primeira restrição prende-se com o tamanho do grafo. Em termos reais, aplicações deste género, por uma questão de praticabilidade, limitam as zonas de atuação a áreas urbanas, onde exista um número razoável de restaurantes registados e de estafetas em operação. Assim sendo, os grafos aqui analisados também terão a sua área limitada.

As outras restrições são como se seguem:

###### 2.5.1 Dados de Entrada

* $ \forall \ v_1,v_2 \in V, \ v_1 \not = v_2 $, no sentido em que não haverá vértices repetidos;
* $ \forall \ e_1,e_2 \in E, \ e_1 \not = e_2 $, no sentido em que não haverá arestas repetidas;
* $ \forall \ e \in E, \ e.weight \gt 0, \ e.state \in \{ \ 0,\ 1 \}$, já que uma aresta - via/rua - tem um comprimento definido e encontra-se transitável, ou não transitável;
* $ \forall \ r_1,r_2 \in R, \ r_1 \not = r_2 $, no sentido em que não haverá restaurantes repetidos;
* $ \forall \ r \in R, \ r.v \not = null $, sendo que um restaurante tem que ter uma posição estabelecida;
* $ \forall \ employee_1,employee_2 \in Employees, \ employee_1 \not = employee_2 $, no sentido em que não haverá estafetas repetidos;
* $ \forall \ employee \in Employee, \ employee.s \not = null $, sendo que um estafeta tem que ter uma posição estabelecida;
* $ \forall \ employee \in Employee, \ employee.maxCargo \gt 0, \ employee.type \in \{ \ 'car',\ 'bike', \ 'foot' \ \} \ , \ employee.ready \in \{ 0,\ 1 \}$;
* $ \forall \ p_1,p_2 \in P, \ p_1 \not = p_2 $, no sentido em que não haverá pedidos repetidos;
* $ \forall \ p \in P, \ p.time \not = null, \ |p.checkPoints| \gt 1, \ p.cargo \gt 0 $;

###### 2.5.2 Dados de Saída

* $ \forall \ task_1,task_2 \in Tasks, \ task_1 \not = task_2 $ ;
* $ \forall \ task \in Tasks, \ task.path \not = null, task.P \not = null, \ task.employee \not = null \ , |task.path| \gt 1$ ;
* $\forall \ task_1,task_2 \in Tasks, \ task_1.P \not = task_2.P$, no sentido em que nenhum pedido pode pertencer a mais do que uma $Task$;
* $\forall \ task_1,task_2 \in Tasks, \ task_1.employee \not = task_2.employee$, no sentido em que nenhum estafeta pode estar associado a mais do que uma $Task$ a ocorrer em simultâneo;
* $ \forall \ task \in Tasks, \text{em} \ task.path,$ os restaurantes terão de ser visitados antes da localização do cliente, em relação ao pedido associado a ambos;

## 2.6 Função Objetivo

A solução ótima para este problema reside, genericamente, na minimização da distância percorrida, em cada rota, por cada estafeta, numa dada tarefa. Assim, será necessário encontrar o mínimo de:

$$ f(task) = \sum_{e(v_k,v_{k+1})} e.weight \ , \ v_k,v_{k+1} \in task.path \ \land \ e \in E $$

Adicionalmente, para múltiplas tarefas a realizar em simultâneo, num dado intervalo de tempo, poderá surgir a necessidade de minimizar, também, as funções:

$$ g = \sum_{task} f(task) \ , \ task \in Tasks
\\ h = |Tasks| $$

Para a função $g$, representando a distância total percorrida por todos os estafetas, relacionados com um dado conjunto de $Tasks$, o mínimo poderá, eventualmente, ser atingido pela simples minimização de $f$, em todas as instâncias, sendo, por isso, a função $f$ de maior prioridade, entre todas. A função $h$ terá mais interesse quando implementada a funcionalidade extra de um cliente poder englobar no seu pedido vários pratos de vários restaurantes, compactando o que seriam diferentes pedidos num pedido e numa tarefa apenas.
