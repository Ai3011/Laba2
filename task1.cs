using System;

class Program
{
    static void Main()
    {
        Console.Write("Enter the string: ");
        string stroka = Console.ReadLine();
        string vowels = "aeioyuAEIOYU";
        string consonants = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
        int num_vowels = 0;
        int num_consonants = 0;

        foreach (char c in stroka)
        {
            if (vowels.Contains(c))
            {
                num_vowels++;
            }
          
        }
        foreach (char c in stroka)
        {
            if (consonants.Contains(c))
            {
                num_consonants++;
            }
          
        }

        if (num_vowels > num_consonants)
        {
            Console.WriteLine("Yes");
        }
        else if (num_vowels < num_consonants)
        {
            Console.WriteLine("No");
        }
        else
        {
            Console.WriteLine("Identical");
        }
    }
}
