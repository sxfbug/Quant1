#include <iostream> // 输入输出工具，比如 cout (用来打印信息)
#include <fstream>  // 文件操作工具，比如 ifstream (用来读取文件)
#include <sstream>  // 字符串处理工具，比如 stringstream (用来切分字符串)
#include <vector>   // 容器工具，比如 vector (用来存很多条数据)
#include <string>   // 字符串工具
#include<iomanip > //求百分比
#include<cmath> //计算金融指标
#include"func_declare.hpp"

//评估绩效

//总评估函数入口
//包含内容：总收益率，年化收益率，最大回撤，日收益率，
// 日收益率标准差，年化波动率，夏普比率
//参数：账户vector，double类的初始资金，int类的年交易日数量，无风险利率
void evaluate_func(const std::vector<Account>& sum, double base, 
	  int days,double norisk) {
	double ret = total_return(sum, base);
	std::cout << "total return: " << ret << "\n";

	double rate = annualized_rate_of_return(sum, base);
	std::cout << "annual rate: " << rate << "\n";

	double md = max_drawdown(sum);
	std::cout << "max drawdown: " << md << "\n";

	std::vector<double> daily_return = daily_rate_of_return(sum);
	//std::cout << "nums of daily return:" << daily_return.size() << "\n";
	double st = standard_deviation(daily_return);
	double an_vo = annualized_volatility(st, days);

	
	double sharpe = sharpe_rate(rate, norisk, an_vo);
	std::cout << "sharpe rate: " << sharpe << "\n";
}
//总收益率
double total_return(const std::vector<Account>& sum, double base) {
	double ratio = (sum[sum.size() - 1].total_value - base) / base;
	//std::cout << std::fixed << std::setprecision(5) << ratio << "%" << std::endl;
	return ratio;
}

//年化收益率
double annualized_rate_of_return(const std::vector<Account>& sum, double base) {
	double times = sum[sum.size() - 1].total_value / base;
	int start_year = std::stoi(sum[0].date.substr(sum[0].date.rfind("/") + 1, 4));
	int end_year = std::stoi(sum[sum.size() - 1].date.substr(sum[sum.size() - 1].date.rfind("/") + 1, 4));
	double annual_rate = std::pow(times, 1.0 / (end_year - start_year)) - 1;

	return annual_rate;
}


//最大回撤
//输入：账户vector，每日数据
//返回：double格式的最大回撤值
//累计净值采取账户总资产
double max_drawdown(const std::vector<Account>& sum) {
	double peak = -1.0;
	double min_drawdown = 0.0;
	double current_drawdown = -1.0;
	for (auto i = sum.begin(); i != sum.end(); i++) {
		//判断是否更新峰值
		if (i->total_value > peak) {
			//更新峰值
			peak = i->total_value;
		}
		//判断是否更新最大回撤
		current_drawdown = (i->total_value - peak) / peak;
		if (current_drawdown < min_drawdown) {
			min_drawdown = current_drawdown;
		}


	}
	return min_drawdown;
}



//日收益率	
//参数：账户 vector
//输出：日收益率vector
std::vector<double> daily_rate_of_return(const std::vector<Account>& sum) {
	std::vector<double> rate;
	//计算后续的收益率
	for (int i = 1; i < sum.size(); i++)
	{
		rate.push_back((sum[i].total_value - sum[i - 1].total_value) / sum[i - 1].total_value);
	}
	return rate;
}

//收益率的标准差
//参数：日收益率vector
//输出：收益率标准差vector
//标准差σ = √[Σ(r? - μ)? / (n-1)]
double standard_deviation(const std::vector<double>& daily) {
	int num = daily.size();
	double ave = 0.0;
	for (const auto& i : daily) {
		ave += i;
	}
	ave /= num;
	double squared_sum = 0.0;
	for (const auto& i : daily) {
		squared_sum += std::pow(i - ave, 2);
	}
	squared_sum = std::sqrt(squared_sum / (num - 1));
	return squared_sum;
}


//年化波动率
// 参数：double标准差，int交易日期数
// 返回：double
double annualized_volatility(double& st, int& days) {
	return st * std::sqrt(double(days));
}


//夏普比率
double sharpe_rate(double& annualized_rate_of_return,
	double& norisk, double& annualized_volatility) {
	return (annualized_rate_of_return - norisk) / annualized_volatility;
}