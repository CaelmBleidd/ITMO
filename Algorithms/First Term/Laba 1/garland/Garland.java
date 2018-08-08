
import java.io.*;
 
public class Main {
    private static boolean isAboveGroove(double mid, double left, int count) {
        double[] array = new double[count];
        array[0] = left;
        array[1] = mid;
        for (int i = 2; i < count; i++) {
            array[i]=2*array[i-1]+2-array[i-2];
            if(array[i]<0){
                return false;
            }
        }
        return true;
 
    }
 
    public static void main(String[] args) {
 
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream("garland.in")));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("garland.out")));
 
            String[] arr = reader.readLine().split(" ");
            double first = Double.parseDouble(arr[1]);
            int count = Integer.parseInt(arr[0]);
            double bad = 0;
            double good = first;
 
            while (true) {
                double mid = (good + bad) / 2;
                if (mid == good || mid == bad)
                    break;
                if (isAboveGroove(mid, first, count))
                    good = mid;
                else
                    bad = mid;
            }
 
            double[] array = new double[count];
            array[0] = first;
            array[1] = good;
 
            for (int i = 2; i < count; i++) {
                array[i]=2*array[i-1]+2-array[i-2];
            }
            String result = String.format("%.2f", array[count-1]);
            writer.write(result);
 
            writer.close();
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
 
        }
 
    }
}