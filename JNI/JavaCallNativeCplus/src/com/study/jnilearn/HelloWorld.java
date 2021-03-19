package com.study.jnilearn;
 
public class HelloWorld {
	
	public static native String sayHello(String name); 	// 声明，这是一个native静态函数，由本地代码实现
	public static native int add(int x, int y);	// 静态求和函数
	public native int addArray(int[] arr); // 非静态数组求和函数
	public native int getBooksValue(Books books, int num);  // 类作为形参的测试

	public static void main(String[] args) {
		// 在编译时通过命令 java -Djava.library.path=./jni，设置动态库目录为当前目录下的 jni 文件夹
		System.out.println("JVM查找的动态库目录如下：");
		String libraryDirs = System.getProperty("java.library.path");
		System.out.println(libraryDirs);
		System.out.println("\n");

		// 调用本地函数
		System.out.println("[Java:main]:测试静态方法与字符串");
		String text = sayHello("Hello World");
		System.out.println(text);

		System.out.println("[Java:main]:测试静态方法与整型");
		int res = add(1, 2);
		System.out.println("[Java:main]:call add()\n" + res);

		System.out.println("[Java:main]:测试非静态方法数组作为形参");
		HelloWorld hello = new HelloWorld();
		int[] arr = {1, 2, 3, 4, 5};
		res = hello.addArray(arr);
		System.out.println("[Java:main]:call addArray()\n" + res);

		System.out.println("[Java:main]:测试非静态方法实类作为形参");
		Books myBook = new Books(20);
		int myNumber = 5;
		int JavaTotalPrice = myBook.getTotalValue(myNumber);
		System.out.println("[Java:main]:totalPrice = " + JavaTotalPrice);
		int NativeTotalPrice = hello.getBooksValue(myBook, myNumber);
		System.out.println("[Java:main]:after call native method:totalPrice = " + NativeTotalPrice);
		System.out.println("\n");
	}

	static {
		System.loadLibrary("HelloWorld");	// 加载实现了native函数的动态库，只需要写动态库的名字
		//System.load("/home/user/gitme/android/JNI/JavaCallNativeCplus/jni/libHelloWorld.so");
	}
}

class Books
{
	public int mPrice = 10;

	public Books(int price)
	{
		System.out.println("[Java:Books]: Books的构造函数中 mPrice = " + price);
		this.mPrice = price;
	}

	public int getTotalValue(int number)
	{
		int res = number * this.mPrice;
		System.out.println("[Java:Books:getTotalValue]: " + res);
		return res;
	}
}


