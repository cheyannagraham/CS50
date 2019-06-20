// Given a string, output all possible permutations
// June 19, 2019
// Cheyanna Graham


const crack = (string) => {
    let permutDig = 1;
    let key = [];
    let count = 0;
    let strLen = string.length;

    // Recursive set permutate digits < 1
    const setDigits = digits => {
        for (let i = 0; i < strLen; i++) {
            // set current value
            key[digits] = string[i];

            // change the prev digits
            if (digits > 1) {
                setDigits(digits - 1);
            }
            else {
                console.log(key.join(""));
            }
        }
    }
    // Iterate over string chars @ 1 digit
    while (count < strLen) {
        for (let i = 0; i < strLen; i++) {

            key[permutDig] = string[i];
            if (permutDig < 2) {
                console.log(key.join(""));
            }
        }
        // At end of string, add digit
        permutDig++;
        if (permutDig > strLen) {
            break;
        } else {
            setDigits(permutDig);
        }
        count++;
    }
}

crack('ABC');