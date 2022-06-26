R1(config)#int f0/0  
R1(config-if)#ip add 10.1.1.1 255.255.255.0  
R1(config-if)#no shut  
R1(config-if)#int f0/1  
R1(config-if)#ip add 20.1.1.1 255.255.255.0  
R1(config-if)#no shut  
R1(config-if)#int f1/0  
R1(config-if)#ip add 192.168.12.1 255.255.255.0  
R1(config-if)#no shut  
R1(config-if)#exit  
R1(config)#router rip  
R1(config-route)#version 2  
R1(config-route)#no auto-summary  
R1(config-route)#network 10.1.1.0  
R1(config-route)#network 20.1.1.0  
R1(config-route)#network 192.168.12.0  


R2(config)#int f0/0  
R2(config-if)#ip add 192.168.12.2 255.255.255.0  
R2(config-if)#no shut  
R2(config-if)#int f0/1  
R2(config-if)#ip add 172.16.1.1 255.255.255.0  
R2(config-if)#no shut  
R2(config-if)#exit  
R2(config)#router rip  
R2(config-route)#version 2  
R2(config-route)#no auto-summary  
R2(config-route)#network 172.16.0.0  
R2(config-route)#network 192.168.12.0  
R2(config-route)#exit  
R2(config)#access-list 1 deny 20.1.1.0 0.0.0.255  
R2(config)#access-list 1 permit any  
R2(config)#int f0/1  
R2(config-if)#ip access-group 1 out  
R2(config-if)#exit  
R2(config)#access-list 2 permit host 192.168.12.1  
R2(config)#access-list 2 deny any  
R2(config)#line vty 0 4  
R2(config-line)#access-class 2 in   
R2(config-line)#password gns3  
R2(config-line)#login


ip 10.1.1.10 255.255.255.0 gateway 10.1.1.1  
ip 20.1.1.10 255.255.255.0 gateway 20.1.1.1  
ip 172.16.1.10 255.255.255.0 gateway 172.16.1.1  

