package com.company;

/**
 * Created by hERO on 12/31/15.
 */

import java.io.IOException;

public class Main {

    public static void main(String[] args) {
	// write your code here
        String test = new String(args[0]);
        fileReader myReader = new fileReader(test);
        String[] fileData = null;

        try{
            fileData = myReader.ReadFileData();

        }
        catch (IOException badStuffHappened){
            System.out.println(badStuffHappened.getMessage());
        }

        /*for (String s: fileData) {
            System.out.println(s);
        }*/

        int numberOfLinesInFile = fileData.length;

    }
}
