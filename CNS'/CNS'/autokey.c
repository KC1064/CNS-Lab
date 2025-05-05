#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char pt[100], ct[100], dct[100];
    int initialKey, i;

    printf("Enter the plaintext (lowercase letters only): ");
    scanf("%s", pt);

    printf("Enter the initial key (number from 0 to 25): ");
    scanf("%d", &initialKey);

    int ptLen = strlen(pt);

    // Encryption
    char key[100];
    key[0] = (initialKey % 26) + 'a';
    for (i = 1; i < ptLen; i++) {
        key[i] = pt[i - 1];
    }

    for (i = 0; i < ptLen; i++) {
        ct[i] = ((pt[i] - 'a') + (key[i] - 'a')) % 26 + 'a';
    }
    ct[i] = '\0';

    printf("Encrypted Ciphertext: ");
    for (i = 0; i < ptLen; i++) {
        printf("%c", toupper(ct[i]));
    }
    printf("\n");

    // Decryption (fix)
    dct[0] = ((ct[0] - 'a') - initialKey + 26) % 26 + 'a';
    for (i = 1; i < ptLen; i++) {
        dct[i] = ((ct[i] - 'a') - (dct[i - 1] - 'a') + 26) % 26 + 'a';
    }
    dct[i] = '\0';

    printf("Decrypted Plaintext: %s\n", dct);

    return 0;
}
