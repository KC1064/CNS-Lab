#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to compute gcd (greatest common divisor)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to perform modular exponentiation (base^exp) % mod
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;  // Handle base greater than mod
    while (exp > 0) {
        if (exp % 2 == 1) {  // If exp is odd, multiply base with result
            result = (result * base) % mod;
        }
        exp = exp >> 1;  // exp = exp / 2
        base = (base * base) % mod;  // base = base^2
    }
    return result;
}

// Function to generate a random private key
int genKey(int q) {
    int key = rand() % (q - 1) + 1;  // Generate a random key in range [1, q-1]
    return key;
}

// Structure to hold the cipher text (g^k and encrypted message)
typedef struct {
    int* encryptedMsg;
    size_t msgLength;
    int p;
} CipherPair;

// Function to encrypt a message using ElGamal
CipherPair encrypt(const char* msg, int q, int h, int g) {
    CipherPair cipher;
    cipher.msgLength = strlen(msg);
    cipher.encryptedMsg = (int*)malloc(cipher.msgLength * sizeof(int));
    int k = genKey(q);  // Generate a random key k

    int p = modExp(g, k, q);  // g^k mod q
    int s = modExp(h, k, q);  // g^(a*k) mod q

    printf("g^k used: %d\n", p);
    printf("g^(a*k) used: %d\n", s);

    // Encrypt the message
    for (size_t i = 0; i < cipher.msgLength; i++) {
        cipher.encryptedMsg[i] = s * (int)msg[i];
    }

    cipher.p = p;  // Store g^k for later use in decryption
    return cipher;
}

// Function to decrypt the message using ElGamal
void decrypt(const CipherPair* cipher, int key, int q, char* decryptedMsg) {
    int h = modExp(cipher->p, key, q);  // Calculate h = g^a mod q

    // Decrypt the message
    for (size_t i = 0; i < cipher->msgLength; i++) {
        int temp = cipher->encryptedMsg[i] / h;
        decryptedMsg[i] = (char)temp;
    }
    decryptedMsg[cipher->msgLength] = '\0';
}

int main() {
    srand(time(0));  // Seed the random number generator

    // Input message
    char msg[1024];
    printf("Enter the message to encrypt: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0';  // Remove newline character from input

    printf("Original Message: %s\n", msg);

    int q = 23;  // A small prime number for modulus (q)
    int g = 5;   // A generator g for ElGamal (choose a suitable value)
    int key = genKey(q);  // Generate private key 'a'
    int h = modExp(g, key, q);  // Calculate h = g^a mod q

    printf("g used: %d\n", g);
    printf("g^a used: %d\n", h);

    // Encrypt the message
    CipherPair cipher = encrypt(msg, q, h, g);

    // Decrypt the message
    char decryptedMsg[1024];
    decrypt(&cipher, key, q, decryptedMsg);

    printf("Decrypted Message: %s\n", decryptedMsg);

    // Clean up
    free(cipher.encryptedMsg);

    return 0;
}
