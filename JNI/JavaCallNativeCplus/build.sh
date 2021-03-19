javac src/com/study/jnilearn/HelloWorld.java -d ./bin
javah -jni -classpath ./bin -d ./jni com.study.jnilearn.HelloWorld
g++ -Ijni -fPIC -shared jni/HelloWorld.cpp -std=c++11 -o jni/libHelloWorld.so
java -Djava.library.path=./jni -classpath ./bin com.study.jnilearn.HelloWorld 