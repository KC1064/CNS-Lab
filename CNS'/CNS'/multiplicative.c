#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to find the modular inverse of the key
int modInverse(int key) {
    for (int i = 1; i < 26; i++) {
        if ((key * i) % 26 == 1) {
            return i;
        }
    }
    return -1; // Return -1 if no modular inverse exists
}

// Function to encrypt the plaintext using the Multiplicative cipher
void encrypt(char *pt, int key, char *ciphertext) {
    for (int i = 0; pt[i] != '\0'; i++) {
        char ch = pt[i];
        if (isupper(ch)) {
            ciphertext[i] = (char)(((ch - 'A') * key % 26) + 'A');
        } else if (islower(ch)) {
            ciphertext[i] = (char)(((ch - 'a') * key % 26) + 'a');
        } else {
            ciphertext[i] = ch; // Non-alphabet characters remain unchanged
        }
    }
    ciphertext[strlen(pt)] = '\0'; // Null-terminate the string
}

// Function to decrypt the ciphertext using the Multiplicative cipher
void decrypt(char *ct, int keyInverse, char *decryptedText) {
    for (int i = 0; ct[i] != '\0'; i++) {
        char ch = ct[i];
        if (isupper(ch)) {
            decryptedText[i] = (char)(((ch - 'A') * keyInverse % 26) + 'A');
        } else if (islower(ch)) {
            decryptedText[i] = (char)(((ch - 'a') * keyInverse % 26) + 'a');
        } else {
            decryptedText[i] = ch; // Non-alphabet characters remain unchanged
        }
    }
    decryptedText[strlen(ct)] = '\0'; // Null-terminate the string
}

int main() {
    char pt[1000], ct[1000], dct[1000];
    int key;

    // Input plaintext and key from the user
    printf("Enter the plaintext: ");
    fgets(pt, sizeof(pt), stdin);
    pt[strcspn(pt, "\n")] = '\0'; // Remove the newline character from input

    printf("Enter the key: ");
    scanf("%d", &key);

    // Find the modular inverse of the key
    int keyInverse = modInverse(key);
    if (keyInverse == -1) {
        printf("Invalid key. The key must be coprime with 26.\n");
        return 0; // Exit if the key is invalid
    }

    // Encrypt the plaintext
    encrypt(pt, key, ct);
    printf("Enc_Ciphertext: %s\n", ct);

    // Decrypt the ciphertext
    decrypt(ct, keyInverse, dct);
    printf("Dec_Ciphertext: %s\n", dct);

    return 0;
}
