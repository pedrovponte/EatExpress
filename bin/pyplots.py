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

    graph = "20x20"
    dijkstra20x20 = pd.read_csv("../logs/phase1/dijkstra_ph1_" + str(graph) +  ".csv")

    x4 = [dijkstra4x4['us'][i] for i in range(0,100,10)]
    x8 = [dijkstra8x8['us'][i] for i in range(0,100,10)]
    x16 = [dijkstra16x16['us'][i] for i in range(0,100,10)]
    x20 = [dijkstra20x20['us'][i] for i in range(0,100,10)]

    ind = [i + 10 for i in range(0,100,10)]
    width = 2
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.bar(ind, x20, width, color='black')
    ax.bar(ind, x16, width, color='g')
    ax.bar(ind, x8, width, color='b')
    ax.bar(ind, x4, width, color='r')
    ax.set_ylabel('Tempo Total (us)')
    ax.set_xlabel('Número de Pedidos')
    ax.set_title('Dijkstra Grids')
    ax.set_xticks(ind)
    ax.set_yticks(range(0,35000,2000))
    ax.legend(labels=["20x20","16x16","8x8","4x4"])
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

    graph = "20x20"
    floyd20x20 = pd.read_csv("../logs/phase1/floyd_ph1_" + str(graph) +  ".csv")

    x4 = [floyd4x4['us'][i] for i in range(0,100,10)]
    x8 = [floyd8x8['us'][i] for i in range(0,100,10)]
    x16 = [floyd16x16['us'][i] for i in range(0,100,10)]
    x20 = [floyd20x20['us'][i] for i in range(0,100,10)]

    ind = [i + 10 for i in range(0,100,10)]
    width = 2
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.bar(ind, x20, width, color='black')
    ax.bar(ind, x16, width, color='g')
    ax.bar(ind, x8, width, color='b')
    ax.bar(ind, x4, width, color='r')
    ax.set_ylabel('Tempo Total (us)')
    ax.set_xlabel('Número de Pedidos')
    ax.set_title('Floyd Grids')
    ax.set_xticks(ind)
    ax.set_yticks(range(0,8000,500))
    ax.legend(labels=["20x20","16x16","8x8","4x4"])
    plt.savefig("../logs/phase1/" + "FloydG.png")

##########################################################

grid_plot("4x4")
grid_plot("4x4",5,100, "_head",1,'o')
grid_plot("8x8")
grid_plot("8x8",10,400, "_head",1,'o')
grid_plot("16x16")
grid_plot("16x16",20,2500, "_head",2,'o')
grid_plot("20x20")
grid_plot("20x20",30,10000, "_head",2,'o')
grid_plot("30x30")
grid_plot("30x30",80,55000, "_head",10,'o')
dijkstra_plot()
floyd_plot()

def table():
    
    graph = "8x8"
    dijkstra8x8 = pd.read_csv("../logs/phase1/dijkstra_ph1_" + str(graph) +  ".csv")

    graph = "16x16"
    dijkstra16x16 = pd.read_csv("../logs/phase1/dijkstra_ph1_" + str(graph) +  ".csv")

    graph = "20x20"
    dijkstra20x20 = pd.read_csv("../logs/phase1/dijkstra_ph1_" + str(graph) +  ".csv")
    
    graph = "8x8"
    floyd8x8 = pd.read_csv("../logs/phase1/floyd_ph1_" + str(graph) +  ".csv")

    graph = "16x16"
    floyd16x16 = pd.read_csv("../logs/phase1/floyd_ph1_" + str(graph) +  ".csv")

    graph = "20x20"
    floyd20x20 = pd.read_csv("../logs/phase1/floyd_ph1_" + str(graph) +  ".csv")

    table = []
    for i in range(0,100,5):
        temp = []
        temp.append(i + 5)
        temp.append(dijkstra8x8['us'][i])
        temp.append(dijkstra16x16['us'][i])
        temp.append(dijkstra20x20['us'][i])
        temp.append(floyd8x8['us'][i])
        temp.append(floyd16x16['us'][i])
        temp.append(floyd20x20['us'][i])
        table.append(temp)

    plt.close()

    fig, axs = plt.subplots(1,1)
    collabel=("Número de Pedidos",
        "Dijkstra 8x8", "Dijkstra 16x16", "Dijkstra 20x20",
        "Floyd 8x8","Floyd 16x16","Floyd 20x20")
    axs.axis('tight')
    axs.axis('off')
    the_table = axs.table(cellText=table,colLabels=collabel,loc='center')
    plt.savefig("../logs/phase1/table.png", dpi=300)

table()