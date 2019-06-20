// Given a string, output all possible permutations
// June 19, 2019
// Cheyanna Graham


const crack = (string) => {
    let permutIdx = 0;
    let permutation = [];
    let count = 0;
    let strLen = string.length;

    // Recursively permutate index < 1
    const setIndex = index => {
        for (let i = 0; i < strLen; i++) {
            // set current value
            permutation[index] = string[i];

            // change the prev index
            if (index > 0) {
                setIndex(index - 1);
            }
            else {
                console.log(permutation.join(""));
            }
        }
    }
    // Iterate over string chars @ 1 digit
    while (count < strLen) {
        for (let i = 0; i < strLen; i++) {

            permutation[permutIdx] = string[i];
            if (permutIdx < 1) {
                console.log(permutation.join(""));
            }
        }
        // At end of string, add digit
        permutIdx++;
        if (permutIdx >= strLen) {
            break;
        } else {
            setIndex(permutIdx);
        }
        count++;
    }
}

crack('AB');