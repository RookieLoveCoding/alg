设计文档类输出可以放到该目录，本项目中使用开源工具Doxygen来生成文档
- 生成文档
    本目录中的Doxyfile是配置好的文件，可以根据自身需要自行修改，无需再通过doxygen -g生成默认的Doxyfile。
    直接执行sh genfile.sh脚本，如果没有安装doxygen的话，会自动安装。安装完成后自动生成项目文档，当前默认只生成html，且文档输出路径为当前目录（doc/）。文档生成之后在doc/html/文件夹中会产生很多文件，其中入口为index.html。此时我们可以有两种方式打开文档：
    1.把整个html/目录download下来，在win系统上直接双击index.html打开
    2.在vscode中安装插件Live Server，右键index.html，选择Open with Live Server，在右下角弹窗点击Open in Browser，就可以直接在win的浏览器上打开了，推荐本方式。