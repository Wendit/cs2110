/**
 * CS 2110 Fall 2014 HW2
 * Part 1 - Coding with bases
 * @author Wendi Tang
 * 
 * *** NOTE: The rules are different for each java file! ***
 *
 * You may not use any of the following:
 * - Any functions found in Java libraries (especially the Math library)
 *     - Example Math.pow, Integer.bitCount, String.valueOf, etc.
 *     - Basically, any function that does everything for you. The purpose of this
 *       homework is to learn how to do these operations yourself, and the Java API!
 *     - The only exception to this rule is String.charAt to get a character from a
 *       String, and you may use String.length to get the size of the string.
 *     - Any Java 7 feature / standard library function (we will be grading using Java 6)
 *     
 * - You my not implement any Java library functions as helpers to use in other functions.
 *     
 * - String concatenation with a number for more than one digit.
 *     - For example, "" + 123 is banned. "" + 6 is allowed, though.
 *     
 * - You may only use 2 conditionals in if-else clauses max per function.
 *     - This means you may have 2 separate conditions, making this okay:
 *     
 *     if(cond1) {
 *         code;
 *     } else {
 *         moreCode;
 *     }
 *     if(cond2) {
 *         code;
 *     } else {
 *         modeCode;
 *     }
 *     
 * - You may not use a switch statement.
 * - No nested for-loops! This is completely doable with one level of looping.
 * - Recursion is not allowed.
 * - You may not reuse any function to implement another function.
 */
public class HW2Bases
{
	/**
	 * strdtoi - Decimal String to int
	 *
	 * Convert a string containing ASCII characters (in decimal) to an int.
	 * You do not have to handle negative numbers. The Strings we will pass in will be
	 * valid decimal numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strdtoi("123"); // => 123
	 */
	public static int strdtoi(String decimal)
	{
		int returnValue = 0;
		
		for(int i = 0 ; i < decimal.length(); i++ )
		{
			returnValue = returnValue * 10 + decimal.charAt(i) - '0';
		}
		
		return returnValue;
	}

	/**
	 * strbtoi - Binary String to int
	 *
	 * Convert a string containing ASCII characters (in binary) to an int.
	 * You do not have to handle negative numbers. The Strings we will pass in will be
	 * valid binary numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strbtoi("111"); // => 7
	 */
	public static int strbtoi(String binary)
	{
		int returnValue = 0;
		
		for(int i = 0 ; i < binary.length(); i++ )
		{
			returnValue = returnValue * 2 + binary.charAt(i) - '0';
		}
		
		return returnValue;
	}

	/**
	 * strxtoi - Hexadecimal String to int
	 *
	 * Convert a string containing ASCII characters (in hex) to an int.
	 * You do not have to handle negative numbers. The Strings we will pass in will be
	 * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strxtoi("A6"); // => 166
	 */
	public static int strxtoi(String hex)
	{
		int returnValue = 0;
		
		for(int i = 0 ; i < hex.length(); i++ )
		{
			returnValue = returnValue * 16;
			if(hex.charAt(i) >= 'A')
				returnValue += hex.charAt(i) - 'A' + 10 ;
			else
				returnValue += hex.charAt(i) - '0';
		}
		
		return returnValue;
	}

	/**
	 * itostrb - int to Binary String
	 *
	 * Convert a int into a String containing ASCII characters (in binary).
	 * You do not have to handle negative numbers.
	 * The String returned should contain the minimum number of characters necessary to
	 * represent the number that was passed in.
	 * 
	 * Example: itostrb(7); // => "111"
	 */
	public static String itostrb(int binary)
	{
		String returnValue = "";
		
		int i = binary;
		for( ; i >= 2; i /= 2)
		{
			returnValue = i % 2 + returnValue;
			
		}
		returnValue = i + returnValue;
		
		return returnValue;
	}

	/**
	 * itostrx - int to Hexadecimal String
	 *
	 * Convert a int into a String containing ASCII characters (in hexadecimal).
	 * You do not have to handle negative numbers.
	 * The String returned should contain the minimum number of characters necessary to
	 * represent the number that was passed in.
	 * 
	 * Example: itostrx(166); // => "A6"
	 */
	public static String itostrx(int hex)
	{
		String returnValue = "";
		int remain = 0;
		
		int i = hex;
		for( ; i >= 16; i /= 16)
		{
			remain = i % 16;
			if( remain >= 10)
				returnValue = (char)('A'+(remain-10)) + returnValue;
			else
				returnValue = remain + returnValue;		
		}
		
		if( i >= 10)
			returnValue = (char)('A'+(i-10)) + returnValue;
		else
		returnValue = i + returnValue;
		
		return returnValue;
	}
}

