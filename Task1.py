stroka = input("Enter the string: ")
vowels = 'aeyuoiAEYUOI' 
consonants = 'bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ' 
num_vowels = 0
num_consonants = 0
for i in stroka: 
    if i in vowels: 
        num_vowels += 1
for j in stroka: 
    if j in consonants: 
        num_consonants +=1
if (num_vowels > num_consonants):
  print("Yes")
if (num_vowels < num_consonants):
  print("No")
if (num_vowels == num_consonants):
  print("Identical")
