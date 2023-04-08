import matplotlib.pyplot as plt
import numpy as np

f = open("x.txt", "r")
x = np.fromfile(f, sep = " ")

f = open("v.txt", "r")
v = np.fromfile(f, sep = " ")

f = open("Ek.txt", "r")
Ek = np.fromfile(f, sep = " ")

f = open("Ve.txt", "r")
Ve = np.fromfile(f, sep = " ")

f = open("E.txt", "r")
E = np.fromfile(f, sep = " ")

f = open("tryb.txt", "r")
metoda = np.fromfile(f, count = 1, dtype = np.int8, sep = " ")  

if metoda == 1:
    metoda = "Euler"
elif metoda == 2:
    metoda = "Trapezy"

dt = np.fromfile(f, count = 1, dtype = np.float64, sep = " ")
alfa = np.fromfile(f, count = 1, dtype = np.float64, sep = " ")
czas = x.size*dt

t = np.linspace(0, czas, x.size)

f.close()

fig, ax = plt.subplots(figsize = (10, 15),nrows = 3, ncols = 2)

rect = plt.Rectangle(
    # (lower-left corner), width, height
    (0.00, 0.00), 1, 1, fill=False, color="black", lw=4, 
    zorder=0, transform=fig.transFigure, figure=fig
)
fig.patches.extend([rect])

ax1 = plt.subplot(3,2,1)
ax1.set_title('Położenie')
plt.plot(t, x)

ax1 = plt.subplot(3,2,2)
ax1.set_title('Prędkoć')
plt.plot(t, v)

ax1 = plt.subplot(3,2,3)
ax1.set_title('Energia kinetyczna')
plt.plot(t, Ek)

ax1 = plt.subplot(3,2,4)
ax1.set_title('Energia potencjalna')
plt.plot(t, Ve)

ax1 = plt.subplot(3,1,3)
ax1.set_title('Energia całkowita')
plt.plot(t, E)

name = metoda + " ,dt=" + str(dt) + " ,czas=" + str(czas) + " ,alfa=" + str(alfa) + ".png"

plt.savefig(name)


