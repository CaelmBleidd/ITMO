import java.util.*;
 
import java.io.*;
 
public class Main {
    private static void radixSort(String[] words, long length, long phases) {
        int R = 256;
        String[] second_array = new String[words.length];
        for (int d = (int)length-1; d>=0; d--) {
            if (phases == 0)
                break;
            else {
                int[] count = new int[R+1];
                for(int i =0; i<words.length; i++)
                    count[words[i].charAt(d)+1]++;
                for(int r = 0; r < R; r++)
                    count[r+1] += count[r];
                for(int i = 0; i<words.length; i++)
                    second_array[count[words[i].charAt(d)]++] = words[i];
                for(int i= 0 ; i<words.length; i++)
                    words[i] = second_array[i];
 
            }
            phases--;
        }
    }
 
    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream("radixsort.in"), "utf8"));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("radixsort.out"), "utf8"));
 
            String[] numbers = reader.readLine().split("\\s");
            int count = Integer.parseInt(numbers[0]);
            long length = Long.parseLong(numbers[1]);
            long phases = Long.parseLong(numbers[2]);
 
            String[] words = new String[count];
 
            for (int i = 0; i < count; i++) {
                words[i] = reader.readLine();
            }
 
            radixSort(words, length, phases);
 
            for(int i=0; i<count; i++){
                writer.write(words[i]+"\n");
            }
            writer.close();
            reader.close();
        } catch (IOException e) {
            e.getStackTrace();
        }
    }
}