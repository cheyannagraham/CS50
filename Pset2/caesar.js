

const encrypt = (key,pt) => {
    let ciphertext = '';
    for(let i = 0; i < pt.length; i++) {
        ciphertext += String.fromCharCode(pt.charCodeAt(i) + key);
    }
    console.log(`PT => ${ciphertext}`);

    return([key,ciphertext]);
}
const decrypt = ([key,ct]) => {
    let plaintext = '';
    for(let i = 0; i < ct.length; i++) {
        plaintext += String.fromCharCode(ct.charCodeAt(i) - key);
    }

    console.log(`CT => ${plaintext}`);

}

decrypt(encrypt(3,'Hey, Chey!'));