/**
 * 该程序用于重现原问题。
 * 
 * @author mkqiao
 *
 */
public class FloatTest1 {

	/**
	 * 按照预期，opacity会在每次计算结束时增加0.01,循环100次后将变为1.0。
	 * 但运行该程序会发现，opacity增加到0.29后便不再增加了。
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		double opacity = 0;
		for (int i = 0; i < 100; i++) {
			opacity = ((int) (opacity * 100 + 1)) / 100.0;

			System.out.println("opacity=" + opacity);
		}
	}

}
