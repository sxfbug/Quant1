#include <iostream> // 输入输出工具，比如 cout (用来打印信息)
#include <fstream>  // 文件操作工具，比如 ifstream (用来读取文件)
#include <sstream>  // 字符串处理工具，比如 stringstream (用来切分字符串)
#include <vector>   // 容器工具，比如 vector (用来存很多条数据)
#include <string>   // 字符串工具
#include<iomanip > //求百分比
#include<cmath> //计算金融指标
#include"func_declare.hpp"

//策略：双均线策略，金叉买入，死叉卖出
//参数：int类的短期MA天数，int类的长期MA天数，dailyinfo类的数据集data
//返回：交易行为vector
std::vector<TradeAct> Dual_MA_Strategy(	int& short_days,int& long_days,
	const std::vector<DailyInfo>& data) {
	//计算短期和长期MA
	std::vector<double>shortMA;
	std::vector<double>longMA;

	shortMA = get_MA(data, short_days);
	longMA = get_MA(data, long_days);

	//交易行为vector
	std::vector<TradeAct> act;

	//状态变量，判断当前持仓状态。不需要hold，因为hold is not actionable
	bool isHolding = false;
	int idx = 0;

	//没有长期均线，不满足比较条件
	while (longMA[idx] == 0)
	{
		TradeAct item;

		item.date = data[idx].date;
		item.close = data[idx].close;
		item.action = TradeAct::HOLD;
		act.push_back(item);
		idx++;
	}



	for (int i = idx; i < longMA.size(); i++) {

		TradeAct item;
		//短期均线向上突破长期均线，形成金叉，且未持有时买入
		if (shortMA[i] > longMA[i] && shortMA[i - 1] <= longMA[i - 1] && !isHolding) {

			item.date = data[i].date;
			item.close = data[i].close;
			item.action = TradeAct::BUY;
			act.push_back(item);
			isHolding = true;
		}
		//短期均线向下突破长期均线，形成死叉，且持有时卖出
		else if (shortMA[i] < longMA[i] && shortMA[i - 1] >= longMA[i - 1] && isHolding) {
			item.date = data[i].date;
			item.close = data[i].close;
			item.action = TradeAct::SELL;
			act.push_back(item);
			isHolding = false;
		}
		else {
			item.date = data[i].date;
			item.close = data[i].close;
			item.action = TradeAct::HOLD;
			act.push_back(item);
		}



	}
	return act;
}
