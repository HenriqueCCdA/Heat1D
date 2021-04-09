import matplotlib.pyplot as plt
import sys


with open('plot.in','r') as f:
    data = f.read()

lines = data.splitlines()

nameFile = lines[0]

step     = lines[1:-1]

print(nameFile,step)


with open(nameFile,'r') as f:
    data = f.read()
        
lines = data.splitlines()

x = lines[0].split()[2:]
x = [float(i) for i in x]

# valores min e max para um float
temp_min = sys.float_info[0]
temp_max = sys.float_info[3]

for i in step:
    tmp  = lines[int(i)+1].split()
    t    = tmp[1]
    temp = [float(i) for i in tmp[2:]]
    plt.plot(x,temp,label='t(s) = ' + t) 
    
    # pegando o valor max e mim de temperatura
    temp_max = max(max(temp),temp_max)
    temp_min = min(min(temp),temp_min)

plt.xlim(min(x) - 1, max(x) + 1)
plt.ylim(temp_min-1, temp_max+1)

plt.xlabel('time (s)')
plt.ylabel('Temperatua(°C)')

plt.legend()
plt.show()
