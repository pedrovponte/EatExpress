EatExpress

Instruções de compilação

No CLion, abra um projeto, selecionando o diretório atual.
Efetuar “Load CMake Project” sobre o ficheiro CMakeLists.txt.
Executar o projeto (Run).

Lista de dependências

Descomprimindo o zip, o diretório deve conter, para além deste ficheiro, os diretórios lib, src e Mapas e os ficheiros CMakeLists.txt,  main.cpp e relatorio.pdf.

Bibliotecas e API's

- GraphViewer API - proveniente das aulas práticas (lib/graphViewer, lib/GraphViewerController)
- Google Tests (lib/googletest-master)

Código fonte

No diretório src devem existir os seguintes diretórios:
- app, contendo os ficheiros: app.h e app.cpp
- eatExpress, contendo os ficheiros: Coordinates.h, Coordinates.cpp, Employee.h, Employee.cpp, Request.h, Request.cpp, SingleTask.h, SingleTask.cpp, SpecialTask.h, SpecialTask.cpp, Task.h e Task.cpp
- graph, contendo os ficheiros: Vertex.h, Edge.h, Graph.h e 
- phase_tests, contendo os ficheiros: p1_test.cpp, p2_test.cpp, p3_test.cpp
- simulations, contendo os ficheiros: simulations.h e simualtions.cpp
- utils, contendo os ficheiros:  utils.h, utils.cpp e tests.cpp

Ficheiros de input

No diretório Mapas encontram-se os ícones usados e ficheiros de input distribuídos pelos diretórios:
- GridGraphs, contendo os diretórios 4x4, 8x8, 16x16,16x16Bike, 16x16Random 20x20, 20x20Bike, 30x30, 30x30Bike cada um com dois ficheiros, edges.txt e nodes.txt
-GridGraphsTags, contendo os diretórios 4x4, 8x8, 16x16,16x16Bike, 16x16Random 20x20, 20x20Bike, 30x30, 30x30Bike cada um com um ficheiro tags_(nomeDoSubdiretorio).txt
-icons
-Penafiel, contendo distances_penafiel.txt, edges_penafiel.txt, nodes_x_y_penafiel.txt, predecessor_penafiel.txt e tags_penafiel.txt


- Os ficheiros de input utilizados encontram-se na pasta Mapas e correspondem, essencialmente, aos ficheiros com as informações sobre os nós e sobre as arestas de cada um dos mapas utilizados. Contém ainda, para cada mapa, um ficheiro de tags para identificar os vértices onde se localizam os restaurantes. 
- Na pasta da cidade Penafiel existem ainda 2 ficheiros que correspondem às matrizes de distâncias e do predecessor no caminho mais curto do grafo correspondente à cidade, pré-processado com o algoritmo de Floyd Warshall.