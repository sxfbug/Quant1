#include <iostream> // 输入输出工具，比如 cout (用来打印信息)
#include <fstream>  // 文件操作工具，比如 ifstream (用来读取文件)
#include <sstream>  // 字符串处理工具，比如 stringstream (用来切分字符串)
#include <vector>   // 容器工具，比如 vector (用来存很多条数据)
#include <string>   // 字符串工具
#include<iomanip > //求百分比
#include<cmath> //计算金融指标
#include"func_declare.hpp"












//模拟交易
//参数：交易行为vector，数据集，初始资产，手续费
//返回：账户的vector
std::vector<Account> simulated_trading(const std::vector<TradeAct>& act, 
	const std::vector<DailyInfo>& data,double base,double handling_Fees) {
	std::vector<Account> sum;
	Account item;
	item.cash = base;

	//遍历交易行为
	int test = 0;
	for (int i = 0;i<act.size();i++) {
		
		if (act[i].date != data[i].date) {
			std::cout << "日期不匹配"<<test<<"\n";
			test++;
		}
		item.date = data[i].date;
		if (act[i].action == TradeAct::action::BUY) {
			item.shares = item.cash / data[i].close;
			item.cash = 0.0;
		}
		else if(act[i].action == TradeAct::action::SELL){
			item.cash = data[i].close * item.shares;
			item.shares = 0.0;
			//手续费
			item.cash -= handling_Fees * item.cash;
		}
		
		item.total_value = item.cash + item.shares * data[i].close;
		sum.push_back(item);
	}
	return sum;
}


