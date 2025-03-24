import java.util.HashMap;
import java.util.Scanner;

public class PlayfairCipher {
    private char[][] keyMatrix;
    private HashMap<Character, int[]> positionMap;

    public PlayfairCipher(String key) {
        keyMatrix = generateKeyMatrix(key);
        positionMap = buildPositionMap();
    }

    private char[][] generateKeyMatrix(String key) {
        key = key.toUpperCase().replaceAll("[^A-Z]", "").replace("J", "I");
        boolean[] used = new boolean[26];
        char[][] matrix = new char[5][5];
        int index = 0;

        for (char ch : key.toCharArray()) {
            if (!used[ch - 'A']) {
                matrix[index / 5][index % 5] = ch;
                used[ch - 'A'] = true;
                index++;
            }
        }

        for (char ch = 'A'; ch <= 'Z'; ch++) {
            if (ch != 'J' && !used[ch - 'A']) {
                matrix[index / 5][index % 5] = ch;
                used[ch - 'A'] = true;
                index++;
            }
        }

        return matrix;
    }

    private HashMap<Character, int[]> buildPositionMap() {
        HashMap<Character, int[]> map = new HashMap<>();
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                map.put(keyMatrix[row][col], new int[]{row, col});
            }
        }
        return map;
    }

    public String encrypt(String plaintext) {
        plaintext = prepareText(plaintext);
        StringBuilder ciphertext = new StringBuilder();

        for (int i = 0; i < plaintext.length(); i += 2) {
            char a = plaintext.charAt(i);
            char b = plaintext.charAt(i + 1);
            int[] posA = positionMap.get(a);
            int[] posB = positionMap.get(b);

            if (posA[0] == posB[0]) {
                ciphertext.append(keyMatrix[posA[0]][(posA[1] + 1) % 5]);
                ciphertext.append(keyMatrix[posB[0]][(posB[1] + 1) % 5]);
            } else if (posA[1] == posB[1]) {
                ciphertext.append(keyMatrix[(posA[0] + 1) % 5][posA[1]]);
                ciphertext.append(keyMatrix[(posB[0] + 1) % 5][posB[1]]);
            } else {
                ciphertext.append(keyMatrix[posA[0]][posB[1]]);
                ciphertext.append(keyMatrix[posB[0]][posA[1]]);
            }
        }

        return ciphertext.toString();
    }

    public String decrypt(String ciphertext) {
        StringBuilder plaintext = new StringBuilder();

        for (int i = 0; i < ciphertext.length(); i += 2) {
            char a = ciphertext.charAt(i);
            char b = ciphertext.charAt(i + 1);
            int[] posA = positionMap.get(a);
            int[] posB = positionMap.get(b);

            if (posA[0] == posB[0]) {
                plaintext.append(keyMatrix[posA[0]][(posA[1] + 4) % 5]);
                plaintext.append(keyMatrix[posB[0]][(posB[1] + 4) % 5]);
            } else if (posA[1] == posB[1]) {
                plaintext.append(keyMatrix[(posA[0] + 4) % 5][posA[1]]);
                plaintext.append(keyMatrix[(posB[0] + 4) % 5][posB[1]]);
            } else {
                plaintext.append(keyMatrix[posA[0]][posB[1]]);
                plaintext.append(keyMatrix[posB[0]][posA[1]]);
            }
        }

        return plaintext.toString().replace("X", "");
    }

    private String prepareText(String text) {
        text = text.toUpperCase().replaceAll("[^A-Z]", "").replace("J", "I");
        StringBuilder formattedText = new StringBuilder();

        for (int i = 0; i < text.length(); i++) {
            formattedText.append(text.charAt(i));
            if (i < text.length() - 1 && text.charAt(i) == text.charAt(i + 1)) {
                formattedText.append('X');
            }
        }

        if (formattedText.length() % 2 != 0) {
            formattedText.append('X');
        }

        return formattedText.toString();
    }

    public void displayKeyMatrix() {
        for (char[] row : keyMatrix) {
            for (char ch : row) {
                System.out.print(ch + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter key: ");
        String key = scanner.nextLine();

        PlayfairCipher playfair = new PlayfairCipher(key);
        System.out.println("\nGenerated Key Matrix:");
        playfair.displayKeyMatrix();

        System.out.print("\nEnter plaintext: ");
        String plaintext = scanner.nextLine();

        String encryptedText = playfair.encrypt(plaintext);
        System.out.println("\nEncrypted Text: " + encryptedText);

        String decryptedText = playfair.decrypt(encryptedText);
        System.out.println("Decrypted Text: " + decryptedText);

        scanner.close();
    }
}