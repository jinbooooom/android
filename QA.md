## JDK版本切换

```shell
sudo update-alternatives --config javac
有 2 个候选项可用于替换 javac (提供 /usr/bin/javac)。

  选择       路径                                        优先级  状态
------------------------------------------------------------
* 0            /usr/lib/jvm/java-11-openjdk-amd64/bin/javac   1111      自动模式
  1            /usr/lib/jvm/java-11-openjdk-amd64/bin/javac   1111      手动模式
  2            /usr/lib/jvm/java-8-openjdk-amd64/bin/javac    1081      手动模式

#
#要维持当前值[*]请按<回车键>，或者键入选择的编号：2
#update-alternatives: 使用 /usr/lib/jvm/java-8-openjdk-amd64/bin/javac 来在手动模式中提供 /usr/bin/javac (javac)
```

查看：

```shell
sudo update-alternatives --display java
```

## 删除不需要的JDK

```shell
# 查看apt安装的包，并选出包含 jdk 的包
dpkg -l | grep jdk
# 卸载 jdk11
sudo apt-get remove openjdk-11-jdk*
```

[如何在Ubuntu中用apt命令删除/卸载软件包（remove/clean/purge）](https://blog.csdn.net/LEON1741/article/details/85114318)

