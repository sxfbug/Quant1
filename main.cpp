#include <iostream> // 输入输出工具，比如 cout (用来打印信息)
#include <fstream>  // 文件操作工具，比如 ifstream (用来读取文件)
#include <sstream>  // 字符串处理工具，比如 stringstream (用来切分字符串)
#include <vector>   // 容器工具，比如 vector (用来存很多条数据)
#include <string>   // 字符串工具
#include<unordered_map> //哈希表
#include"func_declare.hpp"//函数声明



int main() {
	std::string filename = "Data/AAPLcsv_version.csv";
	std::vector<DailyInfo> data;
	data = load_data_from_csv(filename);
	
	std::string yieldsname = "Data/us_treasury_yields_daily_csv.csv";
	std::vector<US_Treasury_Yields> yields;
	yields = load_yields_from_csv(yieldsname);

	
	int days = 252;
	double norisk = 13.21 / 100;
	double base = 10000.0;
	double handle = 0.0;

	Dual_MA_Strategy_full(data, 5, 20, base, handle, days, norisk);
	Dual_MA_Strategy_full(data, 10, 50, base, handle, days, norisk);
	Dual_MA_Strategy_full(data, 50, 200, base, handle, days, norisk);
	Dual_MA_Strategy_full(data, 100, 500, base, handle, days, norisk);
    
}

/*
for (const auto& i : close) {
	std::cout << i << "\t";
}
*/
