using System;

class Program
{
    static bool IsOddDigits(int num)
    {
        int count = 0;
        while (num != 0)
        {
            count++;
            num /= 10;
        }
        return count % 2 != 0;
    }

    static void Main()
    {
        Console.Write("Enter the number of elements in the array: ");
        int n = Convert.ToInt32(Console.ReadLine());

        int[] nums = new int[n];
        Console.Write("Enter the elements of the array: ");
        for (int i = 0; i < n; i++)
        {
            nums[i] = Convert.ToInt32(Console.ReadLine());
        }

        int count = 0;
        foreach (int num in nums)
        {
            if (IsOddDigits(num))
            {
                count++;
            }
        }

        Console.WriteLine("The number of elements with odd number of digits is: " + count);
    }
}
