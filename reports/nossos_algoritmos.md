# 6. Algoritmos e Estratégias implementadas

A primeira e segunda fase planeadas na primeira parte do trabalho serviram de base para desenvolver a fase que realmente consideramos crucial, a fase III, na qual já se tem em conta as várias condicionantes do problema, entre as quais as distâncias dos estafetas aos restaurantes dos pedidos, as capacidades máximas de transporte, os meios de transporte utilizados e a disponibilidade dos estafetas.
Como tal, todos estes fatores que foram ignorados numa fase inicial do desenvolvimento do trabalho, na qual só se pretendia abordar o problema na sua essência, são, na aplicação final, trabalhados tanto para o caso de um estafeta como para o caso em que existem vários.

Para melhor analisar a implementação, optamos, então, por descrever sucintamente as estratégias adotadas para cada caso de utilização, acompanhadas de pseudo-código.

## 6.1 Um ou vários pedidos por ordem temporal

Para o caso em que é feito um pedido ou vários, cada um de um único restaurante, e existem múltiplos estafetas para o realizar, seguimos a estratégia descrita na fase III para a escolha do estafeta.

A implementação deste caso tem como base a função: 
`vector<SingleTask*> distributeRequests(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, min_priority_queue & requests, vector<Employee*> & employees)` - definida em `SingleTask.cpp`; que devolve um conjunto de tarefas, consistindo uma tarefa na atribuição de um pedido a um estafeta.

Começa-se por verificar que tipos de meio de transporte podem ser utilizados para completar cada pedido, tendo em conta que são utilizados grafos diferentes para representar os caminhos transitáveis a pé/bicicleta e aqueles que podem ser percorridos de carro/motociclo. Para isso, são atualizadas as variáveis `deliverableByCar` e `deliverableByFoot` do pedido, consoante exista ou não um caminho entre o vértice do restaurante e a morada de entrega no grafo correpondente a cada meio de transporte. Utiliza-se a função 
`setRequestsDeliverability(const Graph<Coordinates> & graph, const Graph<Coordinates> & reducedGraph, min_priority_queue & requests)` 
para realizar esta verificação.

Seguidamente, realizando os pedidos por ordem temporal, para a escolha de um estafeta para cada pedido, começa-se por definir as distâncias dos estafetas ao restaurante, armazenadas na matriz de distâncias calculada previamente com o algoritmo de Floyd Warshall - 
`setDistancesToCheckpoint(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, vector<Employee*> & employees, Request & request)`. Aí, verifica-se também se existe um caminho entre estes dois pontos no grafo de cada meio de transporte e impõe-se uma distância limite para a realização de pedidos de bicicleta ou a pé, evitando trajetos excessivamente longos para estafetas que utilizem este meio de transporte. 

O passo seguinte, é excluir todos os estafetas que não têm possibilidade de entregar o pedido, não só devido aos fatores anteriores mas também por não terem capacidade para o transportar ou por não estarem disponíveis - 
`getEligibleEmployees(vector<Employee*> & employees, const Request & request)`.

Finalmente, de todos os estafetas disponíveis, a escolha passa pela conjugação de três fatores: distância mais curta até ao restaurante, carga e velocidade média do meio de transporte, dando prioridade à distância, com um peso de 50% na decisão. Para isso utiliza-se o operador menor da classe `Employee` para escolher o estafeta a realizar o pedido.

```cpp
bool Employee::operator<(const Employee &rhs) const {
    return dist * 0.5 + maxCargo * 0.3 + avgVelocity * 0.2 < 
        rhs.getDist() * 0.5 + rhs.getMaxCargo() * 0.3 + rhs.getAvgVelocity() * 0.2;
}
```

Definido um estafeta para um dado pedido, este é marcado como indisponível, sendo necessário distribuir os restantes pedidos pelos estafetas disponíveis. 
Como existem pedidos que só podem ser realizados por alguns estafetas específicos, devido à sua carga ou fraca acessibilidade dos seus vértices, alguns pedidos não serão atribuídos à primeira tentativa, utilizando-se uma fila de prioridade auxiliar `pendingRequests` para os guardar.

Assim que uma ronda de distribuição de pedidos termina, isto é, assim que todos os estafetas tenham um pedido atribuído, volta-se a disponibilizar todos os estafetas para a distribuição dos restantes pedidos e constrói-se o caminho mais curto para cada estafeta realizar o pedido que lhe foi atribuído - `setFloydWarshallPath(Graph<Coordinates> & graph)` - em `SingleTask.cpp`; obtendo o caminho mais curto entre a posição do estafeta e o restaurante e entre o restaurante e a morada de entrega.

