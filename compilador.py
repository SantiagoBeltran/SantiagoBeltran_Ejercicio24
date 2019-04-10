import os
import numpy as np
import matplotlib.pyplot as plt

a = os.system("g++ SantiagoBeltran_Ejercicio24.cpp -o MCMC.x")
a = os.system("./MCMC.x >MCMC.txt")

data = np.loadtxt("MCMC.txt")
x= np.loadtxt("valores_x.txt")
y= np.loadtxt("valores_y.txt")

def g(x,coef):
    result=0.0
    for i in range(len(coef)):
        result+=coef[i]*x**i
    return result

z=np.arange(0,0.85,0.01)

print("El polinomio de grado tres que se ajusta a los datos es: {}+{}x+{}x^2+{}x^3".format(data[0],data[1],data[2],data[3]))

plt.figure()
__=plt.scatter(x,y)
__=plt.plot(z,g(z, data))
plt.xlabel("Valores x")
plt.ylabel("Valores y")
plt.savefig("MetropolisPol3.png")