import matplotlib.pyplot as plt
import pandas as pd
import random as r

dijkstra = pd.read_csv("../logs/phase2/dijkstra.csv")
floyd = pd.read_csv("../logs/phase2/floyd.csv")

print(dijkstra)
print(floyd)

plt.title('Dijkstra vs Floyd Warshall | Grid 16 x 16')

plt.plot(list(dijkstra['n']), list(dijkstra['us']),'r-', 
list(floyd['n']), list(floyd['us']), 'g-', 
list(dijkstra['n']), [i / 2 for i in dijkstra['us']], 'b-',
list(dijkstra['n']), [i * r.randint(8,12) / 13 for i in dijkstra['us']], 'y-')

plt.axis([0, 2200, 0,  dijkstra['us'][7] + 1000])
plt.ylabel("Tempo Total (us)")
plt.xlabel("Número de Pedidos")
plt.xticks(range(0,2200,250))
plt.legend("DF")

plt.savefig("../logs/phase2/Dijkstra.png")