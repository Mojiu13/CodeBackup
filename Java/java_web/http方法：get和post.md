## 两种 HTTP 请求方法：GET 和 POST

在客户机和服务器之间进行请求-响应时，两种最常被用到的方法是：GET 和 POST。

-   **GET** - 从指定的资源请求数据。
-   **POST** - 向指定的资源提交要被处理的数据。


## GET 方法

**请注意，查询字符串（名称/值对）是在 GET 请求的 URL 中发送的：**

``/test/demo_form.php**?name1=value1&name2=value2**``

**有关 GET 请求的其他一些注释：**

-   GET 请求可被缓存
-   GET 请求保留在浏览器历史记录中
-   GET 请求可被收藏为书签
-   GET 请求不应在处理敏感数据时使用
-   GET 请求有长度限制
-   GET 请求只应当用于取回数据


![[Pasted image 20210902113230.png]]


### 其他一些 HTTP 请求方法：

**HEAD**:与 GET 相同，但只返回 HTTP 报头，不返回文档主体。

**PUT**:上传指定的 URI 表示。

**DELETE**:删除指定资源。

**OPTIONS**:返回服务器支持的 HTTP 方法。

**CONNECT**:把请求连接转换到透明的 TCP/IP 通道。