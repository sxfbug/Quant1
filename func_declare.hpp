#ifndef FUNCTION
#define FUNCTION
#include<vector>

//粒度为日的历史数据
struct DailyInfo
{
	std::string date;//日期
	double open;//开盘价
	double high;//最高价
	double low;//最低价
	double close;//收盘价
	double adj_close;//调整后收盘价
	long long int volume;//成交量
};

//交易行为合集
struct TradeAct
{
	int idx;
	std::string date;//日期
	enum action //交易行为
	{
		BUY,
		SELL,
		HOLD,
	}action;
	double close; //当日收盘价

};

//账户结构体
struct Account
{
	std::string date;//日期
	double cash;//现金数
	double shares=0.0;//持有股数
	double total_value;//总资产=cash+shares*close(daily)


};




//提取csv到vector
std::vector<DailyInfo>load_from_csv(const std::string& filename);

std::vector<double>get_sum_close(const std::vector<DailyInfo>& data);
std::vector<double>get_MA(const std::vector<double>& close, int y);
std::vector<TradeAct> Strategy1(const std::vector<double>& shortMA, const std::vector<double>& longMA,
	const std::vector<DailyInfo> data);
//模拟交易，也叫回测？
std::vector<Account> simulated_trading(const std::vector<TradeAct>& act,
	const std::vector<DailyInfo>& data, double base, double handling_Fees = 0.0);

//评估指标
double total_return(const std::vector<Account>& sum, double base);
double annualized_rate_of_return(const std::vector<Account>& sum, double base);
double max_drawdown(const std::vector<Account>& sum);

#endif // !FUNCTION
