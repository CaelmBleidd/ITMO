import java.util.*;
 
import java.io.*;
 
public class Main {
    private static int left_binsearch(long[] array, long key){
        int left = -1;
        int right = array.length;
        boolean isTrue = false;
        while(left<right -1 ){
            int middle = (left+right)/2;
            if(array[middle]==key)
                isTrue = true;
            if(array[middle]<key)
                left = middle;
            else right = middle;
        }
        if(isTrue) {
            return right + 1;
        }
        else return -1;
    }
    private static int right_binsearch(long[] array, long key){
        int left = -1;
        int right = array.length;
        boolean isTrue = false;
 
        while(left<right -1 ){
            int middle = (left+right)/2;
            if(array[middle]==key)
                isTrue = true;
            if(array[middle]<=key)
                left = middle;
            else right = middle;
        }
 
        if(isTrue) {
            return right ;
        }
        else return -1;
    }
 
    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream("binsearch.in"), "utf8"));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("binsearch.out"), "utf8"));
 
            int array_length = Integer.parseInt(reader.readLine());
            long[] array = new long[array_length];
            String[] string_array = reader.readLine().split("\\s");
 
            for (int i = 0; i < array_length; i++)
                array[i] = Long.parseLong(string_array[i]);
 
 
            int number_of_requests = Integer.parseInt(reader.readLine());
            long[] requests = new long[number_of_requests];
            String[] second_string_array = reader.readLine().split("\\s");
 
            for (int i = 0; i < number_of_requests; i++)
                requests[i] = Long.parseLong(second_string_array[i]);
 
 
            for(int i=0; i<number_of_requests; i++){
                writer.write(left_binsearch(array,requests[i])+" " + right_binsearch(array, requests[i])+"\n");
            }
 
 
 
            writer.close();
            reader.close();
        } catch (IOException e) {
            e.getStackTrace();
        }
    }
}