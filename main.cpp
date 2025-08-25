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

	std::vector<double> close;
	close = get_sum_close(data);
	std::cout << "close.size"<<close.size() << std::endl;
	std::vector<double>MA5;
	
	std::vector<double>MA20;

	MA5 = get_MA(close, 5);
	std::cout << "MA5.size"<<MA5.size() << std::endl;
	MA20 = get_MA(close, 20);
	std::cout << "MA20.size"<<MA20.size() << std::endl;
	std::vector<TradeAct> act;
	act=Strategy1(MA5, MA20, data);
	
	
	std::cout << "act.size"<<act.size()<<std::endl;
	

	std::cout << "\n\n\n";
	std::vector<Account> sum;
	double base = 10000.0;
	double fees = 0.0;
	sum = simulated_trading(act, data, base,fees);

	std::cout << "size of sum:"<<sum.size()<<"\n";
	

	double ret = total_return(sum, base);
	std::cout << "total return:" << ret << "\n";

	double rate=annualized_rate_of_return(sum, base);
	std::cout << "annual rate:" << rate<<"\n";
	
	double md = max_drawdown(sum);
	std::cout << "max drawdown:" << md << "\n";

	std::vector<double> daily_return= daily_rate_of_return(sum);
	std::cout << "nums of daily return:" << daily_return.size()<<"\n";
	double st = standard_deviation(daily_return);
	int days = 252;
	double an_vo = annualized_volatility(st, days);
	
	double norisk = 13.21 / 100;
	double sharpe = sharpe_rate(rate, norisk, an_vo);
	std::cout << "sharpe rate:" << sharpe << "\n";


}

/*
for (const auto& i : close) {
	std::cout << i << "\t";
}
*/
