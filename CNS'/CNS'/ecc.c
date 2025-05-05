#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ECC Curve: y^2 = x^3 + ax + b mod p
const int a = 2;
const int b = 3;
const int p = 97; // prime field

typedef struct {
    int x;
    int y;
    int is_infinite;
} ECPoint;

// Mock character to point mapping (NOT SECURE, just for demo)
ECPoint letterToPoint(char c) {
    int x = (c == ' ') ? 0 : (c - 'A' + 1);
    int y = (x * x + 1) % p; // Not actual ECC point verification
    ECPoint pt = {x, y, 0};
    return pt;
}

char pointToLetter(ECPoint pt) {
    if (pt.is_infinite || pt.x == 0) return ' ';
    return 'A' + pt.x - 1;
}

int mod(int x, int m) {
    int r = x % m;
    return r < 0 ? r + m : r;
}

int modinv(int k, int m) {
    int s = 0, old_s = 1;
    int r = m, old_r = k;
    while (r != 0) {
        int q = old_r / r;
        int temp = r;
        r = old_r - q * r;
        old_r = temp;
        temp = s;
        s = old_s - q * s;
        old_s = temp;
    }
    return mod(old_s, m);
}

ECPoint addPoints(ECPoint P, ECPoint Q) {
    if (P.is_infinite) return Q;
    if (Q.is_infinite) return P;
    if (P.x == Q.x && mod(P.y + Q.y, p) == 0) return (ECPoint){0, 0, 1};

    int lambda;
    if (P.x == Q.x && P.y == Q.y) {
        int denom = modinv(2 * P.y, p);
        lambda = mod((3 * P.x * P.x + a) * denom, p);
    } else {
        int denom = modinv(Q.x - P.x, p);
        lambda = mod((Q.y - P.y) * denom, p);
    }

    ECPoint R;
    R.x = mod(lambda * lambda - P.x - Q.x, p);
    R.y = mod(lambda * (P.x - R.x) - P.y, p);
    R.is_infinite = 0;
    return R;
}

ECPoint scalarMultiply(ECPoint P, int k) {
    ECPoint R = {0, 0, 1}; // Point at infinity
    while (k > 0) {
        if (k % 2 == 1) R = addPoints(R, P);
        P = addPoints(P, P);
        k /= 2;
    }
    return R;
}

ECPoint subtractPoints(ECPoint P, ECPoint Q) {
    ECPoint negQ = {Q.x, mod(-Q.y, p), Q.is_infinite};
    return addPoints(P, negQ);
}

int main() {
    ECPoint G = {3, 6, 0}; // Base point
    int d = 7;             // Receiver's private key
    ECPoint Q = scalarMultiply(G, d); // Receiver's public key

    char message[100];
    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove trailing newline

    int msg_len = strlen(message);
    printf("Original message: %s\n", message);

    // === Encryption ===
    int k = 5; // Sender's random ephemeral secret
    ECPoint C1 = scalarMultiply(G, k);

    ECPoint encrypted[msg_len][2]; // Store (C1, C2) for each character

    for (int i = 0; i < msg_len; i++) {
        ECPoint M = letterToPoint(message[i]);
        ECPoint kQ = scalarMultiply(Q, k);
        ECPoint C2 = addPoints(M, kQ);
        encrypted[i][0] = C1;
        encrypted[i][1] = C2;
    }

    printf("\nEncrypted points:\n");
    for (int i = 0; i < msg_len; i++) {
        printf("Letter: %c -> C1=(%d,%d), C2=(%d,%d)\n", 
            message[i], 
            encrypted[i][0].x, encrypted[i][0].y,
            encrypted[i][1].x, encrypted[i][1].y
        );
    }

    // === Decryption ===
    printf("\nDecrypted message: ");
    for (int i = 0; i < msg_len; i++) {
        ECPoint dC1 = scalarMultiply(encrypted[i][0], d);
        ECPoint M = subtractPoints(encrypted[i][1], dC1);
        char decrypted_char = pointToLetter(M);
        printf("%c", decrypted_char);
    }
    printf("\n");

    return 0;
}
