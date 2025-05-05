/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MOD 26

// Function to clean and pad text
void prepareText(char* text, char* cleanText, int size) {
    int i, j = 0;
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            cleanText[j++] = toupper(text[i]);
        }
    }
    // Padding with 'X' if needed
    while (j % size != 0) {
        cleanText[j++] = 'X';
    }
    cleanText[j] = '\0';
}

// Function to multiply matrices
void multiplyMatrix(int* result, int textBlock[2], int key[2][2]) {
    result[0] = (textBlock[0] * key[0][0] + textBlock[1] * key[1][0]) % MOD;
    result[1] = (textBlock[0] * key[0][1] + textBlock[1] * key[1][1]) % MOD;
}

// Function to calculate determinant
int determinant(int key[2][2]) {
    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
}

// Function to find modular inverse
int modInverse(int det, int mod) {
    det = (det % mod + mod) % mod;
    for (int i = 1; i < mod; i++) {
        if ((det * i) % mod == 1)
            return i;
    }
    return -1;
}

// Function to find inverse matrix modulo 26
int inverseMatrix(int key[2][2], int inverse[2][2]) {
    int det = determinant(key);
    int detInv = modInverse(det, MOD);
    if (detInv == -1)
        return 0;

    inverse[0][0] = key[1][1];
    inverse[1][1] = key[0][0];
    inverse[0][1] = -key[0][1];
    inverse[1][0] = -key[1][0];

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inverse[i][j] = ((inverse[i][j] * detInv) % MOD + MOD) % MOD;
        }
    }
    return 1;
}

// Encryption function
void encrypt(char* text, int key[2][2], char* output) {
    int i, block[2], result[2];
    for (i = 0; text[i] != '\0'; i += 2) {
        block[0] = text[i] - 'A';
        block[1] = text[i + 1] - 'A';
        multiplyMatrix(result, block, key);
        output[i] = result[0] + 'A';
        output[i + 1] = result[1] + 'A';
    }
    output[i] = '\0';
}

// Decryption function
void decrypt(char* text, int key[2][2], char* output) {
    int inverse[2][2];
    if (!inverseMatrix(key, inverse)) {
        printf("Key matrix is not invertible modulo 26.\n");
        exit(1);
    }

    int i, block[2], result[2];
    for (i = 0; text[i] != '\0'; i += 2) {
        block[0] = text[i] - 'A';
        block[1] = text[i + 1] - 'A';
        multiplyMatrix(result, block, inverse);
        output[i] = result[0] + 'A';
        output[i + 1] = result[1] + 'A';
    }
    output[i] = '\0';
}

int main() {
    char input[100], cleanText[100], cipherText[100], decryptedText[100];
    int key[2][2];

    printf("Enter plaintext (letters only): ");
    fgets(input, sizeof(input), stdin);

    printf("Enter the 2x2 key matrix (values from 0 to 25):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &key[i][j]);
        }
    }

    prepareText(input, cleanText, 2);
    encrypt(cleanText, key, cipherText);
    printf("Encrypted Ciphertext: %s\n", cipherText);

    decrypt(cipherText, key, decryptedText);
    printf("Decrypted Plaintext: %s\n", decryptedText);

    return 0;
}
