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

A estratégia a seguir, para a resolução deste problema, sugere a divisão do conceito em fases de análise, de implementação e de deliberação. No entanto, como pré-estabelecido tomamos a ideia de que um estafeta em trabalho, antes de receber a sua rota, pode estar localizado num qualquer ponto do mapa. Esta e a generalização de que existirão sempre, no mínimo, um restaurante e uma morada de um cliente como pontos integrantes da rota, serão o ponto de partida para a análise que se segue.

Convém definir, também, o perfil do estafeta, enquanto entidade que se move pelo percurso estabelecido, com características próprias que serão definidas pelo meio de transporte em que se desloca e pela capacidade máxima que pode transportar. Estas condicionantes influenciarão a escolha da rota e serão tidas em conta, antes de o estafeta iniciar a entrega dos pedidos. 
É imperativo realçar também que, em qualquer percurso, o levantamento dos pedidos nos restaurantes terá de ser efetuado antes da sua entrega aos clientes, por uma questão de fiabilidade e praticabilidade real da situação. Este pormenor irá criar certas restrições, que serão exploradas, ao detalhe, mais adiante. 
Outro aspeto importante é a existência de zonas de desconectividade, nos mapas - a existência de obstáculos à circulação, particularmente, a ocorrência de obras na via pública, que pode inviabilizar o acesso a certas moradas e restaurantes, ao tornar zonas inacessíveis. Também isto será tido em conta, aquando da esquematização dos algoritmos.

Numa última nota, destaca-se a predeterminação de todos os restaurantes e clientes registados na plataforma, elegíveis de submeter um pedido. Este detalhe será substancialmente importante para a adoção de determinados algoritmos, sobretudo se se impuser um pré-processamento dos dados, em particular, a cada novo registo, tanto de um estabelecimento comercial, como de um utilizador, na plataforma.

#### Fase I

Na sua simplicidade, consideramos a existência de apenas um estafeta, que realiza, sequencialmente, os percursos que lhe são impostos. Nesta fase, será também considerado um meio de transporte genérico e não restritivo, e uma capacidade máxima definida previamente. Na sua medida, o funcionário terá uma rota em que concretizará o levantamento de vários (alguns, tendo em conta a capacidade de transporte) pedidos, nos restaurantes, e a sua entrega, na morada dos clientes. Poderá ser considerado, como parte da exemplificação, o caso atómico de um estafeta que entrega, apenas, um pedido, entre um restaurante e a morada de um cliente, ou, mais apropriado ao contexto algorítmico (*single source, multiple destinations*), entre um restaurante e vários clientes.

#### Fase II

Nesta fase, serão considerados vários estafetas, cada um com uma capacidade máxima de carga, o mesmo meio de transporte genérico e para os quais é delineado um percurso. Aqui, estaremos perante a distribuição simultânea de pedidos, com a avaliação de todas as condicionantes relacionadas com o problema, nesta instância. Os pedidos estarão, logicamente, organizados numa escala temporal de prioridade e serão entreges aos estafetas, respeitando a sua capacidade de transporte.

#### Fase III

A última fase coincidirá com a implementação de variados meios de transporte, o que corresponderá à utilização de diferentes mapas, para atender às características das múltiplas entidades que entregarão os pedidos e, em simultâneo, às características das diversas vias. Aqui, entrará também em consideração a existência dos obstáculos definidos em cima, o que levará a uma seleção mais restritiva do tipo de estafeta encarregue de determinado pedido.

>---------------------------------

Dados de Entrada
----------------

Os dados a recolher, antes da execução de qualquer dos algoritmos, para os percursos de cada um dos estafetas, são generalizáveis na seguinte lista:

* Grafo $G (V, E)$, dirigido, representando o mapa de vias (múltiplos grafos como opção para vários tipos de veículo - ver atributos das arestas), a percorrer pelos estafetas, onde estão, como parte integrante, destacados e definidos os locais de recolha e entrega dos pedidos.
  * Cada vértice $v \in V$ terá os seguintes atributos:
    * Uma lista de arestas $Adj(v) \in E$, que partam desse vértice;
    * Um $id$, identificativo;
    * Um par de coordenadas $coords$, representando a localização real do respetivo ponto;
    * Uma anotação $type$ que o distinga de restaurante, morada de cliente, ou simples vértice de ligação;
  * Cada aresta $e(v,u) \in E$, que parta de um dado vértice $v$ será caracterizada por:
    * Um vértice $u \in V$ de destino;
    * Um peso $weigth$ associado, relacionado com o seu comprimento real, expresso numa medida de comprimento espacial;
    * Um estado $state$, que representará a transitabilidade da via;
    * Um campo $name$, sem valor expressivo, servindo de identificador;
    * Eventualmente, e como possível alternativa à utilização de diversos grafos para cada tipo de transporte, em certas situações e algoritmos a escolher, um estatuto identificador do tipo de via que permita, ou impeça, a passagem dos respetivos meios de deslocação. Este campo é apenas uma previsão, ou sugestão de implementação, ainda não definitiva.

Estes dados poderão fazer parte de um pré-processamento existente, consoante o algoritmo escolhido e o problema a resolver. 
Se esses cálculos iniciais existirem, no caso de um algoritmo que estabeleça as distâncias mínimas entre cada par de vértices, seguir-se-á a instanciação dos pedidos, entregues aos estafetas, com o estabelecimento, também neste instante, do caminho a ser percorrido. Aqui, ter-se-á em conta as várias restrições, numa problematização um pouco à parte do cálculo das distâncias mínimas.
Ainda assim, os dados relativos a cada situação específica, relacionada com as tarefas entregues aos estafetas, enumeram-se seguidamente:

* Conjunto de estafetas $Employees$:
  * Estafeta $employee \in Employees$, com a informação sobre:
    * A sua posição inicial/no momento, $s$, um vértice/ponto no mapa;
    * A sua capacidade máxima, $maxCargo$;
    * O seu meio de transporte, $type$;
* Lista ordenada de Pedidos $P$:
  * Pedido $p \in P$ com a informação detalhada sobre:
    * Lista ordenada $checkPoints$ de pontos/vértices que façam parte do percurso;
    * Lista de $itens$, cada um com a simples descrição da carga ocupada;
    * Estafeta $emp$, que realizará o pedido;
