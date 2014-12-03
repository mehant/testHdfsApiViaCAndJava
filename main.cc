#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni_helper.h>
#include <hdfs.h>

JNIEnv* getJniEnv() {
  JNIEnv *env;
  jint rv = 0;
  // Determine the # of LIBHDFS_OPTS args
  int noArgs = 1;
  char *hadoopJvmArgs = getenv("LIBHDFS_OPTS");
  char jvmArgDelims[] = " ";
  char *str, *token, *savePtr;
  char *hadoopClassPathVMArg = "-Djava.class.path=";
  char *hadoopClassPath = getenv("CLASSPATH");
  size_t optHadoopClassPathLen = strlen(hadoopClassPath) +
    strlen(hadoopClassPathVMArg) + 1;
  char *optHadoopClassPath = (char *) malloc(sizeof(char)*optHadoopClassPathLen);
    snprintf(optHadoopClassPath, optHadoopClassPathLen,
    "%s%s", hadoopClassPathVMArg, hadoopClassPath);

  if (hadoopJvmArgs != NULL)  {
    hadoopJvmArgs = strdup(hadoopJvmArgs);
    for (noArgs = 1, str = hadoopJvmArgs; ; noArgs++, str = NULL) {
      token = strtok_r(str, jvmArgDelims, &savePtr);
      if (NULL == token) {
        break;
      }
    }
    free(hadoopJvmArgs);
  }

  // Now that we know the # args, populate the options array
  JavaVMOption options[noArgs];
  options[0].optionString = optHadoopClassPath;
  hadoopJvmArgs = getenv("LIBHDFS_OPTS");
  if (hadoopJvmArgs != NULL)  {
    hadoopJvmArgs = strdup(hadoopJvmArgs);
    for (noArgs = 1, str = hadoopJvmArgs; ; noArgs++, str = NULL) {
      token = strtok_r(str, jvmArgDelims, &savePtr);
      if (NULL == token) {
        break;
      }
      options[noArgs].optionString = token;
    }
  }

  //Create the VM
  JavaVMInitArgs vm_args;
  JavaVM *vm;
  vm_args.version = JNI_VERSION_1_2;
  vm_args.options = options;
  vm_args.nOptions = noArgs; 
  vm_args.ignoreUnrecognized = 1;
  rv = JNI_CreateJavaVM(&vm, (void**)&env, &vm_args);
  return env;
}

void createJVMAndJavaRead(char *input) {
  JNIEnv *env = getJniEnv();

  int j = 0;

  if (env == NULL) {
    printf("java vm was not created\n");
  }

  jclass testProgramClass = env->FindClass("TestProgram");

  if (testProgramClass == NULL) {
    printf("could not find class \n");
  }

  jmethodID mainMethod = (env)->GetStaticMethodID(testProgramClass, "main", "([Ljava/lang/String;)V");

  if (mainMethod == NULL) {
    printf("method id is null");
  }

  jobjectArray applicationArgs = (env)->NewObjectArray(1, (env)->FindClass("java/lang/String"), NULL);
  jstring applicationArg0 = (env)->NewStringUTF(input);
  env->SetObjectArrayElement(applicationArgs, 0, applicationArg0);
  env->CallStaticVoidMethod(testProgramClass, mainMethod, applicationArgs);
}

void cRead(char *src_file_path) {
  // get a FS handle
  hdfsFS src_conn = hdfsConnect("127.0.0.1", 7222);

  if (src_conn == NULL) {
    printf("Unable to get file system handle \n");
  }

  tSize readStatus = 0;
  tSize readLength = 8 * 1024;
  hdfsFile srcFile = hdfsOpenFile(src_conn, src_file_path, O_RDONLY, 0, 0, 0);
  hdfsSeek(src_conn, srcFile, 0);

  if (srcFile == NULL) {
    printf("File open failed \n");
  }

  // check if file exists
  int exists = hdfsExists(src_conn, src_file_path);

  if (exists != 0) {
    printf("File %s does not exist", src_file_path);
  }

  // read some data
  void *buffer = malloc(readLength);
  readStatus = hdfsRead(src_conn, srcFile, buffer, readLength);

  if (readStatus == -1) {
    printf("read failed \n");
  }

  printf("number of bytes read by C program: %d \n", readStatus);  

  // printing bytes read
  printf("Printing bytes read in C program \n");
  for (int i = 0; i < readStatus; i++) {
    char *ptr = (char *) buffer + i;
    printf("%c", *ptr);
  }

  hdfsCloseFile(src_conn, srcFile);
} 

int main(int argc, char* argv[]) {
  // create the java vm and read the file via java
  createJVMAndJavaRead(argv[1]);

  // read another file via C
  cRead(argv[2]);

  return 1;
}
