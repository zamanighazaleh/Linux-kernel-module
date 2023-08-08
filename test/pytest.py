import os
path = "/dev/wnode"
fd = os.open(path, os.O_RDONLY)
data = os.read(fd, 700)
print(f'Number of bytes read: {len(data)}')
print(data.decode())
os.close(fd)
