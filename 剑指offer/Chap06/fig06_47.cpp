#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 不利用加减乘除做加法
// 完成一个求两数之和的函数，要求不使用+ - x /四则运算符号

// 对于这种，不能使用+-x/四则运算然后要求加法的
// 要想到位运算
// 想到加法器的本质，是利用异或位运算来实现的
// 但是直接把两个数异或，会丢失金进位的值
// 因此，本题的主要思想则是，如何能够把进位的值求出

// 当且仅当，两个数字，对应的位都是1的时候，才可以产生进位，并且，进位也仅仅往前走了一位
// 因此，我们只要求出，这两个数哪些位置，对应值都是1的，然后左移一位，就是进位的值
// 然后把进位和异或结果相加，但是这里又不能加，因此，只能和前面的方法一样，进行迭代
// 直到进位为0

// 暂不考虑溢出的情况
int add(int num1, int num2) {
	int sum = num1 ^ num2;
	int carray = (num1 & num2 ) << 1;
	// 由于sum和carray不能直接相加的，因此，按照此种方法迭代计算，直到caray为0
	int temp;
	while (carray){
		temp = sum;
		sum = temp ^ carray;
		carray = (temp & carray) << 1;
	} 
	return sum;
}

// 2021.02.14 
// 今日刷题，又看到这道题，现在需要考虑的是(temp & carray) << 1
// 这一步是可能溢出的，比如temp是-1（补码表现形式为11111111...111）carray为1
// 那么左移导致溢出，导致runtime error
// 应该先将temp * carray强制类型转换为unsigned int，再参与左移运算
// 同时把代码精简一下
//
// 注意算法的核心思想：
// 1.异或能得到不带进位的加法的结果
// 2.按位与然后左移1位得到进位结果
// 3.重复上述迭代过程，直到进位为0（不产生进位）
int add2(int a, int b) {
    if (a == 0 || b == 0)
        return a == 0 ? b : a;
    while (b != 0) {  // 这里把b当成一个记录进位的变量，a当成记录最终结果的变量
        int tmp = static_cast<unsigned int>(a & b) << 1;
        a = a ^ b;
        b = tmp;
    }
    return a;
}


int main(void) {
	int a, b;
	while (cin >> a >> b) {
		cout << a << " + " << b << " = " << add(a, b) << endl;
	}
	return 0;
}

