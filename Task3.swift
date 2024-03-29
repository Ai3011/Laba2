func isPalindrome(_ num: Int) -> Bool {
    let numStr = String(num)
    return numStr == String(numStr.reversed())
}

print("Enter the numbers with a space:")
if let entryNums = readLine() {
    let nums = entryNums.split(separator: " ")
    
    for num in nums {
        if num.count != 3 {
            print("\(num) - It's not a three-digit number")
            continue
        }
        
        if let numInt = Int(num) {
            if isPalindrome(numInt) {
                print("\(numInt) - Is Palindrome")
            } else {
                print("\(numInt) - Is not Palindrome")
            }
        }
    }
}
