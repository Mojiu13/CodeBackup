- # 地址：C:\local\vcpkg
- 2024/1/17
	- 设置代理：PS C:\local\vcpkg> git config --global http.proxy 127.0.0.1:10888
				PS C:\local\vcpkg> git config --global https.proxy 127.0.0.1:10888
				PS C:\local\vcpkg> git config --global http.proxy socks5 127.0.0.1:10888
				PS C:\local\vcpkg> git config --global https.proxy socks5 127.0.0.1:10888
				PS C:\local\vcpkg> git config --global http.proxy 'socks5://127.0.0.1:10888'
				PS C:\local\vcpkg> git config --global https.proxy 'socks5://127.0.0.1:10888'
