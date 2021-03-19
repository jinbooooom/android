javac src/com/study/jnilearn/JniFuncMain.java -d ./bin
javah -jni -classpath ./bin -d ./jni com.study.jnilearn.JniFuncMain
g++ -Ijni -fPIC -shared jni/jnifunc.cpp -std=c++11 -o jni/libjnifunc.so
# java -classpath ./bin com.study.jnilearn.JniFuncMain
java -Djava.library.path=./jni -classpath ./bin com.study.jnilearn.JniFuncMain com.study.jnilearn.JniTest