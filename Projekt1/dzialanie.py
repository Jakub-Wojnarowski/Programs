import matplotlib.pyplot as plt
import numpy as np

#przed uruchomieniem tego skryptu trzeba przeprowadzić obliczenia dla wszystkich metod

f = open("a_1.txt", "r")
a_1 = np.fromfile(f, count = 500, dtype = np.float64, sep = " ")
f.close()

f = open("a_2.txt", "r")
a_2 = np.fromfile(f, count = 500, dtype = np.float64, sep = " ")
f.close()

f = open("a_3.txt", "r")
a_3 = np.fromfile(f, count = 500, dtype = np.float64, sep = " ")
f.close()

f = open("a_4.txt", "r")
a_4 = np.fromfile(f, count = 500, dtype = np.float64, sep = " ")
f.close()

plt.figure
plt.plot(a_1, 'r', label='relaksacja')
plt.plot(a_2, 'b', label='nadrelaksacja 1.9')
plt.plot(a_3, 'g', label='relaksacja 1.1')
plt.plot(a_4, 'k', label='min. działania')
plt.xlabel("ilość iteracji")
plt.ylabel("a")
plt.legend()
plt.savefig('dzialanie_wykres.png')
plt.show()

