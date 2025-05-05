#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt the plaintext using the Substitution cipher
void encrypt(char *pt, int key, char *ciphertext) {
    for (int i = 0; pt[i] != '\0'; i++) {
        char ch = pt[i];
        if (isupper(ch)) {
            ciphertext[i] = (char)((((ch - 'A') + key) % 26) + 'A');
        } else if (islower(ch)) {
            ciphertext[i] = (char)((((ch - 'a') + key) % 26) + 'a');
        } else {
            ciphertext[i] = ch; // Non-alphabet characters remain unchanged
        }
    }
    ciphertext[strlen(pt)] = '\0'; // Null-terminate the string
}

// Function to decrypt the ciphertext using the Substitution cipher
void decrypt(char *ct, int key, char *decryptedText) {
    for (int i = 0; ct[i] != '\0'; i++) {
        char ch = ct[i];
        if (isupper(ch)) {
            decryptedText[i] = (char)((((ch - 'A') - key + 26) % 26) + 'A');
        } else if (islower(ch)) {
            decryptedText[i] = (char)((((ch - 'a') - key + 26) % 26) + 'a');
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

    // Encrypt the plaintext
    encrypt(pt, key, ct);
    printf("Enc_Ciphertext: %s\n", ct);

    // Decrypt the ciphertext
    decrypt(ct, key, dct);
    printf("Dec_Ciphertext: %s\n", dct);

    return 0;
}
