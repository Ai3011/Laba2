import Foundation

func countDigit(_ num: Int) -> Int {
    let digitLen = String(abs(num)).count
    if digitLen % 2 != 0 {
        return 1
    } else {
        return 0
    }
}

print("Enter the numbers with a space:")
let entryNum = readLine()
if let entryNum = entryNum {
    let nums = entryNum.split(separator: " ").compactMap { Int($0) }
    let countOddDigits = nums.reduce(0) { $0 + countDigit($1) }
    print(countOddDigits)
}
