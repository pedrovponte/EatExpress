# Formalization

Problematização
---------------

Em primeiro lugar, convém dividir todas as questões relativas aos vários componentes da aplicação. 

O que se pretende com esta análise é garantir a máxima eficiência na implementação de um algoritmo que permita criar e gerir, de forma rápida e precisa, as rotas dos estafetas de entrega de comida, entre as localizações dos restaurantes e as localizações dos clientes que efetuaram os pedidos. 

Não serão equacionadas as implementações da interface da aplicação, ao nível do utilizador, nem serão alvo de análise todos os aspetos não relacionados com grafos, ou algoritmos não abordados.

Assim sendo, o problema reduzir-se-á a encontrar os caminhos mais curtos entre pontos/vértices, num mapa de atuação pré-escolhido, e, por fim, tendo em conta as diversas variantes do problema, definir rotas que permitam navegar pelos percursos, percorrendo a menor distância possível.

>----------------------------------

Estratificação
--------------

A estratégia a seguir, para a resolução deste problema, sugere a divisão do conceito em fases de análise, de implementação e de deliberação. No entanto, como pré-estabelecida tomamos a ideia de que um estafeta em trabalho, antes de receber a sua rota, pode estar localizado num qualquer ponto do mapa. Esta e a generalização de que existirão sempre, no mínimo, um restaurante e uma localização de um cliente como pontos integrantes da rota, serão o ponto de partida para a análise que se segue.

Convém definir, também, o perfil do estafeta, enquanto entidade que se move pelo percurso estabelecido, com características próprias que serão definidas pelo meio de transporte em que se desloca e pela capacidade máxima que pode transportar. Estas condicionantes influenciarão a escolha da rota e serão tidas em conta, antes de o estafeta iniciar a entrega dos pedidos. 
É imperativo realçar também que, em qualquer percurso, o levantamento dos pedidos nos restaurantes terá de ser efetuado antes da sua entrega aos clientes, por uma questão de fiabilidade e praticabilidade real da situação. Este pormenor irá criar certas restrições, que serão exploradas, ao detalhe, mais adiante. 
Outro aspeto importante é a existência de zonas de desconectividade, nos mapas - a existência de obstáculos à circulação, particularmente, a ocorrência de obras na via pública, que pode inviabilizar o acesso a certas moradas e restaurantes, ao tornar zonas inacessíveis. Também isto será tido em conta, aquando da esquematização dos algoritmos.

Numa última nota, destaca-se a predeterminação de todos os restaurantes registados na plataforma, elegíveis de receber um pedido. Este detalhe será substancialmente importante para a adoção de determinados algoritmos, sobretudo se se impuser um pré-processamento dos dados, em particular, a cada novo registo, de um estabelecimento comercial, na plataforma.

#### Fase I

Na sua simplicidade, consideramos a existência de apenas um estafeta, que realiza, sequencialmente, os percursos que lhe são impostos. Nesta fase, de modo a focar a análise na essência da problemática, será considerado um meio de transporte qualquer e desvalorizada a capacidade de transporte. Na sua medida, o funcionário terá uma rota na qual concretizará o levantamento dos pedidos, nos restaurantes, e a sua entrega, na morada dos clientes. Poderá ser considerado, como parte da exemplificação, o caso atómico de um estafeta que entrega apenas um pedido, entre um restaurante e a morada de um cliente, ou, mais apropriado ao estudo dos vários contextos algorítmicos (*single source, multiple destinations*), entre um restaurante e vários clientes.

#### Fase II

Nesta fase, serão considerados vários estafetas que utilizam o mesmo meio de transporte e para os quais é delineado um percurso. Aqui, estaremos perante a distribuição simultânea de pedidos, com a avaliação de todas as condicionantes relacionadas com o problema, nesta fase. 
Os pedidos estarão, logicamente, organizados numa escala temporal, ficando encarregue por um dado pedido o estafeta que se encotre mais perto do restaurante a ele associado.

#### Fase III

Esta fase coincidirá com a implementação de variados meios de transporte, o que poderá corresponder à utilização de diferentes mapas, para atender às características das múltiplas entidades que entregarão os pedidos e, em simultâneo, às características das diversas vias. 
Para além disso será imprescindível ter em conta a capacidade máxima que cada estafeta pode transportar, pois a dimensão da encomenda passa a ser determinante na atribuição dos pedidos. 
Assim, nesta fase, a atribuição de um pedido a um estafeta passa a depender não só da sua proximidade do restaurante, mas também das características próprias do meio de transporte por ele utilizado, preferindo os meios de transporte mais rápidos para encomendas que impliquem deslocações maiores e optando por atribuir as encomendas de maior dimensão aos estafetas que tenham mais facilidade em transportá-las.
 
#### Fase IV

Aqui, entrará em consideração a existência de vários obstáculos nas vias, identificados em cima, o que levará a uma seleção mais restritiva do percurso e do tipo de estafeta encarregue de determinado pedido.

>---------------------------------

Dados de Entrada
----------------

Os dados a recolher, antes da execução de qualquer dos algoritmos, para os percursos de cada um dos estafetas, são generalizáveis na seguinte lista:

