def is_palindrome(num)
  num_str = num.to_s
  return num_str == num_str.reverse
end

puts "Enter the numbers with a space: "
entry_nums = gets.chomp
nums = entry_nums.split()

nums.each do |num|
  if num.length != 3
    puts "#{num} - It's not a three-digit number"
    next
  end

  num = num.to_i

  if is_palindrome(num)
    puts "#{num} - Is Palindrome"
  else
    puts "#{num} - Is not Palindrome"
  end
end
