// HelloWorld.cpp

#include "com_study_jnilearn_HelloWorld.h"
 
#ifdef __cplusplus
extern "C"
{
#endif
 
/*
 * Class:     com_study_jnilearn_HelloWorld
 * Method:    sayHello
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_study_jnilearn_HelloWorld_sayHello(
	JNIEnv *env, jclass cls, jstring j_str)
{
	printf("[native]: call sayhello()\n");
	const char *c_str = NULL;
	char buff[128] = { 0 };
	// Java 默认使用Unicode编码，而C/C++使用UTF编码
	c_str = env->GetStringUTFChars(j_str, NULL);
	if (c_str == NULL)
	{
		printf("out of memory.\n");
		return NULL;
	}

	sprintf(buff, "[native]:%s\n", c_str);
    env->ReleaseStringUTFChars(j_str, c_str);
	return env->NewStringUTF(buff);
}

/*
 * Class:     com_study_jnilearn_HelloWorld
 * Method:    add
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_study_jnilearn_HelloWorld_add
  (JNIEnv *env, jclass cls, jint x, jint y)
{
	printf("[native]: call add()\n");
	int res = x + y;
	return res;
}

/*
 * Class:     com_study_jnilearn_HelloWorld
 * Method:    addArray
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_com_study_jnilearn_HelloWorld_addArray
  (JNIEnv *env, jobject cls, jintArray jarr) 
// 注意本地方法 add() 和 addArray() 的形参 jclass cls 与 jobject cls
// 因为 add() 和 addArray() 在 Java 中分别是静态方法和非静态方法
{
	printf("[native]: call addArray()\n");
	// C风格
	jint *arr = env->GetIntArrayElements(jarr, NULL);
	jint size = env->GetArrayLength(jarr);

	int res = 0;
	printf("[native] size = %d\n", size);
	for (int i = 0; i < size; ++i)
	{
		res += *(arr + i);
	}
	return res;
}

/*
 * Class:     com_study_jnilearn_HelloWorld
 * Method:    getBooksValue
 * Signature: (Lcom/study/jnilearn/Books;I)I
 */
JNIEXPORT jint JNICALL Java_com_study_jnilearn_HelloWorld_getBooksValue
  (JNIEnv *env, jobject cls, jobject book, jint num)
{
    // 查找生成对象的类
    jclass books = env->GetObjectClass(book);
	// 注意 GetFieldID 的第一个参数是 jclass 类型
	jfieldID priceID = env->GetFieldID(books, "mPrice", "I");
	// 注意 GetIntField 里的第一个参数应是 jobject 而不是 jclass，即:
	// 用 GetFieldId 从 jclass(books) 中获得成员变量的字段 ID，
	// 再从 jobject(book) 中获得实例化的对象 book 中的成员变量值。
	jint price = env->GetIntField(book, priceID);  
	jint res = price * num;
	printf("[native]: call getBooksValue(), total price = %d * %d = %d\n", price, num, res);
	return res;
}


#ifdef __cplusplus
}
#endif
