import java.util.Scanner;

public class StandingO {
  
  public static void main (String [] args) {

    Scanner s = new Scanner(System.in);
    int cases = s.nextInt();

    for(int i = 0; i < cases; i++){
      int maxLevel = s.nextInt();
      String line = s.next();
      
      int attendence = 0; //how many people are standing
      int friendsToAdd = 0;
      for(int j = 0; j < line.length(); j++){
        int n = Character.getNumericValue(line.charAt(j));
        //System.out.println("number at " + j + ": " + n);
        if(n > 0){
          if(j > attendence) {
            friendsToAdd += j - attendence;
            //System.out.println("FRIENDSTOADD: " + friendsToAdd);
            //attendence += j - attendence;
            //attendence += n;
            //System.out.println("ATTENDNCE: " + attendence);
          
            attendence = j;
          }

          attendence += n;
         
        }
      
      }
      int temp = i + 1; 
      System.out.println("Case #"+temp+": " + friendsToAdd);
    }

  }


}
