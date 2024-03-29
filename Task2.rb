def count_digit(num)
  digit_len = num.abs.to_s.length
  digit_len % 2 != 0 ? 1 : 0
end

print "Enter the numbers with a space: "
entry_num = gets.chomp
nums = entry_num.split.map(&:to_i)
count_odd_digits = nums.map { |num| count_digit(num) }.sum
puts count_odd_digits
