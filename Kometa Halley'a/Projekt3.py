import matplotlib.pyplot as plt
import numpy as np

au = 149597870700
rok = 31536000

f = open("x.txt", "r")
x = np.fromfile(f, sep = " ")/au

f = open("y.txt", "r")
y = np.fromfile(f, sep = " ")/au

f = open("tryb.txt", "r")
tryb = np.fromfile(f, count = 1, dtype = np.int8, sep = " ")  
krok = np.fromfile(f, count = 1, dtype = np.int8, sep = " ")  
if krok == 2:
    tol = np.fromfile(f, count = 1, sep = " ")
else:
    tol = "nan"

if krok == 1:
    f = open("t.txt", "r")
    czas = np.fromfile(f, sep = " ")/rok
    t = np.linspace(0, czas, x.size)
    f.close()
elif krok == 2:
    f = open("t.txt", "r")
    t = np.fromfile(f, sep = " ")/rok
    f.close()


fig, ax = plt.subplots(figsize = (10, 5),nrows = 1, ncols = 2)

rect = plt.Rectangle(
    #(lower-left corner), width, height
    (0.00, 0.00), 1, 1, fill=False, color="black", lw=4, 
    zorder=0, transform=fig.transFigure, figure=fig
)
fig.patches.extend([rect])

ax1 = plt.subplot(1,2,1)
ax1.set_title('y(x)')
ax1.set_xlabel("x [au]")
ax1.set_ylabel("y [au]")
ax1.set_ylim(-70, 10)
ax1.set_xlim(-40, 40)
plt.plot(x, y)
plt.plot(0, 0, 'ro')

ax1 = plt.subplot(1,2,2)
ax1.set_title('y(t)')
ax1.set_xlabel("t [lat]")
ax1.set_ylabel("y [au]")
ax1.set_ylim(-70, 10)
ax1.set_xlim(0, 415)
plt.plot(t, y)

if tryb == 1:
    metoda = "Euler"
elif tryb == 2:
    metoda = "RK4"
    
if krok == 1:
    r_krok = "const"
elif krok == 2:
    r_krok = "auto"
 
name = metoda + ", " + r_krok + ", " + "tol=" + str(tol) + ".png"
plt.savefig(name)


