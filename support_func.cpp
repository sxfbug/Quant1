#include <iostream> // 输入输出工具，比如 cout (用来打印信息)
#include <fstream>  // 文件操作工具，比如 ifstream (用来读取文件)
#include <sstream>  // 字符串处理工具，比如 stringstream (用来切分字符串)
#include <vector>   // 容器工具，比如 vector (用来存很多条数据)
#include <string>   // 字符串工具
#include<iomanip > //求百分比
#include<cmath> //计算金融指标
#include"func_declare.hpp"


//辅助函数：读取国债时遇到空字符串，手动置为0
double sup_stod(std::string x) {
	if (x == "") {
		return 0.0;
	}
	else {
		return std::stod(x);
	}
}

//从csv中获取数据
std::vector<DailyInfo>load_data_from_csv(const std::string& filename) {
	std::vector<DailyInfo> dataset;

	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cout << "错误：无法打开数据csv文件！路径可能不正确：" << filename << std::endl;
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


//从csv中获取美国国债
std::vector<US_Treasury_Yields>load_yields_from_csv(const std::string& filename) {
	std::vector<US_Treasury_Yields> dataset;

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "错误：无法打开国债收益率csv文件！路径可能不正确：" << filename << std::endl;
		return dataset; // 返回空vector
	}

	//读取第一行并丢弃
	std::string line;//创建一个string类型的临时变量line
	std::getline(file, line);//把第一行内容读取到line中

	while (std::getline(file, line)) {
		US_Treasury_Yields item;

		std::stringstream ss(line);
		std::string token;

		std::getline(ss, item.date, ','); //日期

		std::getline(ss, token, ',');        // 第二刀：切下一个字符串，先放到临时 token 里
		item.m1 = sup_stod(token);

		std::getline(ss, token, ',');
		item.m3 = sup_stod(token);

		std::getline(ss, token, ',');
		item.m6 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y1 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y2 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y3 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y5 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y7 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y10 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y20 = sup_stod(token);

		std::getline(ss, token, ',');
		item.y30 = sup_stod(token);

		dataset.push_back(item);
	}


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

//选择无风险利率（夏普比率），选择数据第一天的10年期美国国债利率
//参数：第一天的日期字符串，国债利率vector
//返回：double类的利率，如果返回-1则为没找到对应日期的利率
double choose_norisk_rate(std::string finddate, std::vector<US_Treasury_Yields>& yields) {
	for (const auto& i : yields) {
		if (i.date == finddate) {
			return i.y10;
		}
	}
}

//输出账户为csv
//输入：账户vector，交易行为vector，两个MA的参数
//输出：无，但是会创建一个csv
void output_account_csv(std::vector<Account>& sum,std::vector<TradeAct>& act,
    int short_days,int long_days) {
    std::string filename = "Data/Analysis/backtest_result_" + std::to_string(short_days) + "and" + std::to_string(long_days)+".csv";
	std::ofstream output(filename);
	output << "date,total_value,action,price\n";
    for (size_t i = 0; i < sum.size(); ++i) {
        output << sum[i].date << ","
            << sum[i].total_value << ","
            << (i < act.size() ? static_cast<int>(act[i].action) : -1) << ","
            << (i < act.size() ? act[i].close : 0) << "\n";
    }
    output.close();


}
