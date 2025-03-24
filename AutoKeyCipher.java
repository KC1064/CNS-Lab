import java.util.Scanner;

class AutoKeyCipher {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the plaintext: ");
        String pt = sc.nextLine();
        System.out.print("Enter the key: ");
        int key = sc.nextInt();
        
        StringBuilder ct = new StringBuilder();
        StringBuilder dct = new StringBuilder();
        
        // Encryption
        int[] keyStream = new int[pt.length()];
        keyStream[0] = key;
        for (int i = 1; i < pt.length(); i++) {
            keyStream[i] = pt.charAt(i - 1) - 'a';
        }
        
        for (int i = 0; i < pt.length(); i++) {
            char ch = pt.charAt(i);
            if (ch >= 'A' && ch <= 'Z') {
                ct.append((char) (((ch - 'A' + keyStream[i]) % 26) + 'A'));
            } else if (ch >= 'a' && ch <= 'z') {
                ct.append((char) (((ch - 'a' + keyStream[i]) % 26) + 'a'));
            } else {
                ct.append(ch);
            }
        }
        System.out.println("Enc_Ciphertext: " + ct);
        
        // Decryption
        for (int i = 0; i < ct.length(); i++) {
            char ch = ct.charAt(i);
            if (ch >= 'A' && ch <= 'Z') {
                dct.append((char) (((ch - 'A' - keyStream[i] + 26) % 26) + 'A'));
            } else if (ch >= 'a' && ch <= 'z') {
                dct.append((char) (((ch - 'a' - keyStream[i] + 26) % 26) + 'a'));
            } else {
                dct.append(ch);
            }
        }
        System.out.println("Dec_Ciphertext: " + dct);
    }
}
