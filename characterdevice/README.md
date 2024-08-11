# fpt
run make to build .ko file (make sure that BBB have header to build )
sudo su 
insmod sample_led.ko
echo 1 > dev/sample_led to turn on the led 
echo 1 > dev/sample_led to turn off the led