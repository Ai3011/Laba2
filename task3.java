import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the numbers with a space: ");
        String entryNums = scanner.nextLine();
        String[] nums = entryNums.split(" ");

        for (String num : nums) {
            if (num.length() != 3) {
                System.out.println(num + " - It's not a three-digit number");
                continue;
            }

            int number = Integer.parseInt(num);
            if (isPalindrome(number)) {
                System.out.println(num + " - Is Palindrome");
            } else {
                System.out.println(num + " - Is not Palindrome");
            }
        }
    }

    public static boolean isPalindrome(int num) {
        String numStr = String.valueOf(num);
        return numStr.equals(new StringBuilder(numStr).reverse().toString());
    }
}
