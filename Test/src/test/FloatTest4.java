/**
 * 
 */
package test;

/**
 * 该程序修正了原程序中的问题。
 * 
 * @author mkqiao
 *
 */
public class FloatTest4 {

	/**
	 * 该程序仍然使用强制转换，但会在每次中间结果上多加0.5，
	 * 从而保证中间结果一定是略大于所期望的整数，这样由于强制
	 * 转换而发生截断不会导致结果小于所期望的整数。
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		double opacity = 0;
		for (int i = 0; i < 100; i++) {
			// 此处是关键，加1.5而不是加1保证了中间结果是符合预期的
			opacity = ((int) (opacity * 100 + 1.5)) / 100.0;

			System.out.println("opacity=" + opacity);
		}
	}

}
