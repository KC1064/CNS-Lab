#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to calculate modular inverse of k1 mod 26
int modInverse(int k1) {
    for (int i = 1; i < 26; i++) {
        if ((k1 * i) % 26 == 1) {
            return i;
        }
    }
    return -1;
}

int main() {
    char pt[1000], ct[1000], dct[1000];
    int k1, k2;

    printf("Enter the plaintext: ");
    fgets(pt, sizeof(pt), stdin);
    pt[strcspn(pt, "\n")] = '\0'; // Remove newline

    printf("Enter k1: ");
    scanf("%d", &k1);

    printf("Enter k2: ");
    scanf("%d", &k2);

    int k1_inverse = modInverse(k1);
    if (k1_inverse == -1) {
        printf("Invalid key. k1 must be coprime with 26.\n");
        return 1;
    }

    // Encryption
    for (int i = 0; pt[i]; i++) {
        char ch = pt[i];
        if (isupper(ch)) {
            ct[i] = ((k1 * (ch - 'A') + k2) % 26) + 'A';
        } else if (islower(ch)) {
            ct[i] = ((k1 * (ch - 'a') + k2) % 26) + 'a';
        } else {
            ct[i] = ch;
        }
    }
    ct[strlen(pt)] = '\0';

    printf("Enc_Ciphertext: %s\n", ct);

    // Decryption
    for (int i = 0; ct[i]; i++) {
        char ch = ct[i];
        if (isupper(ch)) {
            dct[i] = ((k1_inverse * ((ch - 'A' - k2 + 26)) % 26) + 'A');
        } else if (islower(ch)) {
            dct[i] = ((k1_inverse * ((ch - 'a' - k2 + 26)) % 26) + 'a');
        } else {
            dct[i] = ch;
        }
    }
    dct[strlen(ct)] = '\0';

    printf("Deciphered Text: %s\n", dct);

    return 0;
}
