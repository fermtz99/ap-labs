//Fernando Martinez A01630401
import java.util.*;

public class codeChallange{
  public static int valores(String str){
    Set<Character> h = new HashSet<Character>();
    for(int i = 0; i<str.length(); i++){
      h.add(str.charAt(i));
    }
    return h.size();
  }

  public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    System.out.println("Enter the word to check:");
    String word = scan.nextLine();
    System.out.println(valores(word));
  }
}

