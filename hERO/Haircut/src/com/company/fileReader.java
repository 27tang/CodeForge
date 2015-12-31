package com.company;

import java.io.*;

/**
 * Created by hERO on 12/31/15.
 */
public class fileReader {
    private String filePath = null;

    public fileReader(String inputFilePath){
        filePath = inputFilePath;
    }

    public String[] ReadFileData() throws IOException{

        FileReader fr = new FileReader(filePath);
        BufferedReader textReader = new BufferedReader(fr);
        int numberOfLines = countLines();
        String [] fileData = new String[numberOfLines];

        for(int i = 0; i < numberOfLines; ++i){
            fileData[i] = textReader.readLine();
        }
        textReader.close();

        return fileData;
    }

    public int countLines() throws IOException {
        InputStream is = new BufferedInputStream(new FileInputStream(filePath));
        try {
            byte[] c = new byte[1024];
            int count = 0;
            int readChars = 0;
            boolean empty = true;

            while ((readChars = is.read(c)) != -1) { //stops reading when there are no more bytes to read in the stream
                empty = false;
                for (int i = 0; i < readChars; ++i) { // finding the number of newlines in the bytes read from inside the loop
                    if (c[i] == '\n') {
                        ++count;
                    }
                }
            }

            return (count == 0 && !empty) ? 1 : count;

        }
        finally {
            is.close();
        }
    }

}
