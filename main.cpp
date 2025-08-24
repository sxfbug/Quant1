#include <iostream> // 输入输出工具，比如 cout (用来打印信息)
#include <fstream>  // 文件操作工具，比如 ifstream (用来读取文件)
#include <sstream>  // 字符串处理工具，比如 stringstream (用来切分字符串)
#include <vector>   // 容器工具，比如 vector (用来存很多条数据)
#include <string>   // 字符串工具
#include"func_declare.hpp"//函数声明



int main() {
	std::string filename = "Data/AAPLcsv_version.csv";
	std::vector<DailyInfo> data;
	data = load_from_csv(filename);

	std::vector<double> close;
	close = get_sum_close(data);
	std::cout << close.size() << std::endl;
	std::vector<double>MA5;
	
	std::vector<double>MA20;

	MA5 = get_MA(close, 5);
	std::cout << "MA5.size"<<MA5.size() << std::endl;
	MA20 = get_MA(close, 20);
	std::cout << "MA20.size"<<MA20.size() << std::endl;
	std::vector<TradeAct> act;
	act=Strategy1(MA5, MA20, data);
	
	int idx = 1;
	std::cout << "size of act"<<act.size()<<std::endl;
	/*for (int i = 0; i < 50; i++) {
		std::cout << idx << "\t\t";
		std::cout << act[i].date << "\t";
		std::cout << act[i].action << "\t";
		std::cout << act[i].close << std::endl;
		idx++;
	}*/

	std::cout << "\n\n\n";
	std::vector<Account> sum;
	double base = 10000.0;
	double fees = 0.0;
	sum = simulated_trading(act, data, base,fees);

	std::cout << "size of sum:"<<sum.size()<<"\n";
	
	/*for (int i = 0; i < sum.size(); i++) {
		std::cout << "Date:"<<sum[i].date << "\t\t";
		std::cout << "Cash:"<<sum[i].cash << "\t";
		std::cout << "Shares:"<<sum[i].shares << "\t";
		std::cout << "total value:"<<sum[i].total_value << std::endl;
	}*/
	double rate=annualized_rate_of_return(sum, base);
	std::cout << "annual rate:" << rate;
	



}

/*
for (const auto& i : close) {
	std::cout << i << "\t";
}
*/
