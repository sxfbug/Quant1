#ifndef FUNCTION
#define FUNCTION
#include<vector>
#include <string>

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

//美国国债收益率
struct US_Treasury_Yields
{
	std::string date;
	double m1;
	double m3;
	double m6;
	double y1;
	double y2;
	double y3;
	double y5;
	double y7;
	double y10;
	double y20;
	double y30;
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


//support function

//提取csv到vector
std::vector<DailyInfo>load_data_from_csv(const std::string& filename);
std::vector<US_Treasury_Yields>load_yields_from_csv(const std::string& filename);
double sup_stod(std::string x);

//financial indicators function
std::vector<double>get_sum_close(const std::vector<DailyInfo>& data);
std::vector<double>get_MA(const std::vector<double>& close, int y);

//strategy function
std::vector<TradeAct> Strategy1(const std::vector<double>& shortMA, const std::vector<double>& longMA,
	const std::vector<DailyInfo> data);


//stimulated trading function
std::vector<Account> simulated_trading(const std::vector<TradeAct>& act,
	const std::vector<DailyInfo>& data, double base, double handling_Fees = 0.0);

//evaluate function
double total_return(const std::vector<Account>& sum, double base);
double annualized_rate_of_return(const std::vector<Account>& sum, double base);
double max_drawdown(const std::vector<Account>& sum);
std::vector<double> daily_rate_of_return(const std::vector<Account>& sum);
double standard_deviation(const std::vector<double>& daily);
double annualized_volatility(double& st, int& days);
double sharpe_rate(double& annualized_rate_of_return,
	double& norisk, double& annualized_volatility);


#endif // !FUNCTION
