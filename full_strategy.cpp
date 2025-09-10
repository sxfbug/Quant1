#include <iostream> // 输入输出工具，比如 cout (用来打印信息)
#include <sstream>  // 字符串处理工具，比如 stringstream (用来切分字符串)
#include <vector>   // 容器工具，比如 vector (用来存很多条数据)
#include <string>   // 字符串工具
#include<iomanip > //求百分比
#include<cmath> //计算金融指标
#include"func_declare.hpp"

//包含策略、回测、评估的高封装度策略函数

//双均线策略，全仓交易
int Dual_MA_Strategy_full(const std::vector<DailyInfo>& data,int short_days, 
	int long_days, double base, double handling_Fees,int days,double norisk
	) {
	std::vector <TradeAct>act= Dual_MA_Strategy(short_days,long_days,data);
	std::vector<Account> account = full_position(act, data, base,handling_Fees);
	std::cout << "\nshortMA: " << short_days << "\nlongMA: " << long_days << "\n";
;	evaluate_func(account, base, days, norisk);
    output_account_csv(account, act,short_days,long_days);
return 0;
}