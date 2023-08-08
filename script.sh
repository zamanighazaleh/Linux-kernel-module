gcc mymodule.c -o mymodule
modprobe mymodule
mknod /dev/mynode c 240 1
gcc test.c -o test -lpthread
./test
rm /dev/mynode
modprobe -r mymodule
rmmod mymodule
rm test
