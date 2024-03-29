import java.util.Scanner;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the number of elements in the array: ");
        int n = scanner.nextInt();
        
        ArrayList<Integer> nums = new ArrayList<>();
        System.out.print("Enter the elements of the array: ");
        for (int i = 0; i < n; i++) {
            nums.add(scanner.nextInt());
        }
        
        int count = 0;
        for (int num : nums) {
            if (isOddDigits(num)) {
                count++;
            }
        }
        
        System.out.println("The number of elements with odd number of digits is: " + count);
    }
    
    public static boolean isOddDigits(int num) {
        int count = 0;
        while (num != 0) {
            count++;
            num /= 10;
        }
        return count % 2 != 0;
    }
}
