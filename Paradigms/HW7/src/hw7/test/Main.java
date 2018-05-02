package hw7.test;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.math.BigInteger;

public class Main {

    public static void main(String[] args) {

        try (BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"))) {
            final int min = 2; // Минимальное число для диапазона
            final int max = 10000; // Максимальное число для диапазона
            for (int i = 0; i < 1000; i++) {
                int a = rnd(min, max);
                StringBuilder sb3 = new StringBuilder();
                StringBuilder sb4 = new StringBuilder();
                StringBuilder sb = new StringBuilder();
                if (a % 2 == 0) {
                    sb.append('-');
                }
                StringBuilder sb2 = new StringBuilder();
                for (int j = 0; j < a; j++) {

                    sb.append(Integer.toString(rnd(min, max) % 10));
                }
                a = rnd(min, 10);
                if (a % 3 == 0)
                    sb2.append('-');
                for (int j = 0; j < a; j++) {
                    sb2.append(Integer.toString(rnd(min, max) % 10));
                }

                a = rnd(min, 10);
                if (a % 5 == 0)
                    sb3.append('-');
                for (int j = 0; j < a; j++) {
                    sb3.append(Integer.toString(rnd(min, max) % 10));
                }


                a = rnd(min, max);
                if (a % 4 == 0)
                    sb4.append('-');
                for (int j = 0; j < a; j++) {
                    sb4.append(Integer.toString(rnd(min, max) % 10));
                }

                BigInteger first = new BigInteger(sb.toString());
                BigInteger second = new BigInteger(sb2.toString());
                BigInteger third = new BigInteger(sb3.toString());
                BigInteger fourth = new BigInteger(sb4.toString());
                writer.write(first.toString() + " + " + second.toString() + " = " + (first.add(second)) + '\n');
                writer.write(first.toString() + " - " + second.toString() + " = " + (first.subtract(second)) + '\n');
                writer.write(third.toString() + " += " + fourth.toString() + " = " + (third.add(fourth)) + '\n');
                writer.write(third.toString() + " -= " + fourth.toString() + " = " + (third.subtract(fourth)) + '\n');

            }
        } catch (IOException e) {
            System.out.println("Проёб");
        }

    }

    public static int rnd(int min, int max) {
        max -= min;
        return (int) (Math.random() * ++max) + min;
    }


}