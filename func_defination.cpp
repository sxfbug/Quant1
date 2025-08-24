#include <iostream> // 输入输出工具，比如 cout (用来打印信息)
#include <fstream>  // 文件操作工具，比如 ifstream (用来读取文件)
#include <sstream>  // 字符串处理工具，比如 stringstream (用来切分字符串)
#include <vector>   // 容器工具，比如 vector (用来存很多条数据)
#include <string>   // 字符串工具
#include<iomanip > //求百分比
#include<cmath> //计算金融指标
#include"func_declare.hpp"



//
std::vector<DailyInfo>load_from_csv(const std::string& filename) {
	std::vector<DailyInfo> dataset;

	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cout << "错误：无法打开文件！路径可能不正确：" << filename << std::endl;
		return dataset; // 返回空vector
	}
	//读取第一行并丢弃
	std::string line;//创建一个string类型的临时变量line
	std::getline(file, line);//把第一行内容读取到line中

	//循环读取直到末尾
	while (std::getline(file, line)) {
		DailyInfo item;
		//当不是末尾时，line里有东西，把line交给ss
		//stringstream能像操作文件流一样操作字符串，
		// 方便我们按分隔符（这里是逗号）分割字符串，
		// 相当于把一行文本变成一个 “可切割的数据源”
		std::stringstream ss(line);
		std::string token;
		// 4.3 开始“切菜”！按逗号分割字符串
		// 格式是：日期,开盘价,最高价,最低价,收盘价,成交量
		std::getline(ss, item.date, ',');    // 第一刀：切下日期，放到卡片的date栏
		std::getline(ss, token, ',');        // 第二刀：切下一个字符串（开盘价），先放到临时 token 里
		item.open = std::stod(token);        //         把这个字符串转换成 double 数字，再放到卡片的open栏

		std::getline(ss, token, ',');        // 第三刀：切下（最高价）
		item.high = std::stod(token);        //         转换后放入 high

		std::getline(ss, token, ',');        // 第四刀：切下（最低价）
		item.low = std::stod(token);         //         转换后放入 low

		std::getline(ss, token, ',');        // 第五刀：切下（收盘价）
		item.close = std::stod(token);       //         转换后放入 close

		std::getline(ss, token, ',');        // 第六刀：切下（成交量）
		item.volume = std::stoll(token);     //         转换成 long long 数字，放入 volume

		// 4.4 这张卡片填好了，把它放进袋子里！
		dataset.push_back(item);
	}

	// 5. 点名结束，关闭花名册，返回装满卡片的袋子
	file.close();
	return dataset;
	}



//计算所有的收盘价
//参数：数据集
//输出：double的vector
std::vector<double>get_sum_close(const std::vector<DailyInfo>& data) {
	std::vector<double> sum;
	for (const auto& d : data) {
		sum.push_back(d.close);
	}
	return sum;
}

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
	for (int i = y+1; i < close.size(); i++) {
		sum = sum - close[i - y] + close[i];
		MA.push_back(sum/y);
		if (i == 10407) {
			std::cout << i << std::endl;
		}
	}
	return MA;
}


//策略：金叉买入，死叉卖出
//参数：shortMA,longMA，数据集?
//返回：交易行为vector
std::vector<TradeAct> Strategy1(const std::vector<double>& shortMA, const std::vector<double>& longMA,
	const std::vector<DailyInfo> data) {

	//交易行为vector
	std::vector<TradeAct> act;
	
	//状态变量，判断当前持仓状态。不需要hold，因为hold is not actionable
	bool isHolding = false;
	int idx = 0;

	//没有长期均线，不满足比较条件
	while (longMA[idx]==0)
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

//评估绩效

//总收益率
double total_return(const std::vector<Account>&sum,double base) {
	double ratio = (sum[sum.size() - 1].total_value - base) / base;
	std::cout << std::fixed << std::setprecision(5) << ratio << "%" << std::endl;
	return ratio;
}

//年化收益率
double annualized_rate_of_return(const std::vector<Account>&sum, double base) {
	double times = sum[sum.size() - 1].total_value / base;
	int start_year = std::stoi(sum[0].date.substr(sum[0].date.rfind("/") + 1, 4));
	int end_year= std::stoi(sum[sum.size() - 1].date.substr(sum[sum.size() - 1].date.rfind("/") + 1, 4));
	double annual_rate = std::pow(times, 1.0 / (end_year-start_year)) - 1;

	return annual_rate;
}


//最大回撤
//输入：账户vector，每日数据
//返回：double格式的最大回撤值
//累计净值采取账户总资产
double max_drawdown(const std::vector<Account> &sum) {
	double peak = -1.0;
	double min_drawdown = 0.0;
	double current_drawdown = -1.0;
	for (auto i=sum.begin();i!=sum.end();i++) {
		//判断是否更新峰值
		if (i->total_value > peak) {
			//更新峰值
			peak = i->total_value;
		}
		//判断是否更新最大回撤
		current_drawdown= (i->total_value - peak) / peak;
		if (current_drawdown < min_drawdown) {
			min_drawdown = current_drawdown;
		}
		

	}
	return min_drawdown;
}



