 
import java.util.*;
import java.io.*;
import java.math.*;
 
public class Main {
    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream("style.in"), "utf8"));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("style.out"), "utf8"));
 
            String first = reader.readLine();
            int n = Integer.parseInt(first);
            String[] first_array = reader.readLine().split(" ");
            long[] array = new long[n];
 
            for (int i = 0; i < n; i++)
                array[i] = Long.parseLong(first_array[i]);
 
            String second = reader.readLine();
            int m = Integer.parseInt(second);
            String[] second_string_array = reader.readLine().split(" ");
            long[] second_array = new long[m];
 
            for (int i = 0; i < m; i++)
                second_array[i] = Long.parseLong(second_string_array[i]);
 
            String[] result_array = new String[n + m];
            int i = 0;
            int j = 0;
            int p = 0;
            while (true) {
                if (i <= array.length - 1 && j <= second_array.length - 1) {
                    if (array[i] > second_array[j]) {
                        result_array[p] = "s" + second_array[j];
                        p++;
                        j++;
                    } else {
                        result_array[p] = "f" + array[i];
                        i++;
                        p++;
                    }
                } else if (i > array.length - 1 && j > second_array.length - 1)
                    break;
                else if (j <= second_array.length - 1) {
                    result_array[p] = "s" + second_array[j];
                    p++;
                    j++;
                } else {
                    result_array[p] = "f" + array[i];
                    i++;
                    p++;
                }
            }
 
            long min = Long.MAX_VALUE;
            long min_1 = 0;
            long min_2 = 0;
            for (int d = 0; d < m + n - 1; d++) {
                if (result_array[d].charAt(0) == 'f' && result_array[d + 1].charAt(0) == 's') {
                    long a1 = Long.parseLong(result_array[d].substring(1, result_array[d].length()));
                    long a2 = Long.parseLong(result_array[d + 1].substring(1, result_array[d+1].length()));
                    long delta = Math.abs(a1 -a2 );
                    if (delta < min) {
                        min = delta;
                        min_1 = a1;
                        min_2 = a2;
                    }
                } else if (result_array[d].charAt(0) == 's' && result_array[d + 1].charAt(0) == 'f') {
                    long a2 = Long.parseLong(result_array[d].substring(1, result_array[d].length()));
                    long a1 = Long.parseLong(result_array[d + 1].substring(1, result_array[d+1].length()));
                    long delta = Math.abs(a2 -a1);
                    if (delta < min) {
                        min = delta;
                        min_2 =a2;
                        min_1 = a1;
                    }
                }
            }
            writer.write(min_1 + " " + min_2);
            writer.close();
            reader.close();
        } catch (IOException e) {
            e.getStackTrace();
        }
    }
}