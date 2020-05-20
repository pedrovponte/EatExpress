import matplotlib.pyplot as plt
import pandas as pd
import math as m

dijkstra = pd.read_csv("../logs/phase1/dijkstra_ph1_cplxty.csv")


print(dijkstra)
linearithmic = [(3/2*dijkstra['n'][i])*(m.log(dijkstra['n'][i])) for i in range(len(dijkstra['n']))]
dijkstra['n'] = [i*10 for i in dijkstra['n']]

plt.plot(list(dijkstra['n']), list(dijkstra['d']),'-or',list(dijkstra['n']), linearithmic,'-og')
plt.ylabel("Tempo Total (us)")
plt.xlabel("Número de vértices")
plt.legend(["Dijkstra","aprox (V+E) * log(V)"])
plt.savefig("../logs/phase1/Dijkstra-Floyd-Dtime.png")

plt.close()

cubic = [m.pow(dijkstra['n'][i]/25,3) for i in range(len(dijkstra['n']))]

plt.plot(list(dijkstra['n']), list(dijkstra['f']),'-or',list(dijkstra['n']), cubic,'-og')
plt.ylabel("Tempo Total (us)")
plt.xlabel("Número de vértices")
plt.legend(["Floyd-Warshall","aprox V³"])
plt.savefig("../logs/phase1/Dijkstra-Floyd-Ftime.png")