Assim que não existirem mais pedidos para distribuir, havendo a possibilidade de existirem pedidos que nenhum estafeta tenha condições para realizar - por os seus vértices serem inacessíveis ou por nenhum estafeta ter capacidade para o transportar; são devolvidas todas as tarefas que fazem corresponder cada pedido com o estafeta que ficou responsável por ele.

```cpp
distributeRequests(Graph G1, Graph G2, PriorityQueue<Request> R, vector<Employee> E){
    vector<SingleTask> task // Para devolver a distribuição dos pedidos pelos estafetas
    vector<SingleTask> roundTasks // A cada ronda de distribuição guarda as tarefas

    PriorityQueue<Request> pendingRequests 🠄 ∅ // Guardar pedidos pendentes
    R ← setRequestsDeliverability(G1,G2,R)

    while R != ∅ :
        Request request ← R.top() // Tentar atribuir o 1º pedido da fila
        R.pop()

        setDistancesToCheckpoint(G1, G2, E, request)
        eligibleEmployees ← getEligibleEmployees(E, request)

        if E == ∅ :
            pendingRequests.push(request) // Nenhum estafeta eligível
        else :
            sort(E) // de acordo com o operador <
            ready(E[0]) ← false // Ocupar o estafeta com o pedido
            SingleTask task(E[0], request) // Associar o estafeta ao pedido

        if Q == ∅ :
            //Verificar caso em que o pedido não pode ser entregue por nenhum estafeta
            // ...
            // Construção do caminho dos estafetas
            for each task ∈ roundTasks :
                if VehicleType(task) == CAR || VehicleType(task) == MOTORCYCLE :
                    task.setFloydWarshallPath(G1)
                if VehicleType(task) == BIKE || VehicleType(task) == FOOT :
                    task.setFloydWarshallPath(G2) 

            tasks.insert(roundTasks)
            roundTasks.clear()
    return tasks
}
```


## 6.2 Pedido de múltiplos restaurantes

Um outro caso de utilização consiste na atribuição de um pedido que inclui refeições de mais do que um restaurante, cuja implementação se centra essencialmente na função 
`SingleTask * multipleRestaurantsRequest(Graph<Coordinates> & graph, Graph<Coordinates> & reducedGraph, vector<Employee*> & employees, Request & request)` - definida em `SingleTask.cpp`.
Para isso, determinam-se, mais uma vez, quais os estafeta eligíveis para realizar o pedido. Neste caso, no entanto, só podemos descartar, numa fase inicial, aqueles estafetas que não possuam capacidade para transportar a carga do pedido. 
Seguidamente, determina-se para cada estafeta o caminho a seguir para recolher o pedido dos restaurantes, escolhendo sempre o restaurante mais perto  - `int getNearestRestaurant(Graph<Coordinates> & graph, const Coordinates & origin, vector<Coordinates> & restaurants)`; (consultando a matriz de distâncias pré calculada com o algoritmo de Floyd Warshall). Mantém-se sempre guardada a melhor distância, o estafeta ao qual essa distância corresponde e a ordem de visita dos restaurantes, tendo sempre em atenção que pode não existir caminho possível, no caso de alguns meios de transporte (dependendo do grafo de entrada). No fim, é escolhido o estafeta ao qual corresponde a melhor distância.

Mais uma vez, para definir o caminho completo a percorrer pelo estafeta, utiliza-se a função `setFloydWarshallPath(Graph<Coordinates> & graph)` - em `SingleTask.cpp`; que calcula o caminho mais curto entre restaurantes consecutivos cuja ordem de visita já fora determinada no algoritmo descrito.

