#ifndef FUNCTION
#define FUNCTION
#include<vector>

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




//��ȡcsv��vector
std::vector<DailyInfo>load_from_csv(const std::string& filename);

std::vector<double>get_sum_close(const std::vector<DailyInfo>& data);
std::vector<double>get_MA(const std::vector<double>& close, int y);
std::vector<TradeAct> Strategy1(const std::vector<double>& shortMA, const std::vector<double>& longMA,
	const std::vector<DailyInfo> data);
//ģ�⽻�ף�Ҳ�лز⣿
std::vector<Account> simulated_trading(const std::vector<TradeAct>& act,
	const std::vector<DailyInfo>& data, double base, double handling_Fees = 0.0);

//����ָ��
double total_return(const std::vector<Account>& sum, double base);
double annualized_rate_of_return(const std::vector<Account>& sum, double base);
double max_drawdown(const std::vector<Account>& sum);

#endif // !FUNCTION
