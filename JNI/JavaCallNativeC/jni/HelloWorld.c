// HelloWorld.c

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
	c_str = (*env)->GetStringUTFChars(env, j_str, NULL);
	if (c_str == NULL)
	{
		printf("out of memory.\n");
		return NULL;
	}

	sprintf(buff, "[native]:%s\n", c_str);
    (*env)->ReleaseStringUTFChars(env, j_str, c_str);
	return (*env)->NewStringUTF(env, buff);
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
	jint *arr = (*env)->GetIntArrayElements(env, jarr, NULL);
	jint size = (*env)->GetArrayLength(env, jarr);

	int res = 0;
	printf("[native] size = %d\n", size);
	for (int i = 0; i < size; ++i)
	{
		res += *(arr + i);
	}
	return res;
}

#ifdef __cplusplus
}
#endif
