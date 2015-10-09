/**
 * 
 */
package qmk;

import java.math.BigInteger;

/**
 * 4维度超大数（不超过2005位10进制数）的Fibonacci程序：
 *     f(1)=f(2)=f(3)=f(4)=1
 *     n>4时，f(n)=f(n-1)+f(n-2)+f(n-3)+f(n-4)）
 * 
 * 用自定义的大数运算算法计算（运算过程中不使用BigInteger，打印结果时除外）
 * 
 * @author QiaoMingkui
 * 
 */
public class Fibonacci {
	private static final int DIM = 4;
	private static final int MAX_LENGTH = 150;

	/**
	 * @param args
	 * @throws Exception 
	 */
	public static void main(String[] args) throws Exception {
		int n = 100;
		long[] fn = fibonacci(n);
		printVeryLongInt(n, fn);
	}

	private static long[] fibonacci(int n) {
		long[][] fn = new long[DIM + 1][MAX_LENGTH];
		for (int i = 0; i < DIM; i++) {
			fn[i][0] = 1L;
		}

		int currentFnPointer = 0;
		for (int i = DIM + 1; i <= n; i++) {
			currentFnPointer = (i - 1) % (DIM + 1);
			nextFibonacci(fn, currentFnPointer);
		}

		return fn[currentFnPointer];
	}

	private static void nextFibonacci(long[][] fn, int fnPointer) {
		long[] t = new long[MAX_LENGTH];
		for (int i = 0; i < DIM + 1; i++) {
			if (i != fnPointer) {
				addVeryLongInt(fn[i], t);
			}
		}
		fn[fnPointer] = t;
	}

	private static void addVeryLongInt(long[] src, long[] to) {
		long carry = 0L;
		long sum;
		for (int i = 0; i < MAX_LENGTH; i++) {
			sum = src[i] + to[i] + carry;
			carry = sum >> 56; // bit 57 is carray-bit
			to[i] = sum & 0x00FFFFFFFFFFFFFFL; // remove carray-bit
		}
	}

	private static void printVeryLongInt(int n, long[] fn) {
//		int i;
		// find first none-zero fragment
//		for (i = MAX_LENGTH - 1; i >= 0 && fn[i] == 0L; i--) ;

//		for (; i >= 0; i--) {
//			
//		}

		byte[] bs = new byte[MAX_LENGTH * 7];
		long fragment;
		for (int i = MAX_LENGTH - 1, j = 0; i >= 0; i--) {
			fragment = fn[i];
			bs[j++] = (byte) (fragment >> 48);
			bs[j++] = (byte) ((fragment >> 40) & 0xFFL);
			bs[j++] = (byte) ((fragment >> 32) & 0xFFL);
			bs[j++] = (byte) ((fragment >> 24) & 0xFFL);
			bs[j++] = (byte) ((fragment >> 16) & 0xFFL);
			bs[j++] = (byte) ((fragment >> 8 ) & 0xFFL);
			bs[j++] = (byte) ((fragment      ) & 0xFFL);
		}
		BigInteger bi = new BigInteger(bs);
		System.out.println("f(" + n + "):\t" + bi);
	}
}
