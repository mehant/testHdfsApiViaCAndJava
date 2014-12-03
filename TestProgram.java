import org.apache.hadoop.fs.*;
import org.apache.hadoop.conf.*;

public class TestProgram {

  /*
   * Simple program to read a few bytes from the input file
   * and print to screen. Input file to read is provided from
   * the C program.
   */
  public static void main(String args[]) throws Exception {
    Configuration conf = new Configuration();
    // Set default conifguration to maprfs
    conf.set("fs.defaultFS", "maprfs:///");

    FileSystem fs;

    if (args.length != 1) {
      // Throw an exception if the input file is not provided from the C Program
      throw new RuntimeException("Input file not provided from C program");
    }

    String filePath = args[0];
    Path path = new Path(filePath);
    fs = path.getFileSystem(conf);

    // Open the file
    FSDataInputStream inputStream = fs.open(path);
    if (inputStream == null) {
      System.out.println("FSDataInputStream is null");
    }

    byte[] output = new byte[1024];
    int readSize = inputStream.read(output, 0, 1024);
    System.out.println("Amount of bytes read by java program: " + readSize);

    // Close the file
    fs.close();

    System.out.println("Printing bytes read in java\n");
    for (int i = 0; i < readSize; i++) {
      System.out.print((char)output[i]);
    }
  }
}
