import java.util.Scanner;

class HillCipher {

    static void getKeyMatrix(String key, int[][] keyMatrix, int n) {
        int k = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                keyMatrix[i][j] = (key.charAt(k)) % 65;
                k++;
            }
        }
    }

    static void encrypt(int[][] cipherMatrix, int[][] keyMatrix, int[][] messageVector, int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 1; j++) {
                cipherMatrix[i][j] = 0;
                for (int x = 0; x < n; x++) {
                    cipherMatrix[i][j] += keyMatrix[i][x] * messageVector[x][j];
                }
                cipherMatrix[i][j] = cipherMatrix[i][j] % 26;
            }
        }
    }

    static String hillCipher(String message, String key) {
        int n = (int) Math.sqrt(key.length());
        if (n * n != key.length()) {
            throw new IllegalArgumentException("Key length must be a perfect square.");
        }

        int[][] keyMatrix = new int[n][n];
        getKeyMatrix(key, keyMatrix, n);

        StringBuilder cipherText = new StringBuilder();
        int len = message.length();

        for (int i = 0; i < len; i += n) {
            String block = message.substring(i, Math.min(i + n, len));
            if (block.length() < n) {
                block = padMessage(block, n);
            }

            int[][] messageVector = new int[n][1];
            for (int j = 0; j < n; j++) {
                messageVector[j][0] = (block.charAt(j)) % 65;
            }

            int[][] cipherMatrix = new int[n][1];
            encrypt(cipherMatrix, keyMatrix, messageVector, n);

            for (int j = 0; j < n; j++) {
                cipherText.append((char) (cipherMatrix[j][0] + 65));
            }
        }

        return cipherText.toString();
    }

    static String padMessage(String message, int n) {
        while (message.length() < n) {
            message += 'X';
        }
        return message;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter message: ");
        String message = scanner.nextLine().toUpperCase();

        System.out.print("Enter key : ");
        String key = scanner.nextLine().toUpperCase();

        try {
            String cipherText = hillCipher(message, key);
            System.out.println("Ciphertext: " + cipherText);
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }
}