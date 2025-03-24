import java.util.Scanner;

class vigenereCipher {
    
    public static String generateKey(String text, String key) {
        StringBuilder newKey = new StringBuilder();
        int keyIndex = 0;
        for (int i = 0; i < text.length(); i++) {
            if (Character.isLetter(text.charAt(i))) {
                newKey.append(key.charAt(keyIndex % key.length()));
                keyIndex++;
            } else {
                newKey.append(text.charAt(i));
            }
        }
        return newKey.toString();
    }
    
    public static String encrypt(String text, String key) {
        StringBuilder ciphertext = new StringBuilder();
        key = generateKey(text, key);
        
        for (int i = 0; i < text.length(); i++) {
            char ch = text.charAt(i);
            if (Character.isUpperCase(ch)) {
                ciphertext.append((char) ((ch + key.charAt(i) - 2 * 'A') % 26 + 'A'));
            } else if (Character.isLowerCase(ch)) {
                ciphertext.append((char) ((ch + key.charAt(i) - 2 * 'a') % 26 + 'a'));
            } else {
                ciphertext.append(ch);
            }
        }
        return ciphertext.toString();
    }
    
    public static String decrypt(String text, String key) {
        StringBuilder plaintext = new StringBuilder();
        key = generateKey(text, key);
        
        for (int i = 0; i < text.length(); i++) {
            char ch = text.charAt(i);
            if (Character.isUpperCase(ch)) {
                plaintext.append((char) ((ch - key.charAt(i) + 26) % 26 + 'A'));
            } else if (Character.isLowerCase(ch)) {
                plaintext.append((char) ((ch - key.charAt(i) + 26) % 26 + 'a'));
            } else {
                plaintext.append(ch);
            }
        }
        return plaintext.toString();
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the plaintext: ");
        String plaintext = sc.nextLine();
        System.out.print("Enter the key: ");
        String key = sc.nextLine();
        
        String encryptedText = encrypt(plaintext, key);
        System.out.println("Enc_Ciphertext: " + encryptedText);
        
        String decryptedText = decrypt(encryptedText, key);
        System.out.println("Dec_Ciphertext: " + decryptedText);
    }
}
