import java.io.*;
import java.nio.file.Files;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class SHA256Sum {
    public static void main(String[] args) {
        if (args.length != 0) {
            for (String fileName : args) {
                calcFile(fileName);
            }
        } else {
            String fileName = "-";
            calcInput(fileName);
        }
    }

    public static void calcFile(String fileName) {
        try {
            byte[] bytes = Files.readAllBytes(new File(fileName).toPath());
            commonCalc(bytes, fileName);
        } catch (IOException e) {
            System.out.println("There are problems in IOStream");
        }
    }

    public static void calcInput(String fileName) {
        try {
            byte[] bytes = System.in.readAllBytes();
            commonCalc(bytes, fileName);
        } catch (IOException e) {
            System.out.println("There are problems in IOStream");
        }
    }

    public static void commonCalc(byte[] bytes, String fileName) {
        try {
            bytes = MessageDigest.getInstance("sha-256").digest(bytes);
        } catch (NoSuchAlgorithmException e) {
            System.out.println("WHAT? Send email to alex.manshutin99@gmail.com");
        }
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(Integer.toString((b & 0xff) + 0x100, 16).substring(1));
        }
        String result = sb.toString() + " *" + fileName;
        System.out.println(result);

    }
}
