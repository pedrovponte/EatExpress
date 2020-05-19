# 5. Implementação

Iniciada a parte de implementação prática de tudo o que foi discutido anteriormente, os dados de partida, mapas e código genérico foram recolhidos e as novas classes foram criadas, de acordo com tudo o que foi estabelecido como dados de entrada. É de notar que as soluções, disponibilizadas em código nas aulas práticas, para os grafos, vértices e arestas e respetivos algoritmos foram adaptadas e reorganizadas, para melhor satisfazerem as nossas necessidades.

## 5.1 Grafos e Mapas usados

Em matéria de testes, para uma possível readaptação futura em grafos com representação real de áreas urbanas, foram usados grafos em forma de grelha, de diversas dimensões e alguns com distâncias e arestas aleatoriamente distribuídas. A utilização de diferentes mapas com dimensões, em número de vértices, $N \times N$, fortemente conexos, permitiu uma mais fácil visualização de todo o processo e uma fundamentação mais cuidada na escolha de determinados algoritmos. Exemplos de grafos utilizados na implementação são os seguintes:


![](../logs/8x8-graph.png)  |  ![](../logs/30x30-graph.png)
:-------------------------:|:-------------------------:
Grafo $8 \times 8$ | Grafo $30 \times 30$

Todos os grafos presentes na aplicação têm as localizações dos seus restaurantes definidas inicialmente e os seus vértices, na API de visualização, distinguidos com diferentes ícones, para os diferentes tipos de restaurante. Para o grafo $8 \times 8$, por exemplo, a lista de restaurantes existentes é:
```cpp
Type: Fast Food         Vertex id: 10
Type: Pizzeria          Vertex id: 13
Type: Restaurant        Vertex id: 25
Type: Restaurant        Vertex id: 58
Type: Fast Food         Vertex id: 73
Type: Vegetarian        Vertex id: 80
```

## 5.2 Análise empírica

Para uma análise generalizada e abrangente dos algoritmos tidos em consideração, estes foram testados em todos os grafos elegíveis e à nossa disposição. Os testes foram efetuados em conformidade com as fases de elaboração determinadas anteriormente e a sua eficiência temporal foi avaliada.

### 5.2.1 Fase I

Na Fase I de implementação, considerado o caso atómico de um estafeta que entrega apenas um pedido, entre um restaurante e a morada de um cliente, realizando todas as tarefas em sequência, foi calculada a média do tempo demorado na realização de 1 a 100 pedidos, para os algoritmos mais genéricos, neste caso, o Dijkstra unidirecional e o Floyd-Warshall. Os tempos foram medidos em micro-segundos e os grafos considerados tinham dimensões variando entre $4 \times 4$ e $30 \times 30$, como relatam os seguintes dados:


![](../logs/phase1/4x4_all.png)  |  ![](../logs/phase1/16x16_all.png)
:-------------------------:|:-------------------------:
![](../logs/phase1/20x20_all.png)  |  ![](../logs/phase1/30x30_all.png)

Uma aproximação aos dados do grafo de dimensões $20 \times 20$, por exemplo, revela um pormenor interessante relativamente à concorrência entre estes dois algoritmos e à sua rentabilidade, para uso na aplicação. A explicação para os valores reside no facto de o algoritmo de Floyd-Warshall demorar ligeiramente mais tempo, inicialmente, devido ao pré-processamento necessário, mantendo, de seguida, um tempo médio de execução de cada pedido muito inferior, sendo logo ultrapassado, em matéria de tempo acumulado total, pelo algoritmo de Dijkstra, com um comportamento linear mais acentuado.

![](../logs/phase1/20x20_head.png)

A partir de um certo número de pedidos, o algoritmo de Floyd-Warshall torna-se o mais viável, o que satisfaz as necessidades, a longo prazo, de uma aplicação deste tipo, tanto em grafos grandes, como em grafos mais pequenos, já que o custo de operação do algoritmo de Dijkstra aumenta consideravelmente.

![](../logs/phase1/DijkstraG.png)  |  ![](../logs/phase1/FloydG.png)
:-------------------------:|:-------------------------:

O tempo médio gasto a cada pedido, para o algoritmo de Dijkstra, revela, assim, o esperado e aproximado tempo computacional de proporções $O(E + V \log V )$, ou "linearítmico". O pré-processamento realizado pelo algoritmo de Floyd-Warshall, contabilizado apenas como parte do primeiro pedido, revela a sua complexidade na ordem $O(V³)$ e um tempo de execução mínimo para a reconstrução dos caminhos, na ordem $O(E)$, com $E$ o número de arestas entre os dois vértices em consideração. Os valores mais precisos, em micro-segundos, para cada um destes gráficos, encontram-se na tabela seguinte:

![](../logs/phase1/table.png)

Com isto, confirmamos também a complexidade temporal destes algoritmos e reafirmamos e fundamentamos as escolhas para as fases seguintes.

### 5.2.2 Fase II

Nesta segunda fase, voltámos a analisar a execução dos algoritmos, desta vez, tendo em conta a existência de vários estafetas e a distribuição de vários pedidos pelos funcionários disponíveis e elegíveis para os entregar. É de notar que a escolha do estafeta encarregue de determinado pedido era diretamente influenciada pela sua proximidade ao restaurante, o que implicava ainda mais cálculos intermédios e mais execuções dos algoritmos usados. Foram gerados, portanto, pedidos e a cada tarefa concluída, os estafetas atualizavam a sua posição. 

```cpp
    // Add Employees
    vector<Employee> employees;
    Employee employee1(0,Coordinates(10),1000,CAR,true);
    employees.push_back(employee1);
    Employee employee2(1,Coordinates(20),1000,CAR,true);
    employees.push_back(employee2);
    Employee employee3(2,Coordinates(30),1000,CAR,true);
    employees.push_back(employee3);

    // Add Requests
    vector<Request> requests = getRandomRequests(graph,2000);
    queue<Request> requestsQueue;
    for(Request request : requests){
        requestsQueue.push(request);
    }

    // ... Same logic for the Floyd Algorithm

    while(!requestsQueue.empty()){
        vector<SingleTask*> tasks = distributeRequestsByCloseness_Dijkstra(graph, requestsQueue, employees);

        // Couldn't find any Employees to fulfill the remaining requests
        if(tasks.empty())
            return 0;

        // Get requests distribution and paths
        for(int i = 0; i < tasks.size(); i++){
            tasks[i]->setDijkstraPath(graph);
        }
        requestsRound++;
    }
```

Para efeitos de teste desta fase de implementação, considerou-se a existência de 3 estafetas, distribuídos aleatoriamente por um grafo, representativo de uma área urbana, de dimensões $16 \times 16$, e geraram-se até 2000 pedidos também aleatórios.

### 5.2.3 Fase III

Aqui, variados meios de transporte começaram já a ser considerados, o que correspondeu à necessidade de criar mapas adaptados, partindo dos já existentes. A solução, em conformidade com as simulações efetuadas, foi reconverter os mapas em grelha para grafos com um número inferior de vértices e arestas disponíveis, simulando a transitabilidade de certas vias e a sua acessibilidade, conforme o meio de transporte. Um exemplo de um grafo adaptado para servir estafetas que se desloquem a pé, ou de bicicleta, é o seguinte:

![](../logs/phase3/16x16-original.png)  |  ![](../logs/phase3/16x16-bike.png)
:-------------------------:|:-------------------------:
Grafo original para veículos motorizados | Grafo reduzido para estafetas a pé ou de bicicleta

