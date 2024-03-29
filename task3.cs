using System;

class Program
{
    static bool IsPalindrome(int num)
    {
        string numStr = num.ToString();
        char[] charArray = numStr.ToCharArray();
        Array.Reverse(charArray);
        string reversedNumStr = new string(charArray);
        return numStr == reversedNumStr;
    }

    static void Main()
    {
        Console.WriteLine("Enter the numbers with a space: ");
        string entryNums = Console.ReadLine();
        string[] nums = entryNums.Split(' ');

        foreach (string numStr in nums)
        {
            if (numStr.Length != 3)
            {
                Console.WriteLine(numStr + " - It's not a three-digit number");
                continue;
            }

            int num = int.Parse(numStr);

            if (IsPalindrome(num))
            {
                Console.WriteLine(num + " - Is Palindrome");
            }
            else
            {
                Console.WriteLine(num + " - Is not Palindrome");
            }
        }
    }
}
