package com.company;

import java.util.Arrays;

/**
 * Created by hERO on 12/31/15.
 */
public class SmartGuy {
    private String [] data = null;

    public SmartGuy(String [] data){
        this.data = data;
    }

    private int getSmallest(int [] array){
        int smallest = array[0];

        for(int i = 0; i < array.length; ++i ){
            if(array[i] < smallest)
                smallest = array[i];
        }
        return smallest;
    }

    private long getLargest(long [] array){
        long largest = array[0];

        for(int i = 0; i < array.length; ++i ){
            if(array[i] > largest)
                largest = array[i];
        }
        return largest;
    }

    private int[] stringToIntArrSplitter(String toBeWorkedWith){
        String [] toParse = toBeWorkedWith.split(" ");
        int[] data = new int[toParse.length];

        for (int i = 0; i < toParse.length; i++) {
            try {
                data[i] = Integer.parseInt(toParse[i]);
            } catch (NumberFormatException nfe) {};
        }

        return data;
    }

    private long[] stringToLongArrSplitter(String toBeWorkedWith){
        String [] toParse = toBeWorkedWith.split(" ");
        long[] data = new long[toParse.length];

        for (int i = 0; i < toParse.length; i++) {
            try {
                data[i] = Long.parseLong(toParse[i]);
            } catch (NumberFormatException nfe) {};
        }

        return data;
    }

    /*------------------------------------------------Code Begins-----------------------------------------------------*/


    public boolean calculateMyAnswer(){
        int numberOfCases = Integer.parseInt(data[0]);
        int lineNumber = 1;

        for(int i = 0; i < numberOfCases; ++i){
                long [] barberCountAndMyPosition = stringToLongArrSplitter(data[lineNumber]);
                long [] barberSpeedArray = stringToLongArrSplitter(data[lineNumber+1]);
                lineNumber += 2;

                getBarberNumber(barberCountAndMyPosition, barberSpeedArray);

        }

        return true;
    }

    private long peopleServedAtGivenTime(long time,long numberOfBarbers, long [] barberSpeedArray){
        long peopleServed = 0;
        for(int i = 0; i < numberOfBarbers; ++i){
            peopleServed += time/barberSpeedArray[i] + 1; // why does this work even when it is fully divisible
        }

        return peopleServed;
    }

    private long getBarberNumber(long [] barberCountAndMyPosition, long [] barberSpeedArray){
        long min = -1;
        long max = barberCountAndMyPosition[1] * getLargest(barberSpeedArray) * 1000;

        while(min + 1 < max){
            long mid = (min + max)/2;
            if(peopleServedAtGivenTime(mid,barberCountAndMyPosition[0],barberSpeedArray) < barberCountAndMyPosition[1] ){
                min = mid;
            }
            else{
                max = mid;
            }
            long timeWhenYourChanceToGetHaircut = max - 1;
            long customersServerBefore = peopleServedAtGivenTime(timeWhenYourChanceToGetHaircut, barberCountAndMyPosition[0],barberSpeedArray);
            int customersToBeServed =  0;
            for (int barber = 0; barber < barberCountAndMyPosition[0]; barber++)
                // Is the barber available at time T?
                if ( % barberSpeedArray[barber] == 0) {
                    customers_to_be_served--;
                    if (customers_to_be_served == 0)
                        return barber;
                }

        }


        return 0;
    }

    /*---------------------------------------------BAD IMPLEMENTATION-------------------------------------------------*/
    /*
        This is a really direct naive implementation. The algorithm on the website describes it a direct simulation
        Runtime for this is terrible when it comes to bigger test cases
     */

    public boolean calculateMyAnswerLameWay(){
        int numberOfCases = Integer.parseInt(data[0]);
        int lineNumber = 1;

        for(int i = 0; i < numberOfCases; ++i){
                int [] barberCountAndMyPosition = stringToIntArrSplitter(data[lineNumber]);
                int [] barberSpeedArray = stringToIntArrSplitter(data[lineNumber+1]);
                lineNumber += 2;

                equationAndAlgorithmPerformerLame(barberCountAndMyPosition,barberSpeedArray);

        }
        return true;
    }

   private void equationAndAlgorithmPerformerLame(int [] barberCountAndMyPosition, int [] barberSpeedArray) {
        int peopleWithHaircut = 1;
        int[] workingBarberTimeTracker = new int[barberCountAndMyPosition[0]];
        boolean[] barberAvailability = new boolean[barberCountAndMyPosition[0]];

        Arrays.fill(barberAvailability, Boolean.TRUE);//init all the elements to true
        Arrays.fill(workingBarberTimeTracker, 0);

        while(peopleWithHaircut <= barberCountAndMyPosition[1]) {
            for (int j = 0; j < barberCountAndMyPosition[0]; ++j) {
                if (barberAvailability[j] == true) {
                    barberAvailability[j] = false;
                    workingBarberTimeTracker[j] = barberSpeedArray[j];
                    if(peopleWithHaircut == barberCountAndMyPosition[1])
                    {
                        System.out.println(j+1);
                        return;
                    }
                    break;
                }
            }
            while(getSmallest(workingBarberTimeTracker) != 0){
                for (int i = 0; i < barberCountAndMyPosition[0]; ++i) {
                    if (workingBarberTimeTracker[i] > 0) {
                        --workingBarberTimeTracker[i];
                    }
                    if (workingBarberTimeTracker[i] == 0) {
                        barberAvailability[i] = true;
                    }
                }
            }
            ++peopleWithHaircut;
        }
    }


}
