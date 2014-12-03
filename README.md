testHdfsApiViaCAndJava
======================
main.cc is a C++ program that creates a JVM which performs a HDFS read via Java and main.cc also performs a HDFS read. Intent is to test and make sure there are no problems when we use HDFS api's via Java and C in the same process.

Set environment variables

```export LD_LIBRARY_PATH=/opt/mapr/hadoop/hadoop-2.4.1/lib/native/:/usr/java/jdk1.7.0_67/jre/lib/amd64/server```

Set CLASSPATH

```source setclasspath.sh```

Compile C program using the following cmd:

```g++ -I/opt/mapr/hadoop/hadoop-2.4.1/include -I/usr/java/jdk1.7.0_67/include/ -I /usr/java/jdk1.7.0_67/include/linux/ -I /root/ -L /opt/mapr/hadoop/hadoop-2.4.1/lib/native/ -L/usr/java/jdk1.7.0_67/jre/lib/amd64/server main.cc -lMapRClient -ljvm```

Compile Java code using standard cmd:

```javac TestProgram.java```

Run using the following cmd:

```./a.out input_file_1_for_java_read input_file_2_for_c_read```

Example:

```./a.out /user/root/a.txt /tmp/h1.err```
