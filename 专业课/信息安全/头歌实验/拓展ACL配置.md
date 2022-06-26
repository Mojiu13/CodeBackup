hostname R1
interface FastEthernet0/0
ip address 10.1.1.1 255.255.255.0
interface FastEthernet0/1
ip address 20.1.1.1 255.255.255.0
interface FastEthernet1/0
ip address 192.168.12.1 255.255.255.0
router rip
version 2
network 10.0.0.0
network 20.0.0.0
network 192.168.12.0
no auto-summary


hostname R2
interface FastEthernet0/0
ip address 192.168.12.2 255.255.255.0
interface FastEthernet0/1
ip address 192.168.23.2 255.255.255.0
router rip
version 2
network 192.168.12.0
network 192.168.23.0
no auto-summary



hostname R3
R3(config)#router rip  
R3(config-router)#version 2  
R3(config-router)#no auto-summary  
R3(config-router)#network 192.168.23.0  
R3(config-router)#exit  
R3(config)#line vty 0 4  
R3(config-line)#password 123  
R3(config-line)#exit  
R3(config)#access-list 111 permit tcp host 192.168.23.2 host 192.168.23.3 eq telnet       
R3(config)#access-list 112 deny icmp host 10.1.1.10 host 192.168.23.3       
R3(config)#access-list 112 permit icmp any host 192.168.23.3  
R3(config)#int f0/0    
R3(config-if)#ip access-group 111 in  
R3(config-if)#ip access-group 112 in  