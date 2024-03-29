def Count_Digit(Num):
    digit_len = len(str(abs(Num)))
    if digit_len % 2 != 0:
        return 1
    else:
        return 0

entry_num = input("Enter the numbers with a space: ")
Nums = [int(num) for num in entry_num.split()]

count_odd_digits = sum(Count_Digit(num) for num in Nums)
print(count_odd_digits)