* Grafo $G (V, E)$, dirigido, representando o mapa de vias (poderemos estar perante múltiplos grafos como opção para vários tipos de veículo), a percorrer pelos estafetas, onde estão localizados, como parte integrante, os pontos de recolha e entrega dos pedidos.
  * Cada vértice $v \in V$ terá os seguintes atributos:
    * Uma lista de arestas $Adj(v) \in E$, que partam desse vértice;
    * Um $id$, identificativo;
    * Um par de coordenadas $coords$, representando a localização real do respetivo ponto;
  * Cada aresta $e(v,u) \in E$, que parta de um dado vértice $v$ será caracterizada por:
    * Um vértice $u \in V$ de destino;
    * Um peso $weight$ associado, relacionado com o seu comprimento real, expresso numa medida de comprimento espacial;
    * Um estado $state$, que representará a transitabilidade da via;
    * Um campo $name$, sem valor expressivo, servindo de identificador;
<!---->
* Conjunto de pontos $R$, representando os restaurantes registados na plataforma:
  * Restaurante $r \in R$ com atributos:
    * O seu $id$, único, identificativo;
    * A referência para o vértice $v$ do grafo, que representa a sua posição;
<!---->
* Conjunto de estafetas $Employees$:
  * Estafeta $employee \in Employees$, com a informação sobre:
    * A sua posição inicial/no momento, $s$, um vértice/ponto no mapa;
    * A sua capacidade máxima de transporte, $maxCargo$;
    * O seu meio de transporte, $type$;
    * A sua disponibilidade, $ready$, para iniciar uma nova tarefa;
<!---->
* Lista ordenada de Pedidos $P$:
  * Pedido $p \in P$ com a informação detalhada sobre:
    * Data e Hora, $time$, em que foi realizado;
    * Lista, $checkPoints$, de pontos/vértices que façam, obrigatoriamente, parte do percurso (referência apenas aos restaurantes e localização dos clientes);
    * Carga total, $cargo$, ocupada pelos itens que o constituem;

Estes dados poderão fazer parte de um pré-processamento existente, consoante o algoritmo escolhido e o problema a resolver. Se esses cálculos iniciais existirem, no caso de um algoritmo que estabeleça as distâncias mínimas entre cada par de vértices, seguir-se-á, então, a inevitável instanciação dos pedidos, com a sua organização em tarefas e a requisição de estafetas para as realizar, terminando no cálculo do caminho final a ser percorrido pelos mesmos. 

Dados de Saída
--------------

Tendo sido o grafo analisado, tratado e traduzido numa das várias formas plausíveis de representação, poderá ser retornado, como dado de saída.
O importante, realmente, aqui, é a entrega das tarefas aos estafetas, o que resultará nos seguintes dados:

* Conjunto de tarefas $Tasks$:
  * Tarefa $task \in Tasks$, com informação sobre:
    * A lista completa e ordenada dos vértices consecutivos, $path$, por onde passará o estafeta;
    * O pedido $P$, que faz parte da tarefa;
    * O estafeta $employee$, encarregue da sua realização;

O que se segue, nomeadamente, o ato de percorrer o caminho, com a identificação dos pontos já visitados, da entrega dos pedidos, do cálculo da distância percorrida, é um tanto independente desta análise algorítmica inicial, mas poderá ser, eventualmente, alvo de estudo e reflexão, para interpretação de resultados.

Restrições
---------

A primeira restrição prende-se com o tamanho do grafo. Em termos reais, aplicações deste género, por uma questão de praticabilidade, limitam as zonas de atuação a áreas urbanas, onde exista um número razoável de restaurantes registados e de estafetas em operação. Assim sendo, os grafos aqui analisados também terão a sua área limitada.

As outras restrições são como se seguem:

###### Dados de Entrada

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

###### Dados de Saída

* $ \forall \ task_1,task_2 \in Tasks, \ task_1 \not = task_2 $ ;
* $ \forall \ task \in Tasks, \ task.path \not = null, task.P \not = null, \ task.employee \not = null \ , |task.path| \gt 1$ ;
* $ \forall \ task \in Tasks, \text{em} \ task.path,$ os restaurantes terão de ser visitados antes da localização do cliente, em relação ao pedido associado a ambos;

Função Objetivo
---------------
A solução ótima para este problema reside, genericamente, na minimização da distância percorrida, em cada rota, por cada estafeta, numa dada tarefa. Assim, será necessário encontrar o mínimo de:

$$ f(task) = \sum_{e(v_k,v_{k+1})} e.weight \ , \ v_k,v_{k+1} \in task.path \ \land \ e \in E $$

Adicionalmente, para múltiplas tarefas a realizar em simultâneo, num dado intervalo de tempo, poderá surgir a necessidade de minimizar, também, as funções:

$$ g = \sum_{task} f(task) \ , \ task \in Tasks
\\ h = |Tasks| $$

Para a função $g$, o mínimo poderá, eventualmente, ser atingido pela simples minimização de $f$, em todas as instâncias, sendo, por isso, a função $f$ de maior prioridade, entre todas.