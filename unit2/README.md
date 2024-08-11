.Load module B into kernel by 2 ways:
- Manual load using insmod:
    run make to build .ko file
    sudo insmod helloworld.ko
    sudo insmod helloword2.ko
    sudo rmmod .ko file to remove
    dmesg | tail to see change 
-Autoload with modprobe , modprobe will automatically handle dependent modules.# fpt
     
