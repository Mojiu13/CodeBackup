- 1.1Android Studio
Android Studio 是谷歌推出一个Android集成开发工具，基于IntelliJ IDEA. 类似 Eclipse ADT，Android Studio 提供了集成的 Android 开发工具用于开发和调试。

基于Gradle的构建支持
Android 专属的重构和快速修复
提示工具以捕获性能、可用性、版本兼容性等问题
支持ProGuard 和应用签名
基于模板的向导来生成常用的 Android 应用设计和组件
功能强大的布局编辑器，可以让你拖拉 UI 控件并进行效果预览
上面是百度给的百度百科，说白了就是Android开发的新工具Google的亲儿子。具体参看AndroidStudio百度百科

-  1.2Gradle
Gradle是一个基于Apache Ant和Apache Maven概念的项目自动化构建开源工具。它使用一种基于Groovy的特定领域语言(DSL)来声明项目设置，抛弃了基于XML的各种繁琐配置。

- 1.3Gradle插件
其实应该是AndroidStudio Gradle Plugin，也就是AndroidStudio用于开发Android项目的gradle插件。

- 1.4三者的关系
1.Gradle插件会有版本号，每个版本号又对应有一个或一些 Gradle发行版本（一般是限定一个最低版本），也就是我们常见的类似gradle-4.1-all.zip这种东西；如果这两个版本对应不上了，那你的工程构建的时候就会报错。对应关系参看Gradle插件和Gradle版本对应关系。
2.Android Studio 3.0 之后自动将插件版本升级到3.0.0，所以我们也需要对应地把Gradle升级到4.1才行。（后面就是因为这个填坑）
3.Android Gradle Plugin又会跟 Android SDK BuildTool有关联（版本有对应的关系），因为它还承接着AndroidStudio里的编译相关的功能，这也是我们要在项目的 local.properties 文件里写明Android SDK路径、在build.gradle 里注明 buildToolsVersion 的原因。Android Gradle Plugin 本质上就是 一个AS的插件，它一边调用 Gradle本身的代码和批处理工具来构建项目，一边调用Android SDK的编译、打包功能，从而让我们能够顺畅地在AS上进行开发。

二.Gradle插件，Gradle，Android SDK BuildTool（buildToolsVersion）
由于各种坑都填好了，这里就不从头到尾的演示填坑的过程了，而是总结各个要注意的点在升级的时候。

- 2.1弄清Gradle插件和Gradle的配置方法
前面我们介绍了Gradle插件和Gradle不是一个东西，下面我们看看在AndroidStudio中怎么配置。

- 2.1.1Gradle插件的配置
在As工程目录的build.gradle文件中配置（当然也可以在工程目录文件夹下去找到文件配置）如下图：

图中我的插件版本是3.1.3是最新的版本，当然你可以根据自己的需要配置。（配置好后As会自动去下载）

-  2.1.2Gradle配置
Grale配置的意义在于：在项目创建或者编译的时候如何查找Gradle的位置和使用什么版本的Gradle。
配置步骤
1.在gradle-wrapper-propertiies中配置Gradle的版本
2.在本机缓存目录（用户主目录）中存在gradle-4.4-all文件夹或者在As的安装目录中存在。（两个目录下都不一定存在）
解释一下“本机缓存目录”和“As的安装目录”
本机缓存目录（用户主目录下），例如我的是：C:\Users\gongxiaoou.gradle\wrapper\dists
As的安装目录：C:\Program Files\Android\Android Studio\gradle
两个存储位置实例如下图：
本机缓存目录：


As的安装目录：


在gradle-wrapper-propertiies中配置Gradle（主要是版本）
如下图在As的gradle包的gradle-wrapper-propertiies中配置（当然也可以在工程目录文件夹下去找到文件配置）如下图：


Gradle的版本配置相对较复杂一些。先解释一下gradle-wrapper-propertiies中各行的含义和作用：

zipStoreBase和zipStorePath组合在一起，是下载的gradle-4.4-all.zip所存放的位置。
zipStorePath是zipStoreBase指定的目录下的子目录。
distributionBase和distributionPath组合在一起，是解压gradle-4.4-all.zip之后的文件的存放位置。
distributionPath是distributionBase指定的目录下的子目录。
distributionUrl：Gradle下载地址
Gradle查找过程如下：这里涉及配置查找规则
1.Project-level setting中选择Use default gradle wrapper (recommended)，如下图


则先到本机的缓存目录中寻找，找到则使用，找不到则到Gradle下载地址去下载。下载完成会将保存一份到本机的缓存目录。
2.Project-level setting中选择Use local gradle distribution,只是将上面的勾选对象变换一下，这里不粘贴图了。
先到As的安装目录中查找，而不是去1.中本地缓存目录中查找。

如果自己有gradle的压缩包或者去官网下载好gradle的下载地址，而怕在As中下载的过程中出问题或者下载失败，那么我们可以采取如下的方法：
1.Project-level setting中选择Use default gradle wrapper (recommended)，然后将gradle的压缩包（记住是压缩包，不解压）复制到本地缓存目录下的“乱码”文件夹中，例如我的是C:\Users\gongxiaoou.gradle\wrapper\dists\gradle-4.4-all\9br9xq1tocpiv8o6njlyu5op1中，然后clean一下As中工程，此时As会完成压缩包的解压，gradle配置成功。
2.Project-level setting中选择Use local gradle distribution,将gradle压缩包解压，放入As安装包目录下，例如我的是：C:\Program Files\Android\Android Studio\gradle中。
##2.2Android SDK BuildTool（buildToolsVersion）
在升级完gradle的版本之后，可能会由于buildToolsVersion过低造成提示错误的情况出现，这时候你就按照提示下载需要的Android SDK BuildTool版本就可以了。这里的gradle版本和Android SDK BuildTool的版本对应关系和gradle插件与gradle对应关系相似，都是前者确定之后，后者只需要更新到符合要求的最低版本即可，当然也可以是最新的只要匹配就行。
