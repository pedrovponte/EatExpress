##FASE III

### Fatores a considerar
1. distância do estafeta ao restaurante
2. meio de transporte do estafeta
3. capacidade máxima de transporte do estafeta


### Pre-processamento com Floyd Warshall e Grafos de entrada (ideais possíveis)

##### Ficheiros
   - ter um ficheiro de tags para cada grid map com arestas não acessíveis a pé/bicicleta e que são marcadas no grafo
   - igual mas em vez de um ficheiro de tags ter 2 ficheiros de arestas, um para carro/motociclo e outro para bicicleta/a pé. Neste caso uma ideia é manipular também as distâncias de modo a serem maiores nos grafos a pé/bicicleta.

##### Grafos/Matrizes de distâncias
   - calcular duas matrizes de distâncias, uma considerando todas as arestas (carro/mota) e outra só considerando as que não estão marcadas como inacessíveis para deslocamentos a pé/bicicleta
   - ter 2 grafos

##### Guardar dados
 As distâncias para cada grafo / as 2 matrizes de distâncias podiam já estar pre-processadas e guardadas em ficheiros para não estarmos a perder muito tempo no início do programa.


### Ideias para o algoritmo para esta fase, com o Floyd Warshall:

##### Dados de Entrada: 
- 2 grafos - um para bicicleta/a pé e outro para carro/mota ou 1 grafo com duas matrizes de distâncias
- queue de pedidos com dimensões diferentes
- vetor de estafetas com capacidades e meios de transporte diferentes

##### Variáveis temporárias: 
- Apontador para o estafeta escolhido até ao momento sendo importante:
   - a sua distância até ao restaurante
   - a sua capacidade de transporte
   - o seu meio de transporte
- bool que indica se o estafeta foi o primeiro a ser analisado e, por isso, foi imediatamente escolhido


1. Obter matriz de distâncias

2. Para cada pedido na queue de pedidos:
	- Excluir estafetas que não têm capacidade para transportar o pedido ou que não estão disponíveis
	   - para cada pedido haveria um vetor de estafetas disponíveis(com capacidade e disponibilidade para o transportar)

	- Excluir estafetas que não consigam deslocar-se para o restaurante, pois deslocam-se a pé/bicicleta e não existe caminho possível para o restaurante.

	- **Escolher ou não um estafeta em comparação com o anterior:**
	   - Ainda não se escolheu nenhum (1ª estafeta a ser comparado)
		   - ESCOLHER sempre e colocar bool a true.
	   - Ambos se deslocam de carro/mota
		   - Estafeta está mais afastado que o anterior e tem maior capacidade = NÃO ESCOLHER
		   - Estafeta está mais perto do que o anterior e tem menor capacidade = ESCOLHER
		   - Estafeta está mais afastado do que o anterior e tem menos capacidade OU está mais perto e tem maior capacidade
			   - **Como escolher?**
	   -Ambos se deslocam a pé/bike
         - Estafeta está mais afastado que o anterior e tem maior capacidade = NÃO ESCOLHER
         - Estafeta está mais perto do que o anterior e tem menor capacidade = ESCOLHER
         - Estafeta está mais afastado do que o anterior e tem menos capacidade OU está mais perto e tem maior capacidade
            - **Como escolher?**
	   - Anterior desloca-se a pé e o atual de carro
		   - O anterior está mais afastado do que o limite para entregas a pé = ESCOLHER se a capacidade não for demasiado grande
	   - Anterior desloca-se de carro  e o atual a pé
		   - O atual não está mais afastado do que o limite para entregas a pé = ESCOLHER
	