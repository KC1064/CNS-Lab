//Find inverse of a number b in Zn
import java.util.Scanner;

public class Asgmt02_2 {

    public static int extendedGCD(int a, int b, int[] coeffs) {
        if (b == 0) {
            coeffs[0] = 1;
            coeffs[1] = 0;
            return a;
        }
        int[] nextCoeffs = new int[2];
        int gcd = extendedGCD(b, a % b, nextCoeffs);
        coeffs[0] = nextCoeffs[1];
        coeffs[1] = nextCoeffs[0] - (a / b) * nextCoeffs[1];
        return gcd;
    }

    public static Integer findModularInverse(int a, int n) {
        int[] coeffs = new int[2];
        int gcd = extendedGCD(a, n, coeffs);
        if (gcd != 1) {
            return null; // No modular inverse if a and n are not coprime
        }
        // Ensure the inverse is positive
        return (coeffs[0] % n + n) % n;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the number (a): ");
        int a = scanner.nextInt();
        System.out.print("Enter the modulus (n): ");
        int n = scanner.nextInt();

        if (n <= 0) {
            System.out.println("Modulus must be a positive integer.");
        } else {
            Integer inverse = findModularInverse(a, n);
            System.out.println(inverse == null ? "No modular inverse exists for " + a + " in Z" + n
                    : "The modular inverse of " + a + " in Z" + n + " is: " + inverse);
        }

    }
}
