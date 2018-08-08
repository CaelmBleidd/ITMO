 
import java.util.*;
import java.io.*;
import java.math.*;
 
public class Main {
    private static void swap(long[] array, int i, int j) {
        long tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
 
    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream("antiqs.in"), "utf8"));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("antiqs.out"), "utf8"));
 
            int a = Integer.parseInt(reader.readLine());
            long[] arr = new long[a];
            for (int i = 1; i <= a; i++) {
                arr[i-1] = i;
            }
            for (int i = 0; i < a; i++) {
                swap(arr, i, i / 2);
            }
            for (int i = 0; i < arr.length; i++)
                writer.write(arr[i] + " ");
            writer.close();
            reader.close();
        } catch (IOException e) {
            e.getStackTrace();
        }
    }
}