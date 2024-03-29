use std::io;

fn count_digit(num: i32) -> i32 {
    let digit_len = i32::abs(num).to_string().len() as i32;
    if digit_len % 2 != 0 {
        return 1;
    } else {
        return 0;
    }
}

fn main() {
    let mut entry_num = String::new();
    println!("Enter the numbers: ");
    std::io::stdin().read_line(&mut entry_num).expect("Failed to read line");
    let nums: Vec<i32> = entry_num.split_whitespace().map(|num| num.parse().unwrap()).collect();
    
    let count_odd_digits: i32 = nums.iter().map(|&num| count_digit(num)).sum();
    println!("{}", count_odd_digits);
}
