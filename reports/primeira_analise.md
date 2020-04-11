# EatExpress

>Um relatório fixe: [https://github.com/andrefmrocha/MIEIC_CAL_18_19/blob/master/TripMate_Final_Report.pdf](https://github.com/andrefmrocha/MIEIC_CAL_18_19/blob/master/TripMate_Final_Report.pdf)

## Descrição do tema

Um sistema de entrega de comida ao domicílio pretende implementar uma aplicação que permite ao utilizador escolher o restaurante e o prato que deseja, solicitando a entrega no local onde se encontra.

As entregas são realizadas por estafetas que utilizam o seu próprio meio de transporte, cujas características: capacidade, permissão/proibição para circular em certas vias e velocidade; condicionam a atribuição das encomendas ao conjunto de estafetas.

Como tal, procura-se desenvolver um sistema para gerar os percursos de entrega mais rápidos, entre os restaurantes e os clientes, para os estafetas, tendo em conta as características dos veículos e acessibilidade dos pontos de recolha e entrega .

## Identificação do problema

Para facilitar a análise e desenvolvimento da aplicação, optou-se por subdividir o problema em fases que, gradualmente, procuram abordar mais pormenores e condicionantes até cobrirem por completo o objetivo do trabalho.

### 1ª Fase 
*Um estafeta & vários pedidos*
Só existe um estafeta a trabalhar para a plataforma, e este utiliza um meio de transporte com uma determinada velocidade e condicionantes para entregar vários pedidos num só deslocamento, considerando que podem ser todos transportados em simultâneo.
Ao receber um dado número de pedidos, o estafeta, partindo do centro de apoio ao serviço expresso, deve dirigir-se aos restaurantes indicados e às moradas dos clientes que fizeram os pedidos utilizando o caminho mais curto possível. Assim, o cálculo do caminho mais curto entre os vários pontos do trajeto tem que garantir que uma entrega de um pedido só é feita após esse pedido ter sido recolhido do respetivo restaurante.

É também imprescindível conhecer o tipo de meio de transporte: pé, carro, motociclo, bicicleta; pois o cálculo do caminho mais curto está de pendente da existência de condicionantes de circulação associadas ao meio de transporte utilizado:  no caso de o estafeta se deslocar a pé ou de bicicleta está interdito de circular em autoestradas e vias rápidas sendo necessário usar como grafo de entrada (que representa a rede viária)  o correspondente ao meio de transporte do estafeta.

A existência de obstáculos à circulação, particularmente a ocorrência de obras na via pública, pode inviabilizar o acesso a certas moradas e restaurantes ao tornar zonas inacessíveis. Estas condicionantes têm de ser tidas em conta pois a ausência de um caminho para algumas moradas reflete-se na conectividade do grafo - torna o grafo não conexo; sendo a distância infinita nesses casos. 

### 2ª Fase 
*Vários estafetas & vários pedidos, um por estafeta*
Existem vários estafetas a trabalhar para a plataforma, utilizando cada um meio de transporte com uma determinada velocidade e condicionantes. 
A distribução dos pedidos pelos estafetas deve ser realizada de modo a dar preferência a veículos mais rápidos (sendo relevante a velocidade do veículo) para percursos de longa distância e a veículos maiores para grandes encomendas (sendo a dimensão do pedido um novo fator a considerar): é inviável uma pessoa a pé ou de bicicleta entregar um pedido de grandes dimensões.

### 3ª Fase
 *Vários estafetas & vários pedidos por estafeta*
Existem vários estafetas a trabalhar para a plataforma, utilizando cada um meio de transporte com uma determinada velocidade e condicionantes. 
A distribuição dos pedidos é feita com base na sua dimensão e na distância do seu local de entrega, podendo ao mesmo estafeta ser atribuído um conjunto de pedidos dos quais deve tratar no mesmo delocamento.

COMO RAIO FAZEMOS ISTO, EIS A GRANDE QUESTÃO

## Formalização do problema

### Dados de entrada

 - G<sub>P</sub> = (V<sub>P</sub> E<sub>P</sub>), G<sub>V</sub> = (V<sub>V</sub>, E<sub>V</sub>), G<sub>B</sub> = (V<sub>B</sub>, E<sub>B</sub>) 
</br>*Grafos dirigidos pesados que representam as redes viárias para cada meio de transporte, representando P o deslocamento a pé, B de bicileta e V os outros meios transporte, carro e motoclico.* 
	 -  Vi - conjunto de vértices/nós
	 *Os vértices representam as interseções das ruas* 
		 - coords - par de coordenadas geográficas 
		 - visited
		 - adj ⊆ Ei
		 - path 
	 -  Ei - conjunto de arestas
	  </br>*As arestas representam as vias de sentido único*
		 - dest ∈ Vi
		 - src ∈ Vi
         - weight - representa distância ou tempo? 
 - s ∈ Vi - vértice de origem
</br>*Centro de apoio ao serviço expresso de onde partem os estafetas* 
- P = (R,M)- conjunto de pedidos
</br>*Cada pedido emparelha o restaurante, o local onde deve ser entregue o pedido e a sua dimensão*
	- P<sub>i</sub> =  (R<sub>i</sub>, M<sub>i</sub>)
		- R<sub>i</sub> ⊆ V - restaurante
		- M<sub>i</sub> ⊆ V - morada de entrega
		- dim - dimensão do pedido
- T - meios de transporte disponíveis
	- velocidade
	- capacidade (em nº de pedidos)
- F - conjunto de funcionários, sendo que para cada um são importantes os seguintes dados:
   - pathi - conjunto de vértices que constituem o caminho mais curto para atender a um dado número de pedidos
   - Ri = (Vi,Ei) - conjunto ordenado de vértices e arestas que representam o caminho mais curto para um dado conjunto de pedidos
   - Pi = (R,M) - conjunto de pedidos atendidos por aquele funcionário
   - Ti - meio transporte utilizado pelo estafeta
   - ti - tempo de atendimento dos pedidos

### Dados de saída

- R 

### Restrições

- ...
- ...
- ...

### Funções objetivo

Uma função que será importante na primeira etapa do trabalho, na qual ainda só se considera um estafeta, passa por minimizar o tempo dispendido por esse estafeta a realizar os <img src="https://tex.s2cms.ru/svg/n" alt="n" /> pedidos, ou seja, pela minimização da função:

><img src="https://tex.s2cms.ru/svg/f%24%20%3D%20%24%20%24%5Csum_%7Be%20%5Cin%20R.E%7D%20weight(e)" alt="f$ = $ $\sum_{e \in R.E} weight(e)" />
></br>Lembrando que <img src="https://tex.s2cms.ru/svg/R.E" alt="R.E" /> é o conjunto de arestas que constituem o caminho mais curto para o conjunto de <img src="https://tex.s2cms.ru/svg/n" alt="n" /> pedidos de um dado estafeta.


Na segunda e terceira etapa a função objetivo é semelhante, pois o que difere é o número de pedidos entregue a cada estafeta. 
Assim, a solução ótima do problema para uma plataforma com vários estafetas passa por minimizar o tempo dispendido a realizar <img src="https://tex.s2cms.ru/svg/n" alt="n" /> pedidos, pelo que se prende na minimização do máximo tempo de entre os tempos dos <img src="https://tex.s2cms.ru/svg/k" alt="k" /> estafetas para os respetivos conjuntos de pedidos, ou seja, da minimização da função:

><img src="https://tex.s2cms.ru/svg/g%20%3D%20%5Cmax(R)" alt="g = \max(R)" />
>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp<img src="https://tex.s2cms.ru/svg/R%20%3D%20%5C%7Bf_0%2Cf_1%2C...%2Cf_k%5C%7D%20" alt="R = \{f_0,f_1,...,f_k\} " />
></br>Em que <img src="https://tex.s2cms.ru/svg/R" alt="R" /> conjunto de todos os tempos realizados pelos <img src="https://tex.s2cms.ru/svg/k" alt="k" /> estafetas para entregar o número de pedidos <img src="https://tex.s2cms.ru/svg/n_k%2C%20k%20%5Cin%20%5C%7B0%2C1%2C...%2Ck%5C%7D" alt="n_k, k \in \{0,1,...,k\}" /> que lhes foi atribuído do total de  <img src="https://tex.s2cms.ru/svg/n" alt="n" /> pedidos.


## Perspectiva de solução

### Técnicas de concepção

### Algoritmos

## Casos de utilização suportados
