#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char keyMatrix[SIZE][SIZE];
int positionMap[26][2];

// Function to generate the key matrix
void generateKeyMatrix(char *key) {
    int used[26] = {0}; // To track the used letters in the key
    int keyLen = strlen(key);
    int index = 0;
    
    for (int i = 0; i < keyLen; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') {
            ch = 'I'; // Treat 'J' as 'I'
        }
        if (isalpha(ch) && !used[ch - 'A']) {
            keyMatrix[index / SIZE][index % SIZE] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }
    
    // Fill the remaining spaces in the matrix with unused letters
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch != 'J' && !used[ch - 'A']) {
            keyMatrix[index / SIZE][index % SIZE] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }

    // Build position map for quick lookup
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            positionMap[keyMatrix[i][j] - 'A'][0] = i;
            positionMap[keyMatrix[i][j] - 'A'][1] = j;
        }
    }
}

// Function to prepare the plaintext by removing non-alphabet characters
// and ensuring that duplicate letters in a digraph are replaced with 'X'
void prepareText(char *text, char *preparedText) {
    int len = strlen(text);
    int index = 0;

    for (int i = 0; i < len; i++) {
        char ch = toupper(text[i]);
        if (ch == 'J') {
            ch = 'I'; // Treat 'J' as 'I'
        }

        if (isalpha(ch)) {
            preparedText[index++] = ch;
        }
    }
    
    // Add 'X' between identical letters
    for (int i = 0; i < index - 1; i++) {
        if (preparedText[i] == preparedText[i + 1]) {
            for (int j = index; j > i + 1; j--) {
                preparedText[j] = preparedText[j - 1];
            }
            preparedText[i + 1] = 'X';
            index++;
        }
    }

    // If the length is odd, append 'X' at the end
    if (index % 2 != 0) {
        preparedText[index++] = 'X';
    }

    preparedText[index] = '\0'; // Null-terminate the string
}

// Function to encrypt the text using Playfair Cipher
void encrypt(char *plaintext, char *ciphertext) {
    int len = strlen(plaintext);
    int index = 0;

    for (int i = 0; i < len; i += 2) {
        char a = plaintext[i];
        char b = plaintext[i + 1];

        int rowA = positionMap[a - 'A'][0], colA = positionMap[a - 'A'][1];
        int rowB = positionMap[b - 'A'][0], colB = positionMap[b - 'A'][1];

        if (rowA == rowB) {
            ciphertext[index++] = keyMatrix[rowA][(colA + 1) % SIZE];
            ciphertext[index++] = keyMatrix[rowB][(colB + 1) % SIZE];
        } else if (colA == colB) {
            ciphertext[index++] = keyMatrix[(rowA + 1) % SIZE][colA];
            ciphertext[index++] = keyMatrix[(rowB + 1) % SIZE][colB];
        } else {
            ciphertext[index++] = keyMatrix[rowA][colB];
            ciphertext[index++] = keyMatrix[rowB][colA];
        }
    }

    ciphertext[index] = '\0'; // Null-terminate the string
}

// Function to decrypt the text using Playfair Cipher
void decrypt(char *ciphertext, char *plaintext) {
    int len = strlen(ciphertext);
    int index = 0;

    for (int i = 0; i < len; i += 2) {
        char a = ciphertext[i];
        char b = ciphertext[i + 1];

        int rowA = positionMap[a - 'A'][0], colA = positionMap[a - 'A'][1];
        int rowB = positionMap[b - 'A'][0], colB = positionMap[b - 'A'][1];

        if (rowA == rowB) {
            plaintext[index++] = keyMatrix[rowA][(colA + SIZE - 1) % SIZE];
            plaintext[index++] = keyMatrix[rowB][(colB + SIZE - 1) % SIZE];
        } else if (colA == colB) {
            plaintext[index++] = keyMatrix[(rowA + SIZE - 1) % SIZE][colA];
            plaintext[index++] = keyMatrix[(rowB + SIZE - 1) % SIZE][colB];
        } else {
            plaintext[index++] = keyMatrix[rowA][colB];
            plaintext[index++] = keyMatrix[rowB][colA];
        }
    }

    plaintext[index] = '\0'; // Null-terminate the string
}

// Function to display the key matrix
void displayKeyMatrix() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", keyMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char key[100], plaintext[100], ciphertext[100], decryptedText[100];

    // Input the key and plaintext
    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove the newline character

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove the newline character

    // Generate the key matrix
    generateKeyMatrix(key);

    // Display the key matrix
    printf("\nGenerated Key Matrix:\n");
    displayKeyMatrix();

    // Prepare the plaintext for encryption
    char preparedText[200];
    prepareText(plaintext, preparedText);

    // Encrypt the plaintext
    encrypt(preparedText, ciphertext);
    printf("\nEncrypted Text: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}
