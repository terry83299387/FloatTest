/**
 * 
 */
package qmk;

import java.util.Scanner;

/**
 * 有任意种水果，每种水果个数也是任意的，两人轮流从中取出水果，规则如下：
 *   1）每一次应取走至少一个水果；每一次只能取走一种水果的一个或者全部
 *   2）如果谁取到最后一个水果就胜
 * 给定水果种类N和每种水果的个数M1，M2，…Mn，算出谁取胜，编程实现之。
 * （题目的隐含条件是两个人足够聪明，聪明到为了取胜尽可能利用规则）
 * 
 * @author mkqiao
 * 
 */
public class WouldIWinTheGame {
	private static final String EXIT_PROGRAM = "q";

	/**
	 * @param args
	 * @throws Exception
	 */
	public static void main(String[] args) throws Exception {
		Scanner scanner = new Scanner(System.in);
		String input;
		int[] fruitNums;

		do {
			System.out.println("Input number of fruits (seperated by space)");
			System.out.println("Input q or Q to quit.");

			if (EXIT_PROGRAM.equalsIgnoreCase(input = scanner.nextLine())) {
				System.out.println("Program exits, bye");
				break;
			}

			input = input.trim();
			if (input.length() != 0) {
				fruitNums = initFruitNums(input);
				System.out.println(wouldWinTheGame(fruitNums, fruitNums.length));
			}
		} while (true);
	}

	private static int[] initFruitNums(String input) {
		String[] nums = input.split("\\s+");
		int[] fruitNums = new int[nums.length];
		int num;
		for (int i = 0; i < nums.length; i++) {
			num = Integer.parseInt(nums[i]);
			if (num <= 0) {
				throw new IllegalArgumentException("水果数量不能为0或负数：" + num);
			}

			fruitNums[i] = num;
		}

		return fruitNums;
	}

	private static boolean wouldWinTheGame(int[] fruitNums, int numOfTypes) {
		// only 1 fruits, we would win with no doubt
		if (numOfTypes == 1) {
			return true;
		}

		// only 2 fruits, we would win if the sum of their quantities is ODD
		if (numOfTypes == 2) {
			return sumOfTwoFruitNums(fruitNums) % 2 == 1;
		}

		// more than 3 fruits
		int num;
		for (int i = 0; i < fruitNums.length; i++) {
			num = fruitNums[i];
			if (num == 0) continue;

			// first, try to take all the fruit
			fruitNums[i] = 0;
			if (!wouldWinTheGame(fruitNums, numOfTypes - 1)) {
				fruitNums[i] = num;
				return true;
			}
			// take only one
			if (num > 1) {
				fruitNums[i] = num - 1;
				if (!wouldWinTheGame(fruitNums, numOfTypes)) {
					fruitNums[i] = num;
					return true;
				}
			}

			// if still can not win, restore the number of this fruit and continue to try
			fruitNums[i] = num;
		}

		// still can not win? we lose
		return false;
	}

	private static int sumOfTwoFruitNums(int[] fruitNums) {
		int num1 = 0;
		int num2 = 0;

		// find two fruit quantities
		for (int num : fruitNums) {
			if (num > 0) {
				if (num1 == 0) {
					num1 = num;
				} else {
					num2 = num;
					break;
				}
			}
		}

		return num1 + num2;
	}
}
