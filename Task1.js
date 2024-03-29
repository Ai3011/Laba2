let stroka = prompt("Enter the string: ");
let vowels = 'aeyuoiAEYUOI';
let consonants = 'bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ';
let num_vowels = 0;
let num_consonants = 0;

for (let i of stroka) {
  if (vowels.includes(i)) {
    num_vowels += 1;
  }
}

for (let j of stroka) {
  if (consonants.includes(j)) {
    num_consonants += 1;
  }
}

if (num_vowels > num_consonants) {
  console.log("Yes");
} else if (num_vowels < num_consonants) {
  console.log("No");
} else {
  console.log("Identical");
}
