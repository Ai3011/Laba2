function Count_Digit(Num) {
    let digit_len = Math.abs(Num).toString().length;
    if (digit_len % 2 !== 0) {
        return 1;
    } else {
        return 0;
    }
}

let entry_num = prompt("Enter the numbers with a space: ");
let Nums = entry_num.split(" ").map(num => parseInt(num));
let count_odd_digits = Nums.reduce((acc, num) => acc + Count_Digit(num), 0);
console.log(count_odd_digits);
