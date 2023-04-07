import matplotlib.pyplot as plt
import numpy as np

#wczytywanie trybu
f = open("tryb.txt")
tryb = int(np.fromfile(f, count = 1, dtype = np.int32, sep = " "))
f.close()

#pobieranie danych
f = open("u_100.txt", "r")
u_100 = np.empty((63,63))
for i in range(63):
    u_100[i] = np.fromfile(f, count = 63, dtype = np.float64, sep = " ")  
f.close()

f = open("u_500.txt", "r")
u_500 = np.empty((63,63))
for i in range(63):
    u_500[i] = np.fromfile(f, count = 63, dtype = np.float64, sep = " ")  
f.close()

f = open("RO_100.txt", "r")
r_100 = np.empty((63,63))
for i in range(63):
    r_100[i] = np.fromfile(f, count = 63, dtype = np.float64, sep = " ") 
f.close()

f = open("RO_500.txt", "r")
r_500 = np.empty((63,63))
for i in range(63):
    r_500[i] = np.fromfile(f, count = 63, dtype = np.float64, sep = " ") 
f.close()

f = open("delta_100.txt", "r")
d_100 = np.empty((63,63))
for i in range(63):
    d_100[i] = np.fromfile(f, count = 63, dtype = np.float64, sep = " ") 
f.close()

f = open("delta_500.txt", "r")
d_500 = np.empty((63,63))
for i in range(63):
    d_500[i] = np.fromfile(f, count = 63, dtype = np.float64, sep = " ") 
f.close()

if tryb == 1:
    f = open("a_1.txt", "r")
    a = np.fromfile(f, count = 500, dtype = np.float64, sep = " ")
    f.close()
elif tryb == 2:
    f = open("a_2.txt", "r")
    a = np.fromfile(f, count = 500, dtype = np.float64, sep = " ")
    f.close()
elif tryb == 3:
    f = open("a_3.txt", "r")
    a = np.fromfile(f, count = 500, dtype = np.float64, sep = " ")
    f.close()
elif tryb == 4:
    f = open("a_4.txt", "r")
    a = np.fromfile(f, count = 500, dtype = np.float64, sep = " ")
    f.close()

#współrzędne
x = np.empty((63,63))
y = np.empty((63,63))
for i in range (63):
    x[i] = np.linspace(-31, 31, 63)
    y[i] = np.linspace(i - 31, i - 31, 63)

#wykresy
fig, ax = plt.subplots(figsize = (9,16),nrows = 4, ncols = 2)

rect = plt.Rectangle(
    # (lower-left corner), width, height
    (0.00, 0.00), 1, 1, fill=False, color="black", lw=4, 
    zorder=0, transform=fig.transFigure, figure=fig
)
fig.patches.extend([rect])

ax1 = plt.subplot(4,2,1)
ax1.set_title('u po 100 iteracjach')
plt.pcolormesh(x, y, u_100, shading = 'gouraud', cmap = 'hot')
plt.locator_params(axis='x', nbins=7)
plt.locator_params(axis='y', nbins=7)
plt.colorbar()

ax1 = plt.subplot(4,2,2)
ax1.set_title('u po 500 iteracjach')
plt.pcolormesh(x, y, u_500, shading = 'gouraud', cmap = 'hot')
plt.locator_params(axis='x', nbins=7)
plt.locator_params(axis='y', nbins=7)
plt.colorbar()

ax1 = plt.subplot(4,2,3)
ax1.set_title('RO po 100 iteracjach')
plt.pcolormesh(x, y, r_100, shading = 'gouraud', cmap = 'hot', vmin = -1, vmax = 1)
plt.locator_params(axis='x', nbins=7)
plt.locator_params(axis='y', nbins=7)
plt.colorbar()

ax1 = plt.subplot(4,2,4)
ax1.set_title('RO po 500 iteracjach')
plt.pcolormesh(x, y, r_500, shading = 'gouraud', cmap = 'hot', vmin = -1, vmax = 1)
plt.locator_params(axis='x', nbins=7)
plt.locator_params(axis='y', nbins=7)
plt.colorbar()

ax1 = plt.subplot(4,2,5)
ax1.set_title('delta_RO po 100 iteracjach')
plt.pcolormesh(x, y, d_100, shading = 'gouraud', cmap = 'hot')
plt.locator_params(axis='x', nbins=7)
plt.locator_params(axis='y', nbins=7)
plt.colorbar()

ax1 = plt.subplot(4,2,6)
ax1.set_title('delta_RO po 500 iteracjach')
plt.pcolormesh(x, y, d_500, shading = 'gouraud', cmap = 'hot')
plt.locator_params(axis='x', nbins=7)
plt.locator_params(axis='y', nbins=7)
plt.colorbar()

ax1 = plt.subplot(4,1,4)
#ax1.set_title('a w zależnoci od ilosci iteracji')
ax1.set_xlabel("ilość iteracji")
ax1.set_ylabel("a")
plt.plot(a)

if tryb == 1:
    plt.savefig('metoda_relaksacji.png')
elif tryb == 2:
    plt.savefig('metoda_nadrelaksacji(1.9).png')
elif tryb == 3:
    plt.savefig('metoda_nadrelaksacji(1.1).png')
elif tryb == 4:
    plt.savefig('minimalizacja_dzialania.png')

