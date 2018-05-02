import java.io.*;
import java.nio.file.Files;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

//public class CalcMD5 {
//    public static void main(String[] args) {
//        String fileName;
//        String currName;
//
//        try {
//            fileName = args[0];
//        } catch (ArrayIndexOutOfBoundsException e) {
//            System.out.print("You didn't specify a file name");
//            return;
//        }
//
//        try (BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
//            while ((currName = reader.readLine()) != null) {
//                byte[] bytes = Files.readAllBytes(new File(currName).toPath());
//                bytes = MessageDigest.getInstance("MD5").digest(bytes);
//                StringBuilder sb = new StringBuilder();
//                for (byte c : bytes) {
//                    sb.append(Integer.toString((c & 0xff) + 0x100, 16).substring(1));
//                }
//                System.out.println(sb.toString());
//            }
//        } catch (IOException e) {
//            System.out.print("There are problems in IOStream");
//        } catch (NoSuchAlgorithmException e) {
//            System.out.print("Invalid algorithm name");
//        }
//    }
//}

