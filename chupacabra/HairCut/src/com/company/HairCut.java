package com.company;

import java.io.BufferedReader;
import java.io.FileReader;

public class HairCut {
        static int numTests = 0;
        static int[] barbsPosition;
        static int[] timePerBarb;

    public static void main(String[] args) throws Exception {
        String line = null;
        String line2 = null;

        BufferedReader in = new BufferedReader(new FileReader("B-small-practice.in"));
        numTests = Integer.parseInt(in.readLine());

        int count = 1;
        while(count <= numTests) {
            int totalTime = 0;
            int barber = 0;

            line = in.readLine();
            line2 = in.readLine();

            String[] split = line.split(" ");
            barbsPosition = new int[]{Integer.parseInt(split[0]), Integer.parseInt(split[1])};
            String[] split2 = line2.split(" ");
            timePerBarb = new int[split2.length];
            for(int i = 0; i < split2.length; ++i) {
                timePerBarb[i] = Integer.parseInt(split2[i]);
                totalTime += timePerBarb[i];
            }
            barber = (totalTime % barbsPosition[1]) % barbsPosition[0];
            if(barber == 0) {
                barber = barbsPosition[0];
            }
            System.out.print("Case #" + count + ": ");
            System.out.println(barber);
            ++count;
        }
    }
}
