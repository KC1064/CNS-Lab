#include <stdio.h>

// Function to perform modular exponentiation (base^exponent % mod)
int modPow(int base, int exponent, int mod) {
    int result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent % 2 == 1)  // If exponent is odd
            result = (result * base) % mod;
        exponent = exponent >> 1;  // Exponent = exponent / 2
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    int p, q, e, pt;

    // Input prime numbers p and q
    printf("Enter two prime numbers (p and q): ");
    scanf("%d %d", &p, &q);

    // Input public key e
    printf("Enter public key (e): ");
    scanf("%d", &e);

    // Input plaintext (numeric value)
    printf("Enter plain text value (numeric): ");
    scanf("%d", &pt);

    // Compute n and phi(n)
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    // Find private key d
    int d = 0;
    for (int i = 1; i < phi; i++) {
        if ((phi * i + 1) % e == 0) {
            d = (phi * i + 1) / e;
            break;
        }
    }

    // Encrypt the plaintext
    int ct = modPow(pt, e, n);

    // Decrypt the ciphertext
    int decryptedPt = modPow(ct, d, n);

    // Output
    printf("\n--- RSA Calculation ---\n");
    printf("P = %d, Q = %d\n", p, q);
    printf("n = %d, Φ(n) = %d\n", n, phi);
    printf("Public Key (e, n) = (%d, %d)\n", e, n);
    printf("Private Key (d) = %d\n", d);
    printf("Plain Text = %d\n", pt);
    printf("Cipher Text = %d\n", ct);
    printf("Decrypted Plain Text = %d\n", decryptedPt);

    return 0;
}
