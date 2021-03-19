package com.study.jnilearn;

public class JniFuncMain {
    private static int staticIntField = 300;
    //public static int staticIntField = 300;

    // 加载本地库
    static {
        System.loadLibrary("jnifunc");
        //System.load("/home/user/gitme/android/JNI/NativeCallJava/jni/libjnifunc.so");
    }

    public static native JniTest createJniObject();

    public static void main(String[] args) {
        System.out.println("[Java:main]: call createJniObject()");
        JniTest jniObj = createJniObject();

        // 调用 JniTest 对象的方法
        jniObj.callTest();
    }
}

class JniTest
{
    private int intField;
    //public int intField;

    public JniTest(int num)
    {
        intField = num;
        System.out.println("[Java:JniTest]: JniTest的构造函数中 intField = " + intField);
    }

    public int callByNative(int num)
    {
        System.out.println("[Java:callByNative]: 输入形参 num = " + num);
        return num;
    }

    public void callTest()
    {
        System.out.println("[Java:callTest]: 字段 intField = " + intField);
    }
}

