import java.util.*;
 
import java.io.*;
 
public class Main {
    public static final Random RND = new Random();
 
    private static void swap(long[] array, int i, int j) {
        long tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
 
    private static int partition(long[] array, int begin, int end) {
        int index = begin + RND.nextInt(end - begin + 1);
        long pivot = array[index];
        int i = begin;
        int j = end;
        while (i <= j) {
            while (array[i] < pivot)
                i++;
            while (array[j] > pivot)
                j--;
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        return j;
    }
 
 
    private static void qsort(long[] array, int begin, int end) {
        if (end > begin) {
            int index = partition(array, begin, end);
            qsort(array, begin, index);
            qsort(array, index + 1, end);
        }
    }
 
    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream("sort.in"), "utf8"));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("sort.out"),"utf8"));
 
            String array_length_string = reader.readLine();
            int array_length = Integer.parseInt(array_length_string);
            String[] array_string = reader.readLine().split("\\s");
            long[] array = new long[100000];
 
            for (int i = 0; i < array_length; i++) {
                array[i] = Long.parseLong(array_string[i]);
            }
 
            qsort(array, 0, array_length - 1);
 
            for (int i = 0; i < array_length; i++)
               writer.write(array[i] + " ");
            writer.close();
            reader.close();
        } catch (IOException e) {
            e.getStackTrace();
        }
    }
}