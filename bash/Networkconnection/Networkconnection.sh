echo 1111 | sudo -S route add default gw 192.168.100.1
echo 1111 | sudo -S route add -net 10.0.0.0 netmask 255.0.0.0 gw 10.110.217.254
