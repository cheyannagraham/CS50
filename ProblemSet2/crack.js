// Given a string, output all possible permutations
// June 19, 2019
// Cheyanna Graham


const crack = (string) => {
    let permut_dig = 1;
    let key = [];
    let count = 0;
    
    // Initial function to iterate over string chars @ 1 digit
    const permutate = () => {
        
        while (count < string.length) {

            // loop through length of string
            for (let i = 0; i < string.length; i++) {
                
                key[permut_dig] = string[i];
                if (permut_dig < 2) {
                    console.log(key.join(""));
                }
            }
            // At end of string, add digit
            permut_dig++;
            if (permut_dig > string.length) {
                break;
            } else {
                setDigits(permut_dig);
            }
            count++;
        }
    }
    
    const setDigits = digits => {
        for (let i = 0; i < string.length; i++) {
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
    
    permutate();
}

crack('CRACK');