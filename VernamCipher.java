import java.util.Scanner;

class VernamCipher {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the plaintext: ");
        String pt = sc.nextLine().toUpperCase();

        System.out.print("Enter the key (same length as plaintext): ");
        String key = sc.nextLine().toUpperCase();

        if (pt.length() != key.length()) {
            System.out.println("Error: Key must be the same length as plaintext.");
            return;
        }

        StringBuilder ct = new StringBuilder();
        StringBuilder dct = new StringBuilder();

        // Encryption
        for (int i = 0; i < pt.length(); i++) {
            char ch = pt.charAt(i);
            char k = key.charAt(i);

            if (Character.isLetter(ch) && Character.isLetter(k)) {
                int encryptedVal = ((ch - 'A') ^ (k - 'A')) % 26; 
                ct.append((char) (encryptedVal + 'A'));
            } else {
                ct.append(ch); 
            }
        }

        System.out.println("Encrypted Ciphertext: " + ct);

        // Decryption
        for (int i = 0; i < ct.length(); i++) {
            char ch = ct.charAt(i);
            char k = key.charAt(i);

            if (Character.isLetter(ch) && Character.isLetter(k)) {
                int decryptedVal = ((ch - 'A') ^ (k - 'A')) % 26;
                dct.append((char) (decryptedVal + 'A'));
            } else {
                dct.append(ch); 
            }
        }

        System.out.println("Decrypted Plaintext: " + dct);
    }
}
