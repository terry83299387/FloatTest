#include <stdio.h>

/*
 * double转字符串程序，最大支持5位小数
 */
void dbl_to_str(double d, char *s, int precision) {
	// 将小数部分按精度要求乘以指定的倍数，从而转换为整数处理
	unsigned TIMES[] = {1, 10, 100, 1000, 10000, 100000};
	// 用来计算四舍五入的，名字不会起了……
	double ROUND[] = {0.51, 0.051, 0.0051, 0.00051, 0.000051, 0.0000051};

	// 将intPart定义为unsigned可以使支持的整数范围翻倍
	// weight为权值，用来取得整数部分的每一位数字，最大支持到10位（实际上不能超过unsigned的最大值，即40亿）
	unsigned intPart, decPart, times = TIMES[precision = precision > 5 ? 5 : precision], weight = 1000000000, lead_zeros = 1;

	// 处理负号
	if (d < 0) {
		d = -d;
		*(s++) = '-';
	}

	// 截取整数和小数部分（四舍五入），小数部分乘以适当的倍数来转换成整数，方便后面处理
	intPart = (unsigned) d;
	decPart = (unsigned) ((d - intPart + ROUND[precision]) * times);
	// 小数部分是否需要向整数部分进位
	if (decPart == TIMES[precision]) {
		intPart++;
		decPart -= TIMES[precision];
	}
	// printf("intPart is %u, decPart is %u\n", intPart, decPart); // debug

	// 如果整数部分为0，输出一个0
	if (intPart == 0) *(s++) = '0';
	// 否则，按顺序输出整数部分
	while (weight != 0) {
		if (intPart / weight != 0 || !lead_zeros) {
			*(s++) = (intPart / weight) + '0';
			intPart %= weight;
			lead_zeros = 0;
		}
		weight /= 10;
	}

	// 只有精度要求不为0时才加小数点
	if (precision > 0) *(s++) = '.';
	// 按精度要求的位数输出小数部分，即使全部为0也要输出足够的位数
	while (precision-- > 0) {
		times /= 10;
		*(s++) = (decPart / times) + '0';
		decPart %= times;
	}
	// 结束字符
	*(s++) = '\0';
}

/*
 * 测试。下面是输出：
	12345.678(2)=12345.68
	12345.678(8)=12345.67800
	3587009848.384214(1)=3587009848.4
	3587009848.384214(2)=3587009848.38
	-3587009848.384214(2)=-3587009848.38
	3859.978(0)=3860
	3859.978(1)=3860.0
	3859.978(2)=3859.98
	8802318.3971(2)=8802318.40
	1.499999(1)=1.5
	1.05(1)=1.1
	0.235(0)=0
	0.235(1)=0.2
	0.235(2)=0.24
	748313.235898(4)=748313.2359
	748313.235898(5)=748313.23590
 */
int main() {
	double d1 = 12345.678;
	double d2 = 3587009848.384214;
	double d3 = -3587009848.384214;
	double d4 = 3859.978;
	double d5 = 8802318.3971;
	double d6 = 1.499999;
	double d7 = 1.05;
	double d8 = 0.235;
	double d9 = 748313.23589756;
	char str[18];

	// 普通测试
	dbl_to_str(d1, str, 2);
	printf("%.3f(2)=%s\n", d1, str);

	// 测试指定精度大于5
	dbl_to_str(d1, str, 8);
	printf("%.3f(8)=%s\n", d1, str);

	// 测试大整数和四舍五入
	dbl_to_str(d2, str, 1);
	printf("%f(1)=%s\n", d2, str);

	dbl_to_str(d2, str, 2);
	printf("%f(2)=%s\n", d2, str);

	// 测试负数
	dbl_to_str(d3, str, 2);
	printf("%f(2)=%s\n", d3, str);

	// 测试四舍五入后小数部分进位到整数
	dbl_to_str(d4, str, 0);
	printf("%.3f(0)=%s\n", d4, str);

	// 同样进位到整数
	dbl_to_str(d4, str, 1);
	printf("%.3f(1)=%s\n", d4, str);

	// 不会进位到整数
	dbl_to_str(d4, str, 2);
	printf("%.3f(2)=%s\n", d4, str);

	// 百分位进位到十分位
	dbl_to_str(d5, str, 2);
	printf("%.4f(2)=%s\n", d5, str);

	// 测试是否正确四舍五入
	dbl_to_str(d6, str, 1);
	printf("%f(1)=%s\n", d6, str);

	// 测试是否正确四舍五入
	dbl_to_str(d7, str, 1);
	printf("%.2f(1)=%s\n", d7, str);

	// 测试整数部分为0
	dbl_to_str(d8, str, 0);
	printf("%.3f(0)=%s\n", d8, str);

	dbl_to_str(d8, str, 1);
	printf("%.3f(1)=%s\n", d8, str);

	dbl_to_str(d8, str, 2);
	printf("%.3f(2)=%s\n", d8, str);

	// 测试长小数
	dbl_to_str(d9, str, 4);
	printf("%f(4)=%s\n", d9, str);

	dbl_to_str(d9, str, 5);
	printf("%f(5)=%s\n", d9, str);

	return 0;
}
