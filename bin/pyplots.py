import matplotlib.pyplot as plt
import pandas as pd

def grid_plot( graph, xmax = 110, ymax = 1000000, subtitle = "_all", xsteps = 10, type = ''):
    plt.close()
    dijkstra = pd.read_csv("../logs/phase1/dijkstra_ph1_" + str(graph) +  ".csv")
    floyd = pd.read_csv("../logs/phase1/floyd_ph1_" + str(graph) +  ".csv")
    plt.title('Dijkstra vs Floyd Warshall | Grid ' + str(graph))

    plt.plot(list(dijkstra['n']), list(dijkstra['us']),'r'+type, list(floyd['n']), list(floyd['us']), 'g'+type)
   
    plt.axis([0, min(xmax, 110), 0, min(ymax, dijkstra['us'][99] + 200)])
    plt.ylabel("Tempo Total (us)")
    plt.xlabel("Número de Pedidos")
    plt.xticks(range(0,min(xmax,110),xsteps))
    plt.legend("DF")
    plt.savefig("../logs/phase1/" + str(graph) + subtitle +".png")

##########################################################

def dijkstra_plot():
    plt.close()

    graph = "4x4"
    dijkstra4x4 = pd.read_csv("../logs/phase1/dijkstra_ph1_" + str(graph) +  ".csv")
    
    graph = "8x8"
    dijkstra8x8 = pd.read_csv("../logs/phase1/dijkstra_ph1_" + str(graph) +  ".csv")

    graph = "16x16"
    dijkstra16x16 = pd.read_csv("../logs/phase1/dijkstra_ph1_" + str(graph) +  ".csv")

    x4 = [dijkstra4x4['us'][i] for i in range(0,100,10)]
    x8 = [dijkstra8x8['us'][i] for i in range(0,100,10)]
    x16 = [dijkstra16x16['us'][i] for i in range(0,100,10)]

    ind = [i for i in range(0,100,10)]
    width = 2
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.bar(ind, x16, width, color='g')
    ax.bar(ind, x8, width, color='b')
    ax.bar(ind, x4, width, color='r')
    ax.set_ylabel('Tempo Total (us)')
    ax.set_xlabel('Número de Pedidos')
    ax.set_title('Dijkstra Grids')
    ax.set_xticks(ind)
    ax.set_yticks(range(0,20000,2000))
    ax.legend(labels=["16x16","8x8","4x4"])
    plt.savefig("../logs/phase1/" + "DijkstraG.png")

##########################################################

def floyd_plot():
    plt.close()

    graph = "4x4"
    floyd4x4 = pd.read_csv("../logs/phase1/floyd_ph1_" + str(graph) +  ".csv")
    
    graph = "8x8"
    floyd8x8 = pd.read_csv("../logs/phase1/floyd_ph1_" + str(graph) +  ".csv")

    graph = "16x16"
    floyd16x16 = pd.read_csv("../logs/phase1/floyd_ph1_" + str(graph) +  ".csv")

    x4 = [floyd4x4['us'][i] for i in range(0,100,10)]
    x8 = [floyd8x8['us'][i] for i in range(0,100,10)]
    x16 = [floyd16x16['us'][i] for i in range(0,100,10)]

    ind = [i for i in range(0,100,10)]
    width = 2
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.bar(ind, x16, width, color='g')
    ax.bar(ind, x8, width, color='b')
    ax.bar(ind, x4, width, color='r')
    ax.set_ylabel('Tempo Total (us)')
    ax.set_xlabel('Número de Pedidos')
    ax.set_title('Floyd Grids')
    ax.set_xticks(ind)
    ax.set_yticks(range(0,3000,300))
    ax.legend(labels=["16x16","8x8","4x4"])
    plt.savefig("../logs/phase1/" + "FloydG.png")

##########################################################

grid_plot("4x4")
grid_plot("4x4",5,100, "_head",1,'o')
grid_plot("8x8")
grid_plot("8x8",10,400, "_head",1,'o')
grid_plot("16x16")
grid_plot("16x16",20,2500, "_head",2,'o')
dijkstra_plot()
floyd_plot()