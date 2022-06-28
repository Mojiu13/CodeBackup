知识：
##### ACL 原理

访问控制列表 (ACL) 是一种基于包过滤的访问控制技术，它可以根据设定的条件**对接口上的数据包进行过滤**，允许其**通过或丢弃**。访问控制列表被广泛地应用于路由器和三层交换机，借助于访问控制列表，可以有效地控制用户对网络的访问，从而最大程度地保障网络安全。

**匹配方法：**  
ACL 会根据数据包中的源 IP 地址、目的 IP 地址、TCP、UDP 端口号，对比每条匹配规则。匹配，则允许包继续传递；不匹配，则丢弃包。

访问控制列表的**功能**：

1.  限制网络流量、提高网络性能；
    
2.  通信流量的控制，例如 ACL 可以限定或简化路由更新信息的长度，从而限制通过路由器某一网段的通信流量；
    
3.  提供网络安全访问的基本手段；
    
4.  在路由器端口处，决定哪种类型的通信流量被转发或被阻塞。例如，用户可以允许 E-mail 通信流量被路由，拒绝所有的 Telnet 通信流量等。
    

**进入：**

1.  当一个数据包进入一个端口，路由器检查这个数据包是否可路由；
    
2.  如果是可以路由的，路由器检查这个端口是否有 ACL 规则在控制进入的数据包；
    
3.  如果有，根据 ACL 中的条件指令，检查这个数据报；
    
4.  如果数据报是被允许的，就查询路由表，决定数据报的目标端口。
    

**发出：**

1.  数据包发出的时候，路由器检查发出端口是否存在 ACL 规则控制流出的数据包；
    
2.  若不存在，这个数据报就直接发送到目标端口；
    
3.  若存在，就再根据 ACL 进行取舍，禁止发出的就将数据包丢弃，允许发出的就正常发出。
    

**过滤基本原则：**

按照访问控制列表进行筛选，从**头到尾逐条匹配**，当遇到规则匹配之后，就直接根据规则对数据包进行处理，不再匹配后面的规则。

在访问控制列表的末尾处，有一条隐藏的 deny 语句，会直接丢弃所有信息。所以如果列表中所有的规则都不匹配，会直接被隐藏的 deny 语句丢弃。

**标准访问控制列表配置命令：**  
列表号从 1 到 99 属于标准访问列表规则，根据数据包的源 IP 地址，来选择允许或拒绝通过的数据包。

**标准访问控制列表**在一般情况下，一条完整的规则应该包含两个部分，分别是允许通过的和禁止通过的，这样规则才完整，否则规则的配置就有漏洞，无法达到效果。

**配置命令：**`access-list 列表号 permit或deny IP地址 反掩码`，在命令最前方加 no 可以删除该规则，也可以使用`no access-list 列表号`指定删除某条规则。

在配置规则时，通过使用 **permit** 来允许数据通过，通过 **deny** 来拒绝数据通过，通过这两个选项的配合，完成对数据发送与接收的控制，从而达到网络安全的目的。

使用配置命令可以创建新的规则，允许或拒绝指定的 IP 地址的数据的传输。配置完毕，需要将规则应用在指定的地方才能生效。

**反掩码**是用于路由器使用的通配符掩码与源或目标地址一起来分辨匹配的地址范围，在配置的时候有两种特殊的反掩码，分别是 255.255.255.255 ( 等价于 any )和 0.0.0.0 ( 等价于 host )。

any 可以代替 0.0.0.0 255.255.255.255 ，例如：

1.  `R1(config)#access-list 1 permit 0.0.0.0 255.255.255.255`  
2.  `R1(config)#access-list 1 permit any`  
3.  `//这两个命令是同一个意思，都是允许所有包通过`  

host 表示检查 IP 地址的每一位，即指定到一个确定的 IP 地址，而不是一个网段，例如：

1.  `R1(config)#access-list 1 permit 192.168.1.1 0.0.0.0`  
2.  `R1(config)#access-list 1 permit host 192.168.1.1`  
3.  `//这两个命令都是只允许 192.168.1.1 访问`  

**应用规则：**  
命令为：

1.  `ip access-group 列表号 in 或 out`  

必须将规则应用在指定的地方，并指明是 in 进入还是 out 发出，否则规则无法生效。

在接口应用规则，例：

1.  `R1(config)#int f0/0`  
2.  `R1(config-if)#ip access-group 1 in`  
3.  `//将规则 1 应用在接口 f0/0 的进入方向`  

在远程访问线路上应用访问控制策略，例：

1.  `R1(config)#access-list 1 permit host 192.168.1.1`     
2.  `//定义 ACL 访问列表 1 ，只允许指定主机访问`  
3.  `R1(config)#access-list 1 deny any`  
4.  `//禁止其他所有设备访问`  
5.  `R1(config-if)#line vty 0 4`                  
6.  `//设置同时允许 0~4 五个用户访问`  
7.  `R1(config-line)#access-class 1 in`          
8.  `//在 vty 线路上应用 ACL 1 号访问列表，配置时被访问的设备只需要将规则应用在进方向即可`  
9.  `R1(config-line)#password gns3`        
10.  `//设置密码为 gns3`  
11.  `R1(config-line)#login`  
12.  `//启用登录`  

**警告：** 由于访问控制规则是逐条匹配，如果是先配置禁止所有设备访问，那么后面的所有规则都无法生效了，只有删除该规则之后，其他规则才会生效。

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

