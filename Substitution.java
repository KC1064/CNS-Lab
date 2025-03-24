import java.util.Scanner;

  class MultiplicativeCipher {
    private static int modInverse(int key, int mod) {
        for (int i = 1; i < mod; i++) {
            if ((key * i) % mod == 1) {
                return i;
            }
        }
        return -1; // No modular inverse exists
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the plaintext: ");
        String pt = sc.nextLine();
        System.out.print("Enter the key: ");
        int key = sc.nextInt();
        
        // Ensure key has an inverse
        int keyInverse = modInverse(key);
        if (keyInverse == -1) {
            System.out.println("Invalid key! No modular inverse exists.");
            return;
        }
        
        StringBuilder ct = new StringBuilder();
        StringBuilder dct = new StringBuilder();
        
        // Encryption: C = (P * K) mod 26
        for (int i = 0; i < pt.length(); i++) {
            char ch = pt.charAt(i);
            if (ch >= 'A' && ch <= 'Z') {
                ct.append((char) (((ch - 'A') * key % 26) + 'A'));
            } else if (ch >= 'a' && ch <= 'z') {
                ct.append((char) (((ch - 'a') * key % 26) + 'a'));
            } else {
                ct.append(ch);
            }
        }
        System.out.println("Enc_Ciphertext: " + ct);
        
        // Decryption: P = (C * K^-1) mod 26
        for (int i = 0; i < ct.length(); i++) {
            char ch = ct.charAt(i);
            if (ch >= 'A' && ch <= 'Z') {
                dct.append((char) (((ch - 'A') * keyInverse % 26) + 'A'));
            } else if (ch >= 'a' && ch <= 'z') {
                dct.append((char) (((ch - 'a') * keyInverse % 26) + 'a'));
            } else {
                dct.append(ch);
            }
        }
        System.out.println("Dec_Ciphertext: " + dct);
    }
}
