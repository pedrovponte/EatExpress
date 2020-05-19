import matplotlib.pyplot as plt

x = [256, 142, 400, 206, 900, 498]
y1 = [256, 9, 400, 10, 900, 10]
y2 = [256, 20, 400, 17, 900, 26]

plt.scatter(x, y1, marker='o')

plt.savefig("../logs/phase3/connectivity.png")