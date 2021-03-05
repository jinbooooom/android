package com.study.jnilearn;
 
public class HelloWorld {
	
	public static native String sayHello(String name); 	// 声明，这是一个native静态函数，由本地代码实现
	public static native int add(int x, int y);	// 静态求和函数
	public native int addArray(int[] arr); // 非静态数组求和函数

 
	public static void main(String[] args) {
		System.out.println("JVM查找的动态库目录如下：");
		String libraryDirs = System.getProperty("java.library.path");
		System.out.println(libraryDirs);

		// 调用本地函数
		String text = sayHello("Hello World");
		System.out.println(text);

		int res = add(1, 2);
		System.out.println("[Java]:call add()\n" + res);

		// 测试非静态方法与类
		HelloWorld hello = new HelloWorld();
		int[] arr = {1, 2, 3, 4, 5};
		res = hello.addArray(arr);
		System.out.println("[Java]:call addArray()\n" + res);


		System.out.println("\n");
	}

	static {
		//System.loadLibrary("HelloWorld");	// 加载实现了native函数的动态库，只需要写动态库的名字
		System.load("/home/user/gitme/android/JNI/JavaCallNativeCplus/jni/libHelloWorld.so");
	}
}
