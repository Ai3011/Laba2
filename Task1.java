import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the string: ");
        String stroka = scanner.next();
        String vowels = "aeioyuAEIOYU";
        String consonants = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
        int num_vowels = 0;
        int num_consonants = 0;
        
        for (char c : stroka.toCharArray()) {
            if (vowels.indexOf(c) != -1) {
                num_vowels++;
            } 
        }
          for (char c : stroka.toCharArray()) {
            if (consonants.indexOf(c) != -1) {
                num_consonants++;
            } 
        }
        
        if (num_vowels > num_consonants) {
            System.out.println("Yes");
        } else if (num_vowels < num_consonants) {
            System.out.println("No");
        } else {
            System.out.println("Identical");
        }
    }
}
