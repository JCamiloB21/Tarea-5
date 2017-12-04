import numpy as np
import matplotlib.pyplot as plt

data=np.genfromtxt("RadialVelocities.dat",delimiter=" ", skip_header=1)
x=data[:,0]
y=data[:,1]
vel=[]
bb=0.2497
bd=5.16
ad=9.3105
ah=64.3
mb=
md=
mh=
for i in range(len(y)):
    velocity=(((mb)**(1/2)*y[i])/(y[i]**2 + bb**2)**(3/4)) + (((md)**(1/2)*y[i])/(y[i]**2 + (bd+ad)**2)**(3/4)) + (((mh)**(1/2))/(y[i]**2+ah**2)**(1/4))
    vel.append(velocity)
    

plt.figure()
plt.scatter(x,y)
plt.plot(x,vel)
plt.show()
plt.savefig("montecarlo.png")