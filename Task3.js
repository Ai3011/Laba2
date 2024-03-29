function isPalindrome(num) {
    let num_str = num.toString();
    return num_str === num_str.split('').reverse().join('');
}

let entry_nums = prompt("Enter the numbers with a space: ");
let Nums = entry_nums.split(" ");

for (let num of Nums) {
    if (num.length !== 3) {
        console.log(num + " - It's not a three-digit number");
        continue;
    }
    num = parseInt(num);
    if (isPalindrome(num)) {
        console.log(num + " - Is Palindrome");
    } else {
        console.log(num + " - Is not Palindrome");
    }
}
