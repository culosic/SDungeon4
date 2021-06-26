## VSCode局域网调用【手机CAPP】工程模板

### 简述

电脑上使用Microsoft VS Code编写、调试手机CAPP（手机C语言）代码的工程。使用本工程作为模板来开发，可以让vscode显示函数帮助提示等。使用者可按自行需求修改本项目。

### 启动运行步骤

（超简单，由于是局域网运行，需要配置手机的局域网IP。如有疑问，参考[http://i.yzjlb.net/?p=1288](http://i.yzjlb.net/?p=1288)）

* 用vscode打开项目
* 按`ctrl+shift+x`在左栏检查是否安装了`C/C++`扩展，如未安装则要安装一下。
* **【重要】手机电脑连入同一个wifi，更改`run.cmd`的ip为你的手机wifi的IP**（手机wifi的IP在wifi设置里的IP地址栏可以找到，注意不是路由器IP！）
* 电脑vscode中按`ctrl+shift+B`键（或者控制台输入`run`回车），打开手机CAPP局域网版，手机CAPP立即会运行本工程。

### 关于

* 手机CAPP软件、capp_run.exe局域网服务均由【风的影子】提供
* QQ群：
	* 【手机CAPP】影子俱乐部 606757263
	* 【游戏开发】影子俱乐部 496717720
* 2021年6月25日 整理，by 【火烧云】



### （供参考）目录结构说明

* `.vscode` vscode配置相关目录
	* `.vscode\capp.code-snippets` CAPP代码片段模板设置，默认有两个快捷代码片段（**使用者可以自行修改**）
		* 任意c文件中输入`capp`，按回车选中，可以新建模板代码片段
		* 任意c文件中输入`cappg`，按回车选中，可以新建游戏模板代码片段
	* `.vscode\tasks.json` 启动运行手机CAPP的任务
	* `.vscode\settings.json` vscode扩展配置，包括代码格式化等（**使用者可以自行修改**）
* `capp_runner_package` capp工程打包目录，包括：
	* `capp` CAPP函数定义、库声明等
		* `capp\api` CAPP函数定义，主要是为了让代码有提示
		* `capp\libs` CAPP库声明，运行时需要加载这些必要的文件
	* `.gitignore` 定义git忽略文件的类型
	* `Android.mk` CAPP主要的配置文件，定义窗口类型、安卓包名等等
	* `libcapp.so` CAPP库
	* `main.c` 主程序文件（**可在Android.mk文件中修改主程序文件名**）
* `run.cmd` 启动运行手机CAPP的脚本（**在里面更改手机wifi的IP**）
* `README.md` 说明文档
