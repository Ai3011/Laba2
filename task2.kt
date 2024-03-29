import java.util.Scanner

fun isOddDigits(num: Int): Boolean {
    var count = 0
    var number = num
    while (number != 0) {
        count++
        number /= 10
    }
    return count % 2 != 0
}

fun main() {
    val scanner = Scanner(System.`in`)
    print("Enter the number of elements in the array: ")
    val n = scanner.nextInt()
    val nums = IntArray(n)
    print("Enter the elements of the array: ")
    for (i in 0 until n) {
        nums[i] = scanner.nextInt()
    }
    var count = 0
    for (num in nums) {
        if (isOddDigits(num)) {
            count++
        }
    }
    println("The number of elements with odd number of digits is: $count")
}
