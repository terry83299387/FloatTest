// 题目来自：http://segmentfault.com/q/1010000004364292

#include <stdio.h>
#include <stdlib.h>

// 基础函数，用于交换数组中的2个元素，本算法的核心思想是“遍历-交换”，所以可能需要频繁交换数组元素
void swap(int *nums, int n1, int n2) {
	int t = nums[n1];
	nums[n1] = nums[n2];
	nums[n2] = t;
}

// 在swapLastNums()函数中使用，不需要了解该函数的细节，看swapLastNums()函数中的注释即可
int findSwapPos(int *nums, int size, int i, int n, int needGreater) {
	int num = nums[i];
	while (n < i) {
		if ((needGreater > 0 && nums[n] > num)
				|| (needGreater < 0 && nums[n] < num)) {
			return n;
		}

		n += 2;
	}

	// 有解的话，一定能在上面的循环里找到一个符合条件的元素，所以这句代码一定不会执行
	return -1; // would never be here
}

void swapLastNums(int *nums, int size, int i, int needGreater) {
	// 到了这里，说明后面剩下的元素全部是相等的，这时候需要把这些元素以每次间隔一个的顺序与前面合适的元素交换
	//
	// 举个例子，假如现在数组顺序是：3,5,2,4,1,1,1,1，现在刚刚遍历到第二个1的位置，
	// 此时程序发现后面剩下的元素全部是1，所以就要把这些1与前面的元素进行交换。
	// 按照排序规则，第二个1的位置应该是一个较大的元素，所以我们从前面开始查找，
	// 找出连续两个比1大的元素，然后将较小的那个与当前位置的1交换。
	// 开头的两个元素3和5就满足要去，然后我们将较小的3与1交换，于是数组变成了：
	//
	//     [1],5,2,4,1,[3],1,1
	//
	// 括号中的1和3是交换后的元素，可以发现交换后数组的前半部分仍然满足排序规则，
	// 而交换后的3这个位置和它的后一个位置上的1也已经满足了交换规则，所以我们把循环变量加2，直接跳过后面一个1，
	// 然后继续从前面找出一个符合要求的元素来与最后一个1进行交换。当然，这次我们找到的是5和2，然后把较小的2与最后一个1交换，得到：
	//
	//     1,5,[1],4,1,3,1,[2]
	//
	// 可以看到，最后的结果刚好全部满足排序规则。
	//
	// 实际上我们不需要每次都比较2次，因为前半部分已经排好序的数组元素是满足n1<n2>n3<n4...这种关系的，
	// 所以我们只需要将奇数位或偶数位上的元素与当前元素进行比较即可。这也是findSwapPos()函数实际采用的方法，可以少一些比较。
	//
	// 还是以上面的数组为例，我们可以发现数组3,5,2,4,1,1,1,1的前半部分已经排好序的元素中，
	// 两两相邻元素之间较小的元素都在偶数位上（3和2），较大元素都在奇数位上（5和4）。
	// 所以当需要找出“较大元素中较小的那个元素”时，我们只需要判断位于偶数位上的那些元素即可，反之亦然。

	// 下面的变量n就是按这种思路进行初始化和递增的。
	//
	int n = (needGreater == 1 ? 0 : 1);
	while (i < size) {
		// needGreater用来指示是应该找更小的还是更大的
		// 上面注释里面的例子是找更大的，但也可能发生需要在前面找出比当前元素更小的元素的情况
		// 例如：2,5,4,6,6,6
		// 所以需要根据情况区别对待。
		//
		// 另外，在这里n的值会在循环间保持，并传给findSwapPos()函数。
		// 这主要是为了优化效率，因为每次交换后，n位置及其前面的元素都已经搜索过了，不需要每次都重复搜索一遍。
		// 看上面注释中的例子来体会这一点
		n = findSwapPos(nums, size, i, n, needGreater);
		swap(nums, i, n);
		i += 2;
		n += 2;
	}
}

// 不需要了解该函数的细节，见sort()中的注释即可
int findNotEqualOne(int *nums, int size, int i) {
	int num = nums[i];
	for (i++; i < size; i++) {
		if (nums[i] != num) {
			return i;
		}
	}

	return -1;
}

/*
 * 遍历数组，将每一个元素与它前面的元素进行比较，并在必要的时候调整元素的顺序
 * 数组遍历一遍之后就已经排好序了
 */
void sort(int *nums, int size) {
	int n;
	int i = 1;
	// 交替判断是否满足大于和小于关系，不满足时需要调整顺序
	while (i < size) {
		if (i % 2 == 1) { // 索引为奇数的元素需要比它前面的元素大
			if (nums[i] < nums[i-1]) { // 比前一个元素小，交换一下即可调整为大于关系
				swap(nums, i, i - 1);
			} else if (nums[i] == nums[i-1]) { // 两者相等时候的处理较为麻烦一些
				// 首先尝试从后面找出一个与当前元素不相等的元素
				n = findNotEqualOne(nums, size, i);
				if (n != -1) { // 返回值不等于-1说明找到了这样的元素
					// 根据元素n是较大还是较小来决定将其与元素i还是元素i-1交换
					if (nums[i] < nums[n]) {
						swap(nums, i, n);
					} else {
						swap(nums, i - 1, n);
					}
				} else {
					// ************【【【【这里很关键】】】】************
					// ************【【【【这里很关键】】】】************
					// ************【【【【这里很关键】】】】************
					//
					// n等于-1说明没有找到与当前元素不相等的元素，这就说明后面剩下的元素全部是相等的！！
					// 这时候需要把这些元素以每次间隔一个的顺序与前面合适的元素交换。见swapLastNums()函数
					//
					// ************【【【【这里很关键】】】】************
					// ************【【【【这里很关键】】】】************
					// ************【【【【这里很关键】】】】************
					swapLastNums(nums, size, i, 1);
					break;
				}
			} // 这里还有个else，不需要处理，因为已经比前一个元素要大了

		} else { // 判断是否比前一个元素小，不满足时调整顺序（算法与前面一样，就是关系是反过来的而已）
			if (nums[i] > nums[i-1]) {
				swap(nums, i, i - 1);
			} else if (nums[i] == nums[i-1]) {
				n = findNotEqualOne(nums, size, i);
				if (n != -1) {
					if (nums[i] > nums[n]) {
						swap(nums, i, n);
					} else {
						swap(nums, i - 1, n);
					}
				} else {
					swapLastNums(nums, size, i, -1);
					break;
				}
			}
		}

		i++;
	}
}

// -------------------- 下面的用来测试 -------------------
//int NUMS[] = {1, 5, 1, 1, 6, 4};
//int SIZE = 6;

//int NUMS[] = {2, 1};
//int SIZE = 2;

//int NUMS[] = {1, 5, 2, 2, 4, 1, 1};
//int SIZE = 7;

int NUMS[] = {5, 2, 2, 4, 1, 1, 1, 1};
int SIZE = 8;

void printResult() {
	int i = 0;
	while (i < SIZE) {
		printf("%d, ", NUMS[i]);
		i++;
	}
	printf("\n");
}

int main(int argc,char **argv) {
	sort(NUMS, SIZE);

	printResult();

	return EXIT_SUCCESS;
}
