def isPalindrome(num):
    num_str = str(num)
    return num_str == num_str[::-1]

entry_nums = input("Enter the numbers with a space: ")
Nums = entry_nums.split()

for num in Nums:
    if len(num) != 3:
        print(num, " - It's not a three-digit number")
        continue
    num = int(num)
    if isPalindrome(num):
        print(num, " - Is Palindrome")
    else:
        print(num, " - Is not Palindrome")
