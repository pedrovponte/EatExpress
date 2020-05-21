A primeira e segunda fase planeadas na primeira parte do trabalho serviram de base para desenvolver a fase que realmente consideramos crucial, a fase III, na qual já se tem em conta as várias condicionantes do problema, entre as quais as distâncias dos estafetas aos restaurantes dos pedidos, as capacidades máximas de transporte, os meios de transporte utilizados e a disponibilidade do estafetas.
Como tal, todos estes fatores que foram ignorados numa fase inicial do desenvolvimento do trabalho, na qual só se pretendia abordar o problema na sua essência, são, na aplicação final, trabalhados tanto para o caso de um estafeta como para o caso em que existem vários.

Para melhor analisar a implementação, optamos, então, por descrever sucintamente as estratégias adotadas para cada caso de utilização, acompanhadas de pseudo-código.

## Um ou vários pedidos por ordem temporal

Para o caso em que é feito um pedido ou vários de um único restaurante e existem múltiplos estafetas para o realizar, seguimos a estratégia descrita na fase III para a escolha do estafeta.

A implementação deste caso tem como base a função: 
`vector<SingleTask*> distributeRequests(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, min_priority_queue & requests, vector<Employee*> & employees)`, que devolve um conjunto de tarefas, consistindo uma tarefa na atribuição de um pedido a um estafeta.

Começa-se por verificar que tipos de meio de transporte podem ser utilizados para completar cada pedido, tendo em conta que são utilizados grafos diferentes para representar os caminhos transitáveis a pé/bicicleta e aqueles que podem ser percorridos de carro/motociclo. Para isso, são atualizadas as variáveis `deliverableByCar` e `deliverableByFoot` do pedido consoante exista ou não um caminho entre o vértice do restaurante e a morada de entrega no grafo correpondente a cada meio de transporte. Utiliza-se a função `setRequestsDeliverability(const Graph<Coordinates> & graph, const Graph<Coordinates> & reducedGraph, min_priority_queue & requests)` para realizar esta verificação.

Seguidamente, realizando os pedidos por ordem temporal, para escolha de um estafeta para cada pedido, começa-se por definir as distâncias dos estafetas ao restaurante, armazenadas na matriz de distâncias calculada previamente com o algoritmo de Floyd Warshall - ´setDistancesToCheckpoint(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, vector<Employee*> & employees, Request & request)´. Aí, verifica-se também se existe um caminho entre estes dois pontos no grafo de cada meio de transporte e impõe-se uma distância limite para a realização de pedidos de bicicleta ou a pé, evitando trajetos excessivamente longos para estafetas que utilizem este meio de transporte. 

O passo seguinte é excluir todos os estafetas que não têm possibilidade de entregar o pedido, não só devido aos fatores anteriores mas também por não terem capacidade para o transportar ou por não estarem disponíveis - `getEligibleEmployees(vector<Employee*> & employees, const Request & request)`.

Finalmente, de todos os estafetas disponíveis, a escolha passa pela conjugação de três fatores: distância mais curta do restaurante, carga e velocidade média do meio de transporte, dando prioridade à distância, com um peso de 50% na decisão. Para isso utiliza-se o operador menor da classe `Employee` para escolher o estafeta a realizar o pedido.

```cpp
bool Employee::operator<(const Employee &rhs) const {
    return dist*0.5 + maxCargo*0.3 + avgVelocity * 0.2 < rhs.getDist()*0.5 + rhs.getMaxCargo()* 0.3 + rhs.getAvgVelocity() * 0.2 ;
}
```

Definido um estafeta para um dado pedido, o estafeta é marcado como indisponível, sendo necessários distribuir os restantes pedidos pelos restantes estafetas. 
Como existem pedidos que só podem ser realizados por alguns estafetas específicos devido à sua carga ou fraca acessibilidade, alguns pedidos não serão atribuídos à primeira tentativa, utilizando-se uma fila de prioridade auxiliar `pendingRequests` para os guardar.

Assim que uma ronda de distribuição de pedidos termina, isto é, assim que todos os estafetas tenham um pedido atribuído, volta-se a disponibilizar todos os estafetas para a distribuição dos restantes pedidos e constrói-se o caminho mais curto para cada estafeta realizar o pedido que lhe foi atribuído - 'setFloydWarshallPath(Graph<Coordinates> & graph)';

Assim que não existirem mais pedidos para distribuir, havendo a possibilidade de um pedido não poder ser entregue por nenhum estafeta ter condições para o atingir ou carga para o transportar, são devolvidas todas as tarefas que fazem corresponder cada pedido com o estafeta que ficou responsável por ele.

*Pseudo-código*

```
distributeRequests(G1, G2, PriorityQueue<Request> Q, vector<Employee> E){
    vector<SingleTask> task; // Para devolver a distribuição dos pedidos pelos estafetas
    vector<SingleTask> roundTasks; // A cada ronda de distribuição guarda as tarefas

    PriorityQueue<Request> pendingRequests 🠄 ∅ // Para guardar pedidos pendentes
    Q = setRequestsDeliverability(G1,G2,Q) // Para definir se um pedido pode ou não ser entregue por cada meio de transporte

    while Q != ∅ {
        Request r 🠄 Q.top() // Entregar um pedido de cada vez
        Q.pop();

        setDistancesToCheckpoint(G1, G2, E,r);

        eligibleEmployees = getEligibleEmployees(E, r);

        if E == ∅ then
            pendingRequests.push(r); // Nenhum estafeta eligível no momento
        
        else
            sort(E); // de acordo com o operador <
            ready(E[0]) 🠄 false; // Ocupar o estafeta com o pedido
            SingleTask task(E[0], r);

        if Q == ∅ then
            ...
            /* Verificar se um pedido não pode ser entregue a nenhum estafeta - apesar de todos os estafetas estarem disponíveis, não há nenhum eligível para o pedido. Detalhes da implementação podem ser consultados no código fonte */
            ...

            for each task ∈ roundTasks
                if VehicleType(task) == BIKE || VehicleType(task) == FOOT then
                    task.setFloydWarshallPath(G2);
                else if VehicleType(task) == CAR || VehicleType(task) == MOTORCYCLE
                    task.setFloydWarshallPath(G1);

            tasks.insert(roundTasks);
            roundTasks.clear(); 
    }
    return tasks;
}
```


## Pedido de múltiplos restaurantes

Um outro caso de utilização consiste na atribuição de um pedido que inclui refeições de mais do que um restaurante, cuja implementação se basei essencialmente na função `SingleTask * multipleRestaurantsRequest(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, vector<Employee*> & employees, Request & request)`.
Para isso, determinam-se mais uma vez quais os estafeta eligíveis para realizar o pedido. Neste caso, no entanto, só podemos descartar, numa fase inicial, aqueles estafetas que não possuam capacidade para transportar a carga do pedido. 
Seguidamente, determina-se para cada estafeta o caminho a seguir para recolher o pedido dos restaurantes, escolhendo sempre o restaurante mais perto  - `int getNearestRestaurant(Graph<Coordinates> & graph, const Coordinates & origin, vector<Coordinates> & restaurants)`; (consultando a matriz de distâncias pré calculada com o algoritmo de Floyd Warshall). Mantém-se sempre guardada a melhor distância e o estafeta ao qual essa distância corresponde, tendo sempre em atenção que pode não existir caminho possível no caso de alguns meios de transporte (dependendo do grafo de entrada). No fim, é escolhido o estafeta ao qual corresponde a melhor distância.


## Um estafeta - entrega de vários pedidos no mesmo deslocamento (variante do TSP)

