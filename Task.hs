main = do
    putStrLn "Enter the string: "
    stroka <- getLine
    let vowels = "aeyuoiAEYUOI"
    let consonants = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ"
    let num_vowels = (length)  (filter (`elem` vowels) stroka)
    let    num_consonants = (length) (filter (`elem` consonants) stroka)
    if num_vowels > num_consonants
        then putStrLn "Yes"
    else if num_vowels < num_consonants
        then putStrLn "No"
    else
        putStrLn "Identical"