```cpp
multipleRestaurantsRequest(Graph G1, Graph G2, vector<Employee> E, Request request){
    vector<Coordinates> restaurants // Restaurantes por ordem de visita
    int nearestEmployeePos // Estafeta ao qual corresponde a melhor distância
    int nearestRestaurantPos // Restaurante mais próximo dos que faltam visitar  
    double nearestEmployeeDist ← INF // Inicializar a melhor distância com valor elevado

    employees ← getEligibleEmployeesMultipleRestaurants(E, request);

    for i = 0 to E.size(): // Repetir procedimento para cada estafeta disponível
        double totalDist ← 0
        Coordinates orig ← coords(E[i]) // Posição inicial do estafeta
        vector<Coordinates> requestRestaurants ← checkpoints(request) // Restaurantes por visitar
        vector<Coordinates> restaurantsPath // Ordem de visita dos restaurantes

        for j = 0 to checkpoints(request).size() :
            double dist ← 0; // Calcular distância a percorrer pelo estafeta
            if vehicle(E[i]) == CAR ||vehicle(E[i]) == MOTORCYCLE :
                // Restaurante por visitar mais perto do anterior
                nearestRestaurantPos ← getNearestRestaurant(G1, orig, requestRestaurants) 

                dist ← G1.getDist(orig, requestRestaurants[nearestRestaurantPos]);
                //...
                if dist == INF : // Não foi encontrado caminho
                    totalDist ← INF
                    break
            
            else if vehicle(E[i]) == BIKE ||vehicle(E[i]) == FOOT : //...

            totalDist ← totalDist + dist // Acumular distância
            // Guardar restaurantes por ordem de visita
            restaurantsPath.push_back(requestRestaurants[nearestRestaurantPos])
            // Atualizar posição anterior
            orig ← requestRestaurants[nearestRestaurantPos] 
            // Eliminar dos restaurantes por visitar
            requestRestaurants.erase(requestRestaurants.begin() + nearestRestaurantPos) 

        // Não escolher o estafeta
        if totalDist == INF || 
        (totalDist > 6000 && (vehicle(E[i]) == BIKE || vehicle(E[i]) == FOOT))):
            continue

        // Adicionar a distância à morada de destino
        if vehicle(E[i]) == CAR || vehicle(E[i]) == MOTORCYCLE :
            double dist ← G.getDist(restaurantsPath[restaurantsPath.size()-1]),deliveryAddr(request))
            //...
            if(dist == INF) break
            totalDist ← totalDist + dist
        
        else if vehicle(E[i]) == BIKE || vehicle(E[i]) == FOOT) :
            double dist ← G.getDist(restaurantsPath[restaurantsPath.size()-1]),deliveryAddr(request))
            //...
            if(dist == INF || totalDist + dist > 6000) break;
             totalDist ← totalDist + dist
        
        // Melhor distância -> mudar estafeta escolhido
        if totalDist < nearestEmployeeDist : 
            nearestEmployeePos ← i
            nearestEmployeeDist ← totalDist
            restaurants ← restaurantsPath
    }

    // Se não foi encontrado nenhum estafeta para realizar o pedido retornar tarefa vazia
    if nearestEmployeeDist == INF : return SingleTask(nullptr, request)

    request.setCheckpoints(restaurants) // Guardar os restaurantes por ordem de visita
    SingleTask task ← SingleTask(E[nearestEmployeePos], request) // Associar pedido e estafeta

    if vehicle(task) == CAR || vehicle(task) == MOTORCYCLE:
        task.setFloydWarshallPath(G1) // Construção do caminho do estafeta
    if vehicle(task) == BIKE || vehicle(task) == FOOT :
        task.setFloydWarshallPath(G2)

    return task
}

```

## 6.3 Um estafeta - Vários pedidos no mesmo deslocamento (variante do TSP)

Outra alternativa que pensamos ser essencial incluir na nossa implementação, tendo em conta a essência do problema, foi o caso em que um só estafeta deve, num só trajeto, recolher todos os pedidos dos restaurantes e entregá-los nas respetivas moradas de entrega, tendo em atenção que o restaurante de um pedido deve sempre ser visitado antes da morada de entrega e que podem existir múltiplos pedidos do mesmo restaurante.

Para isso, na função `SpecialTask * simultaneousRequests(Graph<Coordinates> & graph, vector<Request> & requests, Employee* employee)` - definida em `SpecialTask.cpp`; utilizam-se dois vetores auxiliares que acabam por funcionar como filas, uma com o restaurante não visitado mais próximo da posição atual do estafeta à cabeça e outra com a morada de entrega não visitada mais próxima da posição atual do estafeta à cabeça.
Estas posições mais próximas são atualizadas nas funções: 
`setNearestRestaurant(Graph<Coordinates> & graph, vector<Request>  & requests, Coordinates origin)` 
e 
`setNearestDeliveryAddress(Graph<Coordinates> & graph, vector<Request>  & requests, Coordinates origin)`, chamadas a cada iteração.

Enquanto existirem restaurantes ou moradas de entrega por visitar, o próximo ponto a visitar é escolhido do seguinte modo:
- Na primeira iteração e sempre que não há pedidos para entregar é necessário recolher um pedido de um restaurante;
- Quando a carga máxima é atingida ou já foram recolhidos todos os pedidos é necessário entregar um pedido;
- Se existir capacidade para tal, recolhe-se múltiplos pedidos de restaurantes dos quais tenha sido feito mais do que um pedido;
- No caso de haver possibilidade de entregar ou recolher um pedido, opta-se por escolher o deslocamento de menor distância;

