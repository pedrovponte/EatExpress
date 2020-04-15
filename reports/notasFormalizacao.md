## Notas 1: Fases 
(no geral não pensei nas fases da mesma forma)
- acho que os varios grafos não são um fator que devemos considerar só na ultima etapa mas sim em todas
> #### Eduardo 
>Não necessariamente, porque a primeira fase de abordagem pode e deve ser o mais genérica possível, para podermos mostrar os algoritmos em ação para o caso menos restritivo possível, com menos pormenores. Isso pode significar começar apenas com um grafo, pela pura existência de apenas um tipo de veículo, tal como sugere o enunciado.
> *"Nesta fase posterior, considere usar estafetas com veículos mais rápidos para percursos de longa distância, e maiores para grandes encomendas"*
> Porque o número de grafos seria implicado pelos vários tipos de veículos, com cada grafo constituido por diferentes arestas/vias, consoante as ruas acessíveis a esse determinado veículo. Isso seria para fases posteriores, portanto.

> #### Diana
> Nota no próximo ponto relativamente aos dois

***
- numa primeira fase ignorava a capacidade
> #### Eduardo 
>Eu não ignorava, porque isso faz parte do estafeta como elemento subatómico do problema, já que é ele quem vai interligar os diferentes componentes, servindo a capacidade para limitar também o número de vértices a visitar, porque, caso fosse, por exemplo, infinita, poderia não haver instante de paragem, com o/um estafeta a poder realizar todos os pedidos que entrassem a todo o momento na queue de pedidos? Uma coisa assim... Mas, na primeira fase, podemos sim considerar uma capacidade não restritiva, maior, para criarmos exemplos de aplicação com vários restaurantes, pedidos e clientes num só percurso. 
> Apesar disto, a capacidade estará lá como atributo dos dados de entrada, já que vai ser usada e vai. O seu valor é que pode ser um tal de maneira a ser "discriminada", de certa forma.

> #### Diana
> Numa primeira fase o meio de transporte não traria complexidade acrescida em termos de algoritmo porque o que seria alterado era o dado de entrada - o Grafo; correspondente ao meio de transporte. Ou seja não seria isso que afetaria a generalidade em termos práticos apesar de em teoria poder parecer. Quando consideras um só estafeta este está associdado a um só meio de trasporte e esse meio de trasnporte é que deve estar associdado a uma capacidade. Portanto a capacidade não "faz parte do estafeta como elemento subatómico do problema". O meio de transporte no entando faz e daí considerear a capacidade seja na minha opinião algo que vem depois numa segunda fase. Aliás, podemos ter uma segunda fase, ainda para um estafeta, em que se considera a capacidade. No entanto, este atributo já vai condicionar o teu algoritmo e trazer complexidade acrescida pois de um conjunto de pedidos vais ter que selecionar apenas o número de pedidos que podes realmente transportar. A minha ideia seria claro, trabalhar inicialmente com um nº pequeno de pedidos mas não trabalhar logo como é feita a seleção dos pedidos para entrega se existirem mais do que a capacidade do meio de transporte permite (a tal "capacidade não restritiva" mas isso é logico que não ia considerar mil pedidos, simplesmente esse dado não seria limitativo). Tinhamos um conjunto de pedidos e tinhamos de calcular o caminho mais curtos para o estafeta realizar todos os pedidos usando como input o grafo associdado ao seu meio de transporte.

***
- concordo com a escala temporal que não coloquei na análise que fiz
> A escala temporal serviria apenas para organizar os pedidos. No entanto, isto não deveria ser um grande foco no nosso trabalho, porque o que queremos mesmo é minimizar as distâncias, não organizar os pedidos da melhor forma possível. Além disso, eu penso que nós não devemos considerar nada que tenha que ver com *"tempo"* já que é a única coisa que, em sistemas reais, também, é imprevisível e impossível de calcular de verdade. Temos de nos limitar ao fixo e ao imutável que são as distâncias. Minimizar o tempo não é algo legítimo, para este tipo de problemas. Quanto muito, podemos sempre, depois de calculada a distância mínima, estimar o tempo, com base numa velocidade média para cada veículo, mas isso só serviria como anotação para o cliente, por exemplo, que é o que acontece na realidade, nessas apps.

> #### Diana
> Exato, é isso. Concordo.
***

