use std::io;

fn main() {
    let mut stroka = String::new();

    println!("Enter the string: ");
    io::stdin().read_line(&mut stroka).expect("Failed to read line");

    let vowels = "aeioyuAEIOYU";
    let consonants = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
    let mut num_vowels = 0;
    let mut num_consonants = 0;

    for c in stroka.chars() {
        if vowels.contains(c) {
            num_vowels += 1;
        } 
    }
    
    for c in stroka.chars() {
        if consonants.contains(c) {
            num_consonants += 1;
        } 
    }

    if num_vowels > num_consonants {
        println!("Yes");
    } else if num_vowels < num_consonants {
        println!("No");
    } else {
        println!("Identical");
    }
}
