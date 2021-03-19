#include <iostream>
#include "com_study_jnilearn_JniFuncMain.h"

using namespace std;

/*
 * Class:     com_study_jnilearn_JniFuncMain
 * Method:    createJniObject
 * Signature: ()Lcom/study/jnilearn/JniTest;
 */
JNIEXPORT jobject JNICALL Java_com_study_jnilearn_JniFuncMain_createJniObject
(JNIEnv *env, jclass clazz)
{
    jclass targetClass;
    jmethodID mid;
    jobject newObject;
    jstring helloStr;
    jfieldID fid;
    jint staticIntField;
    jint result;

    // 获取 JniFuncMain.staticIntField 值。获取 Java 的成员变量前必须先获取该变量的字段 ID，再根据 ID 拿值
    // 成员变量 ID 保存在 jfieldID 类型的变量中
    fid = env->GetStaticFieldID(clazz, "staticIntField", "I"); // 获取静态 jfieldID
    staticIntField = env->GetStaticIntField(clazz, fid);
    printf("[native]: 获取 JniFuncMain 类的静态字段值 JniFuncMain.staticIntField = %d\n", staticIntField);

    // 查找生成对象的类
    targetClass = env->FindClass("com/study/jnilearn/JniTest");

    // 查找构造函数（访问 Java 方法之前得先获取方法的 ID，方法 ID 保存在 jmethodID 变量中）
    // 获取指定类的指定方法。构造函数称为 <init>，其它方法就是原名
    mid = env->GetMethodID(targetClass, "<init>", "(I)V"); 

    // 生成 JniTest 对象，返回其引用
    printf("[native]: 生成对象 JniTest\n");
    newObject = env->NewObject(targetClass, mid, 100); // 传入构造函数的方法 ID

    // 调用对象的方法
    mid = env->GetMethodID(targetClass, "callByNative", "(I)I");
    result = env->CallIntMethod(newObject, mid, 200);

    // 设置 JniObject 对象的 intField 值
    fid = env->GetFieldID(targetClass, "intField", "I");
    printf("[native]: 设置 JniTest.intField = %d\n", 200);
    env->SetIntField(newObject, fid, result);
    
    // 返回对象的引用
    return newObject; 
}