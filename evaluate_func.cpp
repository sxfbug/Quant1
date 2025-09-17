#include <iostream> // ����������ߣ����� cout (������ӡ��Ϣ)
#include <fstream>  // �ļ��������ߣ����� ifstream (������ȡ�ļ�)
#include <sstream>  // �ַ����������ߣ����� stringstream (�����з��ַ���)
#include <vector>   // �������ߣ����� vector (������ܶ�������)
#include <string>   // �ַ�������
#include <iomanip> //��ٷֱ�
#include <cmath> //�������ָ��
#include"func_declare.hpp"

//������Ч

//�������������
//�������ݣ��������ʣ��껯�����ʣ����س����������ʣ�
// �������ʱ�׼��껯�����ʣ����ձ���
//�������˻�vector��double��ĳ�ʼ�ʽ�int����꽻�����������޷�������
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
//��������
double total_return(const std::vector<Account>& sum, double base) {
	double ratio = (sum[sum.size() - 1].total_value - base) / base;
	//std::cout << std::fixed << std::setprecision(5) << ratio << "%" << std::endl;
	return ratio;
}

//�껯������
double annualized_rate_of_return(const std::vector<Account>& sum, double base) {
	double times = sum[sum.size() - 1].total_value / base;
	int start_year = std::stoi(sum[0].date.substr(sum[0].date.rfind("/") + 1, 4));
	int end_year = std::stoi(sum[sum.size() - 1].date.substr(sum[sum.size() - 1].date.rfind("/") + 1, 4));
	double annual_rate = std::pow(times, 1.0 / (end_year - start_year)) - 1;

	return annual_rate;
}


//���س�
//���룺�˻�vector��ÿ������
//���أ�double��ʽ�����س�ֵ
//�ۼƾ�ֵ��ȡ�˻����ʲ�
double max_drawdown(const std::vector<Account>& sum) {
	double peak = -1.0;
	double min_drawdown = 0.0;
	double current_drawdown = -1.0;
	for (auto i = sum.begin(); i != sum.end(); i++) {
		//�ж��Ƿ���·�ֵ
		if (i->total_value > peak) {
			//���·�ֵ
			peak = i->total_value;
		}
		//�ж��Ƿ�������س�
		current_drawdown = (i->total_value - peak) / peak;
		if (current_drawdown < min_drawdown) {
			min_drawdown = current_drawdown;
		}


	}
	return min_drawdown;
}



//��������	
//�������˻� vector
//�������������vector
std::vector<double> daily_rate_of_return(const std::vector<Account>& sum) {
	std::vector<double> rate;
	//���������������
	for (int i = 1; i < sum.size(); i++)
	{
		rate.push_back((sum[i].total_value - sum[i - 1].total_value) / sum[i - 1].total_value);
	}
	return rate;
}

//�����ʵı�׼��
//��������������vector
//����������ʱ�׼��vector
//��׼��� = ��[��(r? - ��)? / (n-1)]
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


//�껯������
// ������double��׼�int����������
// ���أ�double
double annualized_volatility(double& st, int& days) {
	return st * std::sqrt(double(days));
}


//���ձ���
double sharpe_rate(double& annualized_rate_of_return,
	double& norisk, double& annualized_volatility) {
	return (annualized_rate_of_return - norisk) / annualized_volatility;
}