/**
 * Given a string, write a routine that converts the string to a long, without using the
 * built in functions that would do this.
 */
public class StrToLong{

    /**
     * Helper function to convert a character to a decimal number 
     * 
     * @param ch the Character to convert
     * @param radix the radix (base) to use in the conversion
     * @return a decimal number if the charater arugment can be converted
     *         or -1 if the character argument is not valid.
     */
    private static int getDigit(char ch, int radix) {
        int digit = ch - '0';
        if ((radix == 8 || radix == 10) && 0 <= digit && digit < radix) {
            return digit;
        } else if (radix == 16) {
            int upperDigit = ch - 'A' + 10;
            int lowerDigit = ch - 'a' + 10;
            if (0 <= digit && digit < 10) {
               return digit;
            } else if (10 <= upperDigit && upperDigit < 16) {
               return upperDigit;
            } else if (10 <= lowerDigit && lowerDigit < 16) {
               return lowerDigit;
            }
        }
        return -1;
    }

    /**
     * The function first discards as many whitespace characters as necessary until
     * the first non-whitespace character is found. Then, starting from this character, 
     * takes an optional initial plus or minus sign followed by as many numerical 
     * digits as possible, and interprets them as a numerical value.
     * 
     * The string can contain additional characters after those that form the integral 
     * number, which are ignored and have no effect on the behavior of this function.
     * 
     * If the first sequence of non-whitespace characters in string is not a valid 
     * integral number, or  * if no such sequence exists because either string is empty
     * or it contains only whitespace characters, no conversion is performed.

     * If no valid conversion could be performed, a NumberFormatException is thrown.
     * If the correct value is out of the range of representable values 
     * (Long.MIN_VALUE(-9223372036854775808) to Long.MAX_VALUE (9223372036854775807)),
     * a NumberFormatException is thrown.
     * @param s the String to convert
     * @return the String argument converted to long (decimal)
     * @throws NumberFormatException if s cannot be converted as a long
     */

    private static long stringToLong(String s) {
        long res = 0;
        if (s == null || s.length() < 1) { // empty string
            throw new NumberFormatException();
        }
        int i = 0;
        int len = s.length();
        boolean positive = true;
        while (i < len && s.charAt(i) == ' ') { // delete leading spaces
            i++;
        }
        if (i == len) {
            throw new NumberFormatException();
        }
        if (s.charAt(i) == '+') {
            i++;
        } else if (s.charAt(i) == '-') {
            i++;
            positive = false;
        }
        if (i == len) {
            throw new NumberFormatException();
        }
        int radix = 10;
        if (s.charAt(i) == '0') {
            if (++i == len) {
                return 0;
            }
            if ((s.charAt(i) & ~('x' ^ 'X')) == 'X') {
                radix = 16;
                i++;
            } else {
                radix = 8;
            }
        }
        if (i == len || getDigit(s.charAt(i), radix) == -1) { // starting with non-digit character
            throw new NumberFormatException();
        }
        int ch = 0;
        while (i < s.length() && (ch = getDigit(s.charAt(i), radix)) != -1) { 
            if (Long.MAX_VALUE / radix < res || 
                Long.MAX_VALUE / radix == res && Long.MAX_VALUE % radix < ch) {
                throw new NumberFormatException(); 
            }
            res = res * radix + ch;
            i++;
        }
        return positive ? res : -res; 
    }

    public static void main(String []args){
        // valid postive decimal input with leading spaces
        long i  = stringToLong("   123");
        System.out.println(i == 123);
        // valid postive decimal
        i  = stringToLong("0x12345");
        // valid positive hexadecimal input
        System.out.println(i == 0x12345);
        // valid negative hexadecimal input
        i  = stringToLong("-0X4321");
        System.out.println(i == -0X4321);
        // valid negative octal input
        i  = stringToLong("-012455");
        System.out.println(i == -012455);
        // valid positive decimal input
        i  = stringToLong("+123abc");
        System.out.println(i == 123);
        // out of range decimal input (> Long.MAX_VALUE)
        try { i  = stringToLong("1223412341235199999999999");
        } catch (NumberFormatException e) {
            e.printStackTrace();
        }
        // out of range decimal input (< Long.MIN_VALUE)
        try { i  = stringToLong("-1223412341235199999999999");
        } catch (NumberFormatException e) {
            e.printStackTrace();
        }
        // invalid decimal input
        try { i  = stringToLong("");
        } catch (NumberFormatException e) {
            e.printStackTrace();
        }
        // invalid decimal input
        try { i  = stringToLong("abc123");
        } catch (NumberFormatException e) {
            e.printStackTrace();
        }
    }
}