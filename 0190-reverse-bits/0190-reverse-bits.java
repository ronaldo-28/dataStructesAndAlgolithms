public class Solution {
    // you need treat n as an unsigned value
    public int reverseBits(int n) {
        int result = 0;
        int power = 31; // 32-bit integer, so start from the 31st bit

        while (n != 0) {
            // Extract the rightmost bit from n and append it to the reversed integer
            result += (n & 1) << power;
            n >>>= 1; // Unsigned right shift
            power--;
        }

        return result;
    }
}
