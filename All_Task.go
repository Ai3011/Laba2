package main

import (
	"fmt"
	"strconv"
	"strings"
)

// задание 1
func countVowelsAndConsonants(s string) string {
	vowels := 0
	consonants := 0
	s = strings.ToLower(s) // заменяем все буквы на маленькие

	for _, char := range s { //цикл по каждому символу в строке,  каждый символ присваивается переменной char
		if strings.Contains("aeiouy", string(char)) { // проверка есть ли строчке символы.
			vowels++
		} else if 'a' <= char && char <= 'z' {
			consonants++
		}
	}

	if vowels > consonants {
		return "Yes"
	} else if vowels < consonants {
		return "No"
	} else {
		return "Identical"
	}
}

//задание 2

func countNumbersWithOddDigits(nums []int) int {
	count := 0
	for _, num := range nums {
		tempNum := num
		digitCount := 0
		for tempNum > 0 {
			tempNum /= 10
			digitCount++
		}
		if digitCount%2 != 0 {
			count++
		}
	}
	return count
}

// Задание 3
func isPalindrome(n int) bool {
	temp := n
	reverse := 0
	for temp > 0 {
		remainder := temp % 10
		reverse = reverse*10 + remainder
		temp /= 10
	}
	return n == reverse
}

func main() {
	var s string
	fmt.Println("Enter the string:")
	fmt.Scanln(&s)

	result := countVowelsAndConsonants(s)
	fmt.Println(result)

	//Задание 2
	var n int
	fmt.Println("Enter the number of elements in the array:")
	fmt.Scanln(&n)

	nums := make([]int, n) // создание среза с длиной n

	fmt.Println("Enter the elements of the array:")
	for i := 0; i < n; i++ {
		fmt.Scanln(&nums[i])
	}

	result2 := countNumbersWithOddDigits(nums)
	fmt.Println("The number of elements with odd number of digits is:", result2)

	//Задание 3
	fmt.Println("Enter three-digit numbers separated by a space:")
	for i := 0; i < 3; i++ {
		var input string
		fmt.Scan(&input)
		number, err := strconv.Atoi(input)
		if err != nil { // nil = 0
			fmt.Println("Number entry error.")
			return
		}

		if number >= 100 && number <= 999 {
			if isPalindrome(number) {
				fmt.Printf("%d - YES\n", number)
			} else {
				fmt.Printf("%d - NO\n", number)
			}
		} else {
			fmt.Println("Error!")
		}
	}
}
