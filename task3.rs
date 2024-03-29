fn is_palindrome(num: i32) -> bool {
    let num_str = num.to_string();
    num_str == num_str.chars().rev().collect::<String>()
}

fn main() {
    let mut entry_nums = String::new();
    println!("Enter the numbers with a space: ");
    std::io::stdin().read_line(&mut entry_nums).expect("Failed to read line");
    
    let nums: Vec<&str> = entry_nums.split_whitespace().collect();
    
    for num in nums {
        if num.len() != 3 {
            println!("{} - It's not a three-digit number", num);
            continue;
        }
        
        let num: i32 = num.parse().expect("Failed to parse number");
        
        if is_palindrome(num) {
            println!("{} - Is Palindrome", num);
        } else {
            println!("{} - Is not Palindrome", num);
        }
    }
}
