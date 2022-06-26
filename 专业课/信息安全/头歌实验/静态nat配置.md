PC1控制台: 
PC1>ip 192.168.1.10 255.255.255.0 gateway 192.168.1.1  
PC1>save  
PC2  

PC2控制台:
PC2>ip 192.168.1.20 255.255.255.0 gateway 192.168.1.1  
PC2>save


R1控制台 :
int f0/0  
ip add 192.168.1.1 255.255.255.0
no shut  
int s1/0  
ip add 100.99.12.1 255.255.255.0
no shut  
exit  
ip nat inside source static 192.168.1.10 100.99.12.10
ip nat inside source static 192.168.1.20 100.99.12.20
int f0/0  
ip nat inside   
int s0/1  
ip nat outside


R2控制台:
int s1/0  
p add 100.99.12.2 255.255.255.0 
no shut  
exit  