#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate the key based on the length of the plaintext
void generateKey(char *text, char *key, char *newKey) {
    int keyIndex = 0;
    int textLen = strlen(text);
    for (int i = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            newKey[i] = key[keyIndex % strlen(key)];
            keyIndex++;
        } else {
            newKey[i] = text[i];
        }
    }
    newKey[textLen] = '\0'; 
}

// Function to encrypt the plaintext using the Vigenère cipher
void encrypt(char *text, char *key, char *ciphertext) {
    char newKey[strlen(text) + 1];
    generateKey(text, key, newKey);
    
    for (int i = 0; i < strlen(text); i++) {
        char ch = text[i];
        if (isupper(ch)) {
            ciphertext[i] = (char)((ch + newKey[i] - 2 * 'A') % 26 + 'A');
        } else if (islower(ch)) {
            ciphertext[i] = (char)((ch + newKey[i] - 2 * 'a') % 26 + 'a');
        } else {
            ciphertext[i] = ch;
        }
    }
    ciphertext[strlen(text)] = '\0'; // Null-terminate the string
}

// Function to decrypt the ciphertext using the Vigenère cipher
void decrypt(char *text, char *key, char *plaintext) {
    char newKey[strlen(text) + 1];
    generateKey(text, key, newKey);

    for (int i = 0; i < strlen(text); i++) {
        char ch = text[i];
        if (isupper(ch)) {
            plaintext[i] = (char)((ch - newKey[i] + 26) % 26 + 'A');
        } else if (islower(ch)) {
            plaintext[i] = (char)((ch - newKey[i] + 26) % 26 + 'a');
        } else {
            plaintext[i] = ch;
        }
    }
    plaintext[strlen(text)] = '\0'; 
}

int main() {
    char plaintext[1000], key[1000], encryptedText[1000], decryptedText[1000];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 

    // Encrypt the plaintext
    encrypt(plaintext, key, encryptedText);
    printf("Enc_Ciphertext: %s\n", encryptedText);

    // Decrypt the ciphertext
    decrypt(encryptedText, key, decryptedText);
    printf("Dec_Ciphertext: %s\n", decryptedText);

    return 0;
}
