知识：
##### 扩展 ACL

标准访问控制列表只能过滤源地址，无法针对某个协议，所以在有些时候无法达到目的，于是就出现了扩展访问列表控制。

扩展访问控制列表是根据源地址、目的地址、端口号进行过滤的，而且扩展 ACL 可以针对特定的协议。

标准访问列表控制的列表号范围是 1~99 ，扩展访问控制列表的列表号范围是 100~199 。

标准访问控制列表与扩展访问控制列表都有一条隐藏的 deny 规则，如果配置了 permit ，有时候不配置 deny ，规则也可以正常使用。但是如果配置的是 deny ，没有配置 permit 的话，所有的规则都会被丢弃。

扩展 ACL 配置方法：

1.  `access-list 列表号 deny 或 permit 条件`  

注意事项：

-   扩展访问控制列表的**列表号的范围**是 100~199 ；
-   选择使用 deny 拒绝或 permit 允许通过；
-   条件包括**协议种类、源地址、目的地址、运算符、端口号**。

其中运算符和端口号是用于匹配 TCP、UDP 数据包中的端口号，可以指定端口号，也可以直接指定具体的协议。根据需要，也可以配置**指定某个网段**，配置整个网段所有的设备的访问控制，也可以**单独指定某一个主机**的访问控制，需要根据不同的环境是具体选择。

下表为常见的协议所使用的端口号以及该协议使用的传输方式：

端口号

协议名称

TCP/UDP

20/21

FTP (文件传输协议)

TCP

23

Telnet (终端连接)

TCP

25

SMTP (简单邮件传输协议)

TCP

42

NAMESERVER (主机名字服务器)

UDP

53

DOMAIN (域名服务器（DNS）)

TCP/UDP

69

TFTP (普通文件传输协议（TFTP）)

UDP

80

WWW (万维网)

TCP

上表是一些常用的协议以及这些协议所使用的端口号、传输方式，但是还有一个常用的 ping 命令没有被放进去，因为 ping 命令使用的 ICMP 协议，这个协议将数据包含在 IP 中，没有特定的端口，所以配置的方式也与其他协议的配置方式不同，具体的配置方式为：

1.  `access-list 列表号 permit或deny icmp 源地址 源地址反掩码 目的地址 目的地址反掩码`  

通过端口实现扩展访问控制列表配置**示例**： R1

1.  `R1(config)#access-list 100 permit tcp 192.168.1.0 0.0.0.255 192.168.2.0 0.0.0.255 eq 23`  
2.  `//允许来自 192.168.1.0 网段传输方式为 tcp 的数据通过 23 号端口进入 192.168.2.0 网段`  
3.  `R1(config)#access-list 100 deny ip any any`  
4.  `//拒绝其他所有流量`  
5.  `R1(config)#int f0/0`  
6.  `R1(config-if)#ip access-group 100 in`  
7.  `//将规则应用在端口的进方向`  

通过协议实现扩展访问控制列表配置**示例**： R1

1.  `R1(config)#access-list 100 permit tcp host 192.168.23.2 host 192.168.23.3 eq telnet`       
2.  `//允许 R2 访问 R3 的 telnet 服务`  
3.  `R1(config)#int f0/0`      
4.  `//进入路由器的 f0/0 接口`  
5.  `R1(config-if)#ip access-group 100 in`        
6.  `//将规则应用在入方向`


router rip
version 2
no auto-summary
network 192.168.23.0
network 192.168.12.0















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