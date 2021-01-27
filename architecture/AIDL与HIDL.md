### AIDL与HIDL简介

*AIDL*

Android 接口定义语言，是Android服务化架构的关键要素，用来定义Android 基于Binder通信的Client 与Service之间的接口。AIDL引入为开发人员提供了极大的便利，开发人员可以用简单的接口描述语言描述一个服务需要导出的接口，然后使用AIDL工具自动产生对应的java/c++ stub/proxy框架。AIDL语言其实就是一种编程语言，并且Google也为此开发了一个编译器，用于将AIDL语言转化对应的Java/C++语言。

*HIDL*

HIDL的全称是HAL interface definition language（硬件抽象层接口定义语言），在此之前Android 有AIDL，架构在Android binder 之上，用来定义Android 基于Binder通信的Client 与Service之间的接口。HIDL也是类似的作用，只不过定义的是Android Framework与Android HAL实现之间的接口。

[HIDL 简单介绍](https://blog.csdn.net/lei7143/article/details/80931412)

