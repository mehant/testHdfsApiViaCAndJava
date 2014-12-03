testHdfsApiViaCAndJava
======================
Compile using the following cmd:

```g++ -I/opt/mapr/hadoop/hadoop-2.4.1/include -I/usr/java/jdk1.7.0_67/include/ -I /usr/java/jdk1.7.0_67/include/linux/ -I /root/ -L /opt/mapr/hadoop/hadoop-2.4.1/lib/native/ -L/usr/java/jdk1.7.0_67/jre/lib/amd64/server main.cc -lMapRClient -ljvm```

Run using the following cmd:

```./a.out input_file_1_for_java_read input_file_2_for_c_read```

Example:

```./a.out /user/root/a.txt /tmp/h1.err```
