#ifndef FUNCTION
#define FUNCTION
#include<vector>
#include <string>

//����Ϊ�յ���ʷ����
struct DailyInfo
{
	std::string date;//����
	double open;//���̼�
	double high;//��߼�
	double low;//��ͼ�
	double close;//���̼�
	double adj_close;//���������̼�
	long long int volume;//�ɽ���
};

//������ծ������
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

//������Ϊ�ϼ�
struct TradeAct
{
	int idx;
	std::string date;//����
	enum action //������Ϊ
	{
		BUY,
		SELL,
		HOLD,
	}action;
	double close; //�������̼�

};

//�˻��ṹ��
struct Account
{
	std::string date;//����
	double cash;//�ֽ���
	double shares=0.0;//���й���
	double total_value;//���ʲ�=cash+shares*close(daily)


};


//support function

//��ȡcsv��vector
std::vector<DailyInfo>load_data_from_csv(const std::string& filename);
std::vector<US_Treasury_Yields>load_yields_from_csv(const std::string& filename);
double sup_stod(std::string x);

//outoput csv
void output_account_csv(std::vector<Account>& sum, std::vector<TradeAct>& act,
    int short_days, int long_days);
//financial indicators function
std::vector<double>get_sum_close(const std::vector<DailyInfo>& data);
std::vector<double>get_MA(const std::vector<DailyInfo>& close, int y);
//strategy function
std::vector<TradeAct> Dual_MA_Strategy(int& short_days, int& long_days,
	const std::vector<DailyInfo>& data);


//stimulated trading function
std::vector<Account> full_position(const std::vector<TradeAct>& act,
	const std::vector<DailyInfo>& data, double base, double handling_Fees = 0.0);

//evaluate function
void evaluate_func(const std::vector<Account>& sum, double base,
	int days, double norisk);

double total_return(const std::vector<Account>& sum, double base);
double annualized_rate_of_return(const std::vector<Account>& sum, double base);
double max_drawdown(const std::vector<Account>& sum);
std::vector<double> daily_rate_of_return(const std::vector<Account>& sum);
double standard_deviation(const std::vector<double>& daily);
double annualized_volatility(double& st, int& days);
double sharpe_rate(double& annualized_rate_of_return,
	double& norisk, double& annualized_volatility);



//comprehensive strategy function
int Dual_MA_Strategy_full(const std::vector<DailyInfo>& data, int short_days,
	int long_days, double base, double handling_Fees, int days, double norisk
);

#endif // !FUNCTION
