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

    public boolean calculateMyAnswer(){
        int numberOfCases = Integer.parseInt(data[0]);
        int lineNumber = 1;

        for(int i = 0; i < numberOfCases; ++i){
                int [] barberCountAndMyPosition = stringToIntArrSplitter(data[lineNumber]);
                int [] barberSpeedArray = stringToIntArrSplitter(data[lineNumber+1]);
                lineNumber += 2;

                equationAndAlgorithmPerformer(barberCountAndMyPosition,barberSpeedArray);

        }
        return true;
    }

    private void equationAndAlgorithmPerformer(int [] barberCountAndMyPosition, int [] barberSpeedArray) {
        int peopleWithHaircut = 1;
        int[] workingBarberTimeTracker = new int[barberCountAndMyPosition[0]];
        boolean[] barberAvailability = new boolean[barberCountAndMyPosition[0]];

        Arrays.fill(barberAvailability, Boolean.TRUE);//init all the elements to true
        Arrays.fill(workingBarberTimeTracker, 0);

        while(peopleWithHaircut <= barberCountAndMyPosition[1]) {
            //System.out.println(peopleWithHaircut);
            //System.out.println("working barber "+Arrays.toString(workingBarberTimeTracker));
            //System.out.println("barber avail "+Arrays.toString(barberAvailability));
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
            //System.out.println("mid working barber "+Arrays.toString(workingBarberTimeTracker));
            //System.out.println("mid barber avail "+Arrays.toString(barberAvailability));
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

            //System.out.println("end working barber "+Arrays.toString(workingBarberTimeTracker));
            //System.out.println("end barber avail "+Arrays.toString(barberAvailability));
            //System.out.println("barber speed "+Arrays.toString(barberSpeedArray));
            ++peopleWithHaircut;
        }
    }

    private int getSmallest(int [] array){
        int smallest = array[0];

        for(int i = 0; i < array.length; ++i ){
            if(array[i] < smallest)
                smallest = array[i];
        }
        return smallest;
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
}
