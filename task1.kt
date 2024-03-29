import java.util.Scanner

fun main() {
    val scanner = Scanner(System.`in`)
    print("Enter the string: ")
    val stroka = scanner.next()
    val vowels = "aeioyuAEIOYU"
    val consonants = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ"
    var num_vowels = 0
    var num_consonants = 0
    for (c in stroka) {
        if (vowels.contains(c)) {
            num_vowels++
        } 
    }
    for (c in stroka) {
        if (consonants.contains(c)) {
            num_consonants++
        } 
    }
    when {
        num_vowels > num_consonants -> println("Yes")
        num_vowels < num_consonants -> println("No")
        else -> println("Identical")
    }
}
