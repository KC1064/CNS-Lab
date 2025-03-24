//Find gcd of any two numbers using Extended Euclidean algorithm.
import java.util.*;

public class Asgmt02_1 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter two numbers: ");
        int a = scanner.nextInt();
        int b = scanner.nextInt();
        int gcd = extendedGcd(a, b);
        System.out.println("GCD of " + a + " and " + b + " is " + gcd);
    }

    public static int extendedGcd(int a, int b) {
        int r1 = a, r2 = b;
        int s1 = 1, s2 = 0;
        int t1 = 0, t2 = 1;

        while (r2 != 0) {
            int q = r1 / r2;

            int temp = r2;
            r2 = r1 - q * r2;
            r1 = temp;

            temp = s2;
            s2 = s1 - q * s2;
            s1 = temp;

            temp = t2;
            t2 = t1 - q * t2;
            t1 = temp;
        }
        System.out.println("Coefficients s: " + s1 + ", t: " + t1);
        return r1;
    }
}