A ordem de visita dos vários pontos é guardada num vetor, que mantém a associação das coordenadas do ponto com o pedido ao qual este está associado, de modo a facilitar cálculos posteriores de tempos estimados.

Finalmente, é definido o caminho completo e também os tempos estimados para cada pedido na função 
`setFloydWarshallPath(Graph<Coordinates> & graph, const vector<pair<Coordinates,unsigned long>> & checkpoints)` - em `SpecialTask.cpp`; que procede de modo similar à função do mesmo nome descrita anteriormente, calculando o caminho mais curto entre cada par de pontos consecutivos do caminho parcial.

```cpp
simultaneousRequests(Graph G, vector<Request> R, Employee employee){
    vector<Coordinates> path // Pontos por ordem de visita
    Coordinates orig ← coordinates(employee) // Ponto de origem
    
    vector<Request> pick ← R // Pedidos a recolher do restaurante
    setNearestRestaurant(G, pick, orig) // Restaurante mais perto da origem na frente
    vector<Request> deliver; // Pedidos recolhidos, a ser entregues nas moradas

    int totalCargo ← 0;
    while deliver == ∅ || pick == ∅ :
        // Estafeta não tem mais capacidade / Não há mais pedidos para recolher
        if totalCargo == maxCargo(e) || pick == ∅ :
            // Entrega pedido já recolhido (da morada mais perto)
            orig ← deliveryAddr(deliver.front())
            path.push_back(orig)
            totalCargo ← totalCargo - cargo(deliver.front())
            deliver.erase(deliver.begin())

        // Não há mais pedidos para entregar
        else if deliver == ∅ :
            // Recolher pedido(s) do restaurante mais perto da localização atual
            orig ← restaurant(pick.front())
            path.push_back(orig)
            totalCargo ← totalCargo + cargo(pick.front())

            // Recolher pedidos do mesmo restaurante, se possível(verifica carga)
            repeatedRestaurants(pick,deliver,totalCargo,maxCargo(employee));

            // Adicionar aos pedidos a entregar, remover dos pedidos a recolher
            deliver.push_back(pick.front())
            pick.erase(pick.begin())
        
        // Escolher a opção mais próxima - recolher ou entregar um pedido
        // Se não tiver capacidade entrega um pedido
        else:
            if(totalCargo + cargo(pick.front()) > maxCargo(employee) ||
                G.getDist(orig,deliveryAddr(deliver.front())) < G.getDist(orig,restaurant(pick.front()))):
                //...Entrega um pedido...
            else: //...Recolhe pedido(s) do restaurante mais perto...

        // Manter na frente o restaurante mais perto da nova origem
        setNearestRestaurant(G,pick,orig)
        // Manter na frente a morada (dos pedidos recolhidos) mais perto da origem
        setNearestDeliveryAddress(G,deliver,orig)

    SpecialTask s(employee,R) // Atribui pedidos ao estafeta
    // Constrói caminho total a partir da ordem de visita dos restaurantes e moradas 
    s.setFloydWarshallPath(G,path)
    return s
}

```

## 6.4 Nota geral acerca dos algoritmos implementados

Por fim, é de salientar a vantagem proporcionada pelo pré-processamento com o algoritmo de Floyd Warshall quando utilizados algoritmos como os descritos acima.
Para efeitos de comparação, no entanto, podem ser consultados em `simulations.cpp` e em `SingleTask.cpp` os algoritmos que testamos na Fase II e que utilizam o algoritmo de Dijkstra na sua implementação. Também a análise das funções 
`virtual void setFloydWarshallPath(Graph<Coordinates> & graph)`
e 
`void setDijkstraPath(Graph<Coordinates> & graph)` permite facilmente perceber que, ao utilizar o Floyd Warshall, é evitado o cálculo repetitivo das distâncias e do caminho mais curto para cada novo ponto de origem, uma desvantagem do Dijkstra. 

*Parte da função utilizada para definir o caminho final de um estafeta, nos algoritmos *1* e *2**

```cpp 
void SingleTask::setFloydWarshallPath(Graph<Coordinates> & graph){
    //...
    // Percorrer coordenadas do pedido - por ordem de visita
    for(Coordinates checkpoint: request.getCheckpoints()){
        // Caminho mais curto desde o ponto anterior
        tempPath = graph.getfloydWarshallPath(orig, checkpoint); 
        // Acumular a distância
        totalDistance += graph.getDist(graph.findVertexIdx(orig), graph.findVertexIdx(checkpoint)); 
        //...
        // Adicionar caminho calculado ao caminho construído até então
        path.insert(path.end(),tempPath.begin()+1, tempPath.end());
        orig = checkpoint; // Definir novo ponto de origem
    }
    //...
}
```