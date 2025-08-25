#include <iostream> // 输入输出工具，比如 cout (用来打印信息)
#include <fstream>  // 文件操作工具，比如 ifstream (用来读取文件)
#include <sstream>  // 字符串处理工具，比如 stringstream (用来切分字符串)
#include <vector>   // 容器工具，比如 vector (用来存很多条数据)
#include <string>   // 字符串工具
#include<iomanip > //求百分比
#include<cmath> //计算金融指标
#include"func_declare.hpp"

//计算对应的MA
//参数：收盘价vector，MA的y（过去y日）
//输出：double的vector
std::vector<double>get_MA(const std::vector<double>& close, int y) {
	std::vector<double> MA;
	double sum = 0.0;
	/*if (close.size() < y) {
		std::cout << "too few arguments in close vector";
		return MA;
	}*/
	//滑动窗口：先计算前面y个元素
	int temp;
	for (int i = 0; i < y && i < close.size(); i++) {
		sum += close[i];
		MA.push_back(0.0);
		temp = i;
	}

	//第y+1个元素的MA值
	MA.push_back(sum / y);

	//从第y+2个元素开始
	for (int i = y + 1; i < close.size(); i++) {
		sum = sum - close[i - y] + close[i];
		MA.push_back(sum / y);

	}
	return MA;
}
