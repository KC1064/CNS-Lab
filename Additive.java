import java.util.Scanner;

class Additive {
    public static int modInverse(int key) {
        for (int i = 1; i < 26; i++) {
            if ((key + i) % 26 == 0) {
                return 26 - i;
            }
        }
        return -1;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the plaintext: ");
        String pt = sc.nextLine();
        System.out.print("Enter the key: ");
        int key = sc.nextInt();
        
        StringBuilder ct = new StringBuilder();
        StringBuilder dct = new StringBuilder();
        
        // Encryption
        for (int i = 0; i < pt.length(); i++) {
            char ch = pt.charAt(i);
            if (ch >= 'A' && ch <= 'Z') {
                ct.append((char) (((ch - 'A' + key) % 26) + 'A'));
            } else if (ch >= 'a' && ch <= 'z') {
                ct.append((char) (((ch - 'a' + key) % 26) + 'a'));
            } else {
                ct.append(ch);
            }
        }
        System.out.println("Enc_Ciphertext: " + ct);
        
        // Decryption
        for (int i = 0; i < ct.length(); i++) {
            char ch = ct.charAt(i);
            if (ch >= 'A' && ch <= 'Z') {
                dct.append((char) (((ch - 'A' - key + 26) % 26) + 'A'));
            } else if (ch >= 'a' && ch <= 'z') {
                dct.append((char) (((ch - 'a' - key + 26) % 26) + 'a'));
            } else {
                dct.append(ch);
            }
        }
        System.out.println("Dec_Ciphertext: " + dct);
    }
}
