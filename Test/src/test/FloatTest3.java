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
public class FloatTest3 {

	/**
	 * 由于去除了强制转换，因此不会导致原程序中由于截断所引起的错误。
	 * 同时该程序简单、直接，容易理解，因此我推荐用这种方法。
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		double opacity = 0;
		while (opacity < 1) {
			opacity += 0.01;
			System.out.println("opacity=" + opacity);
		}
	}

}
