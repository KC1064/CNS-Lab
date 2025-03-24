import java.util.Scanner;

class Affine {
    
    public static int modInverse(int k1) {
        for (int i = 1; i < 26; i++) {
            if ((k1 * i) % 26 == 1) {
                return i;
            }
        }
        return -1;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

  
        System.out.print("Enter the plaintext: ");
        String pt = sc.nextLine();

        System.out.print("Enter k1 : ");
        int k1 = sc.nextInt();
        
        System.out.print("Enter k2: ");
        int k2 = sc.nextInt();
        sc.nextLine(); 


        int keyInverse = modInverse(k1);
        if (keyInverse == -1) {
            System.out.println("Invalid key. k1 must be coprime with 26.");
            return;
        }

     
        StringBuilder ct = new StringBuilder();
        for (char ch : pt.toCharArray()) {
            if (Character.isUpperCase(ch)) {
                ct.append((char) (((((ch - 'A') * k1 + k2) % 26) + 'A')));
            } else if (Character.isLowerCase(ch)) {
                ct.append((char) (((((ch - 'a') * k1 + k2) % 26) + 'a')));
            } else {
                ct.append(ch);
            }
        }
        System.out.println("Enc_Ciphertext: " + ct);

       
        StringBuilder dct = new StringBuilder();
        for (char ch : ct.toString().toCharArray()) {
            if (Character.isUpperCase(ch)) {
                dct.append((char) (((((ch - 'A' - k2 + 26) * keyInverse) % 26) + 'A')));
            } else if (Character.isLowerCase(ch)) {
                dct.append((char) (((((ch - 'a' - k2 + 26) * keyInverse) % 26) + 'a')));
            } else {
                dct.append(ch);
            }
        }
        System.out.println("Deciphered Text: " + dct);
    }
}
