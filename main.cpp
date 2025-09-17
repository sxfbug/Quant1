#include <iostream> // ����������ߣ����� cout (������ӡ��Ϣ)
#include <fstream>  // �ļ��������ߣ����� ifstream (������ȡ�ļ�)
#include <sstream>  // �ַ����������ߣ����� stringstream (�����з��ַ���)
#include <vector>   // �������ߣ����� vector (������ܶ�������)
#include <string>   // �ַ�������
#include <unordered_map> //��ϣ��
#include "func_declare.hpp"//��������



int main() {
	std::string filename = "Data/AAPLcsv_version.csv";
	std::vector<DailyInfo> data;
	data = load_data_from_csv(filename);
	
	std::string yieldsname = "Data/us_treasury_yields_daily_csv.csv";
	std::vector<US_Treasury_Yields> yields;
	yields = load_yields_from_csv(yieldsname);

	
	int days = 252;
	double norisk = 13.21 / 100;
	double base = 10000.0;
	double handle = 0.0;

	Dual_MA_Strategy_full(data, 5, 20, base, handle, days, norisk);
	Dual_MA_Strategy_full(data, 10, 50, base, handle, days, norisk);
	Dual_MA_Strategy_full(data, 50, 200, base, handle, days, norisk);
	Dual_MA_Strategy_full(data, 100, 500, base, handle, days, norisk);
    
}

/*
for (const auto& i : close) {
	std::cout << i << "\t";
}
*/
