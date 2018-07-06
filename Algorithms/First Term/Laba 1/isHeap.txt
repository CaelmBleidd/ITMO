import java.io.*;
 
 
public class Main {
 
    public static void main(String[] args) {
 
 
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream("isheap.in")));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("isheap.out")));
 
 
 
        long array_length = Long.parseLong(reader.readLine());
 
 
        boolean IsTrue = true;
 
        String[] arr = reader.readLine().split("\\s");
 
        for (int i = 0; i < array_length / 2 + 1; i++) {
            if (i * 2 + 1 < array_length && Long.parseLong(arr[2 * i + 1]) < Long.parseLong(arr[i])) {
                IsTrue = false;
                break;
            } else if (i * 2 + 2 < array_length && Long.parseLong(arr[2 * i + 2]) < Long.parseLong(arr[i])) {
                IsTrue = false;
                break;
            }
        }
 
        if (IsTrue)
            writer.write("YES");
        else  writer.write("NO");
        writer.close();
        reader.close();
        } catch (IOException e) {
            e.printStackTrace();
 
        }
         
 
    }
}