package com.company;

import java.io.IOException;

public class Main {

    public static void main(String[] args) {
	// write your code here
        fileReader torrent = new fileReader(args[0]);

        String [] fileData = null;

        try{
            fileData = torrent.ReadFileData();

        }
        catch (IOException badStuffHappened) {
            System.out.println(badStuffHappened.getMessage());
        }

        int numberOfCases = Integer.parseInt(fileData[0]);

        for(int i = 1; i <= numberOfCases; ++i) {

            //int worstCase = Character.getNumericValue(fileData[i].charAt(0));
            String [] Data = fileData[i].split(" ");
            int worstCase = Integer.parseInt(Data[0]);
            String shyData = Data[1];

            int numPeopleStanding = 0;
            int numPeopleNeeded = 0;

            for(int j = 0; j <= worstCase; ++j) {
                int xx = Character.getNumericValue(shyData.charAt(j));

                if(numPeopleStanding >= j){
                    numPeopleStanding += xx;
                    continue;
                }
                else{
                    numPeopleNeeded += (j - numPeopleStanding);
                    numPeopleStanding += (j - numPeopleStanding);
                }

                numPeopleStanding += xx;

            }

            System.out.println("Case #"+ i + ": " + numPeopleNeeded);
        }
    }
}
