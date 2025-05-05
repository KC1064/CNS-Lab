#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *plaintext, char *key, char *ciphertext) {
    int len = strlen(plaintext);
    int key_len = strlen(key);

    for (int i = 0; i < len; i++) {
        char pt_char = toupper(plaintext[i]);
        char key_char = toupper(key[i % key_len]);

        if (isalpha(pt_char)) {
            // Vigenère Cipher encryption formula
            int encryptedVal = ((pt_char - 'A') + (key_char - 'A')) % 26;
            ciphertext[i] = encryptedVal + 'A';
        } else {
            ciphertext[i] = plaintext[i]; // Keep non-letter characters as is
        }
    }
    ciphertext[len] = '\0'; // Null-terminate the string
}

void decrypt(char *ciphertext, char *key, char *decryptedText) {
    int len = strlen(ciphertext);
    int key_len = strlen(key);

    for (int i = 0; i < len; i++) {
        char ct_char = toupper(ciphertext[i]);
        char key_char = toupper(key[i % key_len]);

        if (isalpha(ct_char)) {
            // Vigenère Cipher decryption formula
            int decryptedVal = ((ct_char - 'A') - (key_char - 'A') + 26) % 26;
            decryptedText[i] = decryptedVal + 'A';
        } else {
            decryptedText[i] = ciphertext[i]; // Keep non-letter characters as is
        }
    }
    decryptedText[len] = '\0'; // Null-terminate the string
}

int main() {
    char plaintext[100], key[100], ciphertext[100], decryptedText[100];

    // Input the plaintext and key
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove the newline character

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove the newline character

    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext);
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, key, decryptedText);
    printf("Decrypted Plaintext: %s\n", decryptedText);

    return 0;
}
