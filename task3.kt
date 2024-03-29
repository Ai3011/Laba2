fun isPalindrome(num: Int): Boolean {
    val numStr = num.toString()
    return numStr == numStr.reversed()
}

fun main() {
    print("Enter the numbers with a space: ")
    val entryNums = readLine()
    val nums = entryNums?.split(" ") ?: emptyList()

    for (num in nums) {
        if (num.length != 3) {
            println("$num - It's not a three-digit number")
            continue
        }
        val numInt = num.toInt()
        if (isPalindrome(numInt)) {
            println("$num - Is Palindrome")
        } else {
            println("$num - Is not Palindrome")
        }
    }
}
