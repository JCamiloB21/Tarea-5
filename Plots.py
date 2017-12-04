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
mb=1000
md=28000
mh=50
for i in range(len(x)):
    a=(mb**(0.5))*x[i]
    d=(x[i]**2 + bb**2)**(0.75)
    e=a/d
    b=((md**(0.5)*x[i]))/(x[i]**2 + (bd+ad)**2)**(0.75)
    c= mh**(0.5)/(x[i]**2+(ah**2))**(0.25)
    velocity= e + b + c
    vel.append(velocity)
    print e

plt.figure()
plt.plot(x,y)
plt.plot(x,vel,c="black")
plt.savefig("montecarlo.png")