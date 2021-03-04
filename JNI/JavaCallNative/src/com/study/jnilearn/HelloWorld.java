package com.study.jnilearn;
 
public class HelloWorld {
	
	public static native String sayHello(String name); 	// 1.声明这是一个native函数，由本地代码实现
 
	public static void main(String[] args) {
		String text = sayHello("yangxin");	// 3.调用本地函数
		System.out.println(text);
	}
	
	static {
		//System.loadLibrary("HelloWorld");	// 2.加载实现了native函数的动态库，只需要写动态库的名字
		System.load("/home/user/gitme/android/NDK/JNI/JavaCallNative/0304a/jni/libHelloWorld.so");
	}
 
}
