#!/bin/bash

setCLASSPATH() {
    HADOOP_HOME=/opt/mapr/hadoop/hadoop-2.4.1
    local h=$HADOOP_HOME/lib

    # Add the hadoop jars to classpath
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/yarn/hadoop-yarn-server-web-proxy*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/yarn/hadoop-yarn-common*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/yarn/hadoop-yarn-server-common*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/yarn/hadoop-yarn-api*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/yarn/hadoop-yarn-server-applicationhistoryservice*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/yarn/hadoop-yarn-server-resourcemanager*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/common/lib/hadoop-annotations*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/tools/lib/hadoop-auth*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/hdfs/hadoop-hdfs*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/mapreduce/hadoop-mapreduce-client-core*.jar)
    CLASSPATH+=:$(getPath /opt/mapr/lib/hadoop-common*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/common/*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/common/lib/*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/tools/lib/*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/hdfs/*.jar)
    CLASSPATH+=:$(getPath ${HADOOP_HOME}/share/hadoop/mapreduce/*.jar)
    CLASSPATH+=:$(getPath /opt/mapr/lib/maprfs*.jar)
    CLASSPATH+=:$(getPath /opt/mapr/lib/zookeeper*.jar)
    CLASSPATH+=:$(getPath /opt/mapr/lib/baseutils*.jar)
    CLASSPATH+=:$(getPath /opt/mapr/lib/libprotodefs*.jar)
    CLASSPATH+=:$(getPath /opt/mapr/lib/central-logging*.jar)

    # get the jars associated with impala
    CLASSPATH+=:$(getPath ${IMPALA_HOME}/lib/*.jar)

    # set the class path to pick up configuration files
    export CLASSPATH
}



##################################################################3
# create a path from a list of things - adds ":"
################################################333
getPath() {  # <list of things on path>
    local path=$1; shift
    local p;
    for p in "$@"; do
        path+=:$p
    done
    echo $path
}

setCLASSPATH
