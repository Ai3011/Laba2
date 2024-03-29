print "Enter the string: "
stroka = gets.chomp
vowels = 'aeyuoiAEYUOI'
consonants = 'bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ'
num_vowels = 0
num_consonants = 0

stroka.each_char do |char|
  if vowels.include?(char)
    num_vowels += 1
  end
end

stroka.each_char do |char|
  if consonants.include?(char)
    num_consonants += 1
  end
end

if num_vowels > num_consonants
  puts "Yes"
elsif num_vowels < num_consonants
  puts "No"
else
  puts "Identical"
end
