Run make to build .ko file
Load module B into kernel by 2 ways:
- Manual load using insmod:
    sudo insmod helloworld.ko
    sudo insmod helloword2.ko
    dmesg | tail to see change 
-Autoload with modprobe , modprobe will automatically handle dependent modules
run make to build .ko file
sudo mkdir -p /lib/modules/$(uname -r)/extra/
sudo cp helloworld.ko /lib/modules/$(uname -r)/extra/
sudo cp helloworld2.ko /lib/modules/$(uname -r)/extra/
sudo depmod -a
sudo modprobe helloworld

     
