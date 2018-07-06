package com.company;

import java.util.Scanner;

public class Main {


    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);

        int n = reader.nextInt(), k = reader.nextInt();
        int[][] mass = new int[101][101];
        int[][] dop = new int[101][101];
        int[] size = new int[101];
        int[] arr = new int[101];

        int ans = 0;

        for (int i = 0; i < k; i += 1) {
            for (int j = 0; j < n; j += 1) {
                mass[i][j] = reader.nextInt();
                dop[i][j] = mass[i][j];
                if (mass[i][j] != -1) {
                    size[i] += 1;
                }
            }
        }

        for (int i = 0; i < n; i += 1) {
            arr[i] = -1;
        }

        while (true) {
            int fl = 0;
            for (int i = 0; i < k; i += 1) {
                if (size[i] == 1) {
                    fl = 1;
                    for (int j = 0; j < n; j += 1) {
                        if (mass[i][j] != -1) {
                            arr[j] = mass[i][j];
                        }
                    }
                }
            }
            if (fl == 0) break;
            for (int i = 0; i < k; i += 1) {
                if (size[i] != 0) {
                    for (int j = 0; j < n; j += 1) {
                        if (mass[i][j] != -1 && arr[j] != -1) {
                            int z;
                            if (mass[i][j] == 1) {
                                z = arr[j];

                            } else {
                                if(arr[j]==0)
                                    z = 1;
                                else z = 0;
                            }
                            if (z == 1) {
                                size[i] = 0;
                                break;
                            } else {
                                size[i] -= 1;
                                mass[i][j] = -1;
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < k; i += 1) {
            int fl = 0;
            for (int j = 0; j < n; j += 1) {
                if (dop[i][j] != -1) {
                    if (arr[j] == -1) {
                        arr[j] = 0;
                    }
                    if (dop[i][j] == 0) {
                        int d;
                        if(arr[j]==0)
                            d = 1;
                        else d = 0;
                        if (fl < d) {
                            fl = d;
                        }
                    } else {
                        if (fl < arr[j]) {
                            fl = arr[j];
                        }
                    }
                }
            }
            if (fl == 0) {
                ans = 1;
            }
        }

        if (ans == 1) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }


    }
}