import java.math.BigDecimal;

/**
 * 该程序用于重现原问题，并通过BigDecimal来让我们更清楚地看到每次计算的结果。
 * 
 * @author mkqiao
 *
 */
public class FloatTest2 {

	/**
	 * 按照预期，opacity会在每次计算结束时增加0.01,循环100次后将变为1.0。
	 * 但运行该程序会发现，opacity增加到0.29后便不再增加了。
	 * 
	 * 由于Java会在输出double值时做一些“处理”，从而导致有时显示的并不是
	 * double在内存中存储的实际值，因此在这里借助BigDecimal来准确输出
	 * “opacity”和“opacity * 100”的值。
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		double opacity = 0;
		for (int i = 0; i < 100; i++) {
			opacity = ((int) (opacity * 100 + 1)) / 100.0;

			System.out.println("opacity=" + new BigDecimal(opacity));
			System.out.println("opacity*100=" + new BigDecimal(opacity * 100));
			System.out.println("----------------------------");
		}
	}

}
