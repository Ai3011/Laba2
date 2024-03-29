print("Enter the string: ")
let stroka = readLine()!
let vowels = "aeyuoiAEYUOI"
let consonants = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ"
var num_vowels = 0
var num_consonants = 0

for i in stroka {
    if vowels.contains(i) {
        num_vowels += 1
    }
}

for j in stroka {
    if consonants.contains(j) {
        num_consonants += 1
    }
}

if num_vowels > num_consonants {
    print("Yes")
} else if num_vowels < num_consonants {
    print("No")
} else {
    print("Identical")
}
