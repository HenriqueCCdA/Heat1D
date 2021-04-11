import matplotlib.pyplot as plt
import sys
from matplotlib.animation import FuncAnimation

def init():
    return line, annotation


def animate(i):
    tmp  = lines[i].split()
    t    = tmp[1]
    annotation.set_text(f"t = {t} s")
    temp = [float(j) for j in tmp[2:]]  
    line.set_data(x, temp)
    
    return line, annotation
 

nameFile = "../../Python/prob_node.python"

with open(nameFile,'r') as f:
    data = f.read()
        
lines = data.splitlines()

x = lines[0].split()[2:]
x = [float(i) for i in x]

# valores min e max para um float
temp_min = sys.float_info[0]
temp_max = sys.float_info[3]

x_max = max(x)
x_min = min(x)

time_steps = len(lines) - 1

for i in range(1,time_steps - 1):
    tmp  = lines[i].split()
    temp = [float(j) for j in tmp[2:]]    
    # pegando o valor max e mim de temperatura
    temp_max = max(max(temp),temp_max)
    temp_min = min(min(temp),temp_min)
        
    
    
fig = plt.figure()
ax = plt.axes(xlim=(x_min, x_max), ylim = (temp_min - 10, temp_max + 10))
annotation = ax.annotate('t = 0.0 s', xy=(25, 200), xycoords="axes points")
ax.hlines(temp_min, 0, 50, color = 'gray', ls='--')
ax.hlines(temp_max, 0, 50, color = 'gray', ls='--')
annotation.set_animated(True)

line, = ax.plot([], [])
plt.title('Temperatura ao longo da barra')
plt.xlabel('x (m)')
plt.ylabel('Temperatua(°C)') 
   


anim = FuncAnimation(fig, animate, frames = None, init_func=init, interval = 1, save_count=time_steps)
#anim = FuncAnimation(fig, animate, frames = None, init_func=init, interval = 10, save_count=200)
 

anim.save('movie.gif')
 