- existência dos obstáculos para cada meio de transporte: colocaste um estado nas arestas que representa se a via estára impedida ou não mas não sei até que ponto conseguimos implementar isso dessa forma. Como irias ao processar o grafo fazer esse tipo de identificação? Ou como gerias o facto de as vias mudarem a sua "transitabilidade" com o tempo?
> Basicamente, isso acontecer, ou não, é aquela famosa questão do Google Maps quando funciona offline. 
> Offline não identifica acidentes, não mostra trânsito, etc. Limita-se a mostrar a distância mínima entre dois pontos e o percurso entre eles. Isso seria para o estado inicial - processamento inicial, onde nenhuma estivesse impedida. Quando detetada uma aresta impedida, teria que se proceder, de novo, ao processamento do grafo. Em mapas pequenos - there's no real problem. Em mapas grandes, imagino que eles tenham algoritmos melhores, que só processem por exemplo partes fortemente conexas ou coisas do género, comuns aos dois vértices. Teriamos que pensar na melhor maneira. Mas penso ser uma boa approach, porque mantendo esse atributo, num qualquer algoritmo que gera o caminho mais curto, verificando esse atributo, pode ser usado para definir outro caminho ou não - a aresta não deixa de existir só porque fica intransitável, podendo voltar ao normal passado uns tempos. Entre tirar a aresta, ou mudar-lhe o valor de um atributo, prefiro a segunda, porque o grafo vai ter que ser tratado de qualquer maneira, quando passa a haver um obstáculo na via.

> #### Diana
> Pois, acho que deviamos perguntar aos professores porque realmente não se sabe bem como devemos trabalhar esta questão das condicionantes devido a obras na via pública etc.
***

## Dados de Entrada:
- o estafeta parte do centro de apoio ao serviço expresso para um dado conjunto de pedidos ou seja a posição inicial não faz mt sentido na minha opinião (não entendi bem a posição por essa razão)
> Isso não está escrito no enunciado. Eu penso que eles queiram fazer algo como Uber Eats, ou no mesmo mecanismo que as plataformas tipo Uber e afins, onde não existe um "centro de apoio". Quando um estafeta/motorista recebe uma proposta de tarefa, pode estar em qualquer sítio do mapa. Essa é a posição dele. Senão, limitarias o problema ao caso do estafeta sair sempre do centro de apoio quando tivesse que fazer um pedido. Nisto, quando o estafeta terminasse determinada tarefa, ias obriga-lo a voltar para o centro ?... quando poderia muito bem começar uma nova tarefa, a partir desse ponto onde terminou (nova posição inicial do estafeta).
- associava os meios de transporte a uma dimensão e/ou velocidade
> Isso seriam exatamente as propriedades do estafeta. Um meio de transporte não existe sem um estafeta, nem a capacidade, que pode estar associada ao transporte, mas que tem de ser uma característica do estafeta, por transitividade dos atributos. Logo, fica tudo no estafeta. A velocidade já expliquei em cima a minha visão, em relação ao *"tempo"*

> #### Diana
> No enuncidado falam de um centro de apoio como dado de entrada daí a minha questão: *"Considere a possibilidade de utilizar mapas reais, extraídos do OpenStreetMaps (www.openstreetmap.org) e coordenadas geográficas das moradas e do centro de apoio do serviço expresso, na implementação desta aplicação."*.
Também acho mais interessante assim como disseste mas se eles pretendem um centro de apoio temos que ter não é? Mais vale perguntar também para confirmar.

> Quanto à velocidade também falam em termos de característica do meio de transporte que deve ser considerada na segunda fase: *" Nesta fase posterior, considere usar estafetas com veículos mais rápidos para percursos de longa distância, e maiores para grandes encomendas."*. Penso que a abordagem da velocidade é enquanto fator de seleção. Por exemplo, se tiveres dois estafetas um com um motociclo e um com uma bicicleta e se o pedido for feito num local distante o caminho mais curto vai ser o do motociclo (calculando os caminhos + curtos para ambos os meios de transporte vais obter um melhor resultado para o motociclo). Acho que é isto que eles querem dizer com "+ rápidos". Alterei isto na minha análise para tornar mais clara a abordagem da velocidade. Quanto à dimensão acho que é a tal "capacidade" mas está associdado ao veículo (tipo uma bicicleta/a pé vs carro/motociclo, podendo claro haver uma dimensão que varie para carros maiores e mais pequenos etc).
***

> #### Diana
Nota final relativamente à minha opinião em relação à consideração dos meios de transporte e às diferentes fases:

1. Numa primeira fase o meio de tranporte associdado ao estafeta vai decidir apenas o grafo de entrada, pois é essencial saberes o meio de transporte utilizado para calculares o caminho mais curto para um dado conjunto de pedidos.

2. *(Possível fase nova)* A dimensão estaria associda ao meio de transporte e podia ser considerada numa segunda fase, ainda para um só estafeta. Nesta fase esta afetaria o número de pedidos a realizar (pois teria de ser feita uma escolha de modo a não ultrapassar a capacidade em termos de número de pedidos).

3. Numa terceira fase, sendo considerados vários estafetas penso que podemos continuar a considerar a capacidade pois será importante na distribuição dos pedidos.
No entanto, o meio de de transporte genérico não será benéfico pois o meio de tranporte vai apenas interferir no cálculo do caminho + curto para cada estafeta(conceito de velocidade) não sendo um problema na distribuição geral dos pedidos. 

4. Talvez considerar as condicionantes (obras na via pública e assim). Teriamos que perguntar.


## Notas 2: Função Objetivo

Concordo. Mudei na minha análise porque estava a considerar aspetos relacionados com o tempo e que não eram bem pensados.
