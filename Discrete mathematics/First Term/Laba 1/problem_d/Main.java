package com.company;

import java.util.Scanner;



public class Main {

    int[] arr = new int[50];
    int[] table = new int[50];
    int[] z = new int[50];
    int[] ans = new int[50];
    int[] two_pow = {1,2, 4, 8, 16, 32, 64, 128};

   public  int dfs2(int n) {
       if (z[n] != -1)
           return z[n];
       else {
           int a = 0;
           int h = arr[n].length;
           for (int i = 0; i < h; i += 1)
           {
               a += dfs2(arr[n][i])*two_pow[h-i-1];
           }
           return table[n][a];
       }

   }
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);




    }

    }
}