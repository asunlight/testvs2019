//单向无环图最长路径

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<tuple>
#include<map>
using namespace std;
map<int, tuple<int, bool>> cachmap;

void Split(const std::string& src, const std::string& separator, std::vector<int>& dest) //字符串分割到数组
{

	//参数1：要分割的字符串；参数2：作为分隔符的字符；参数3：存放分割后的字符串的vector向量

	string str = src;
	string substring;
	string::size_type start = 0, index;
	dest.clear();
	index = str.find_first_of(separator, start);
	do
	{
		if (index != string::npos)
		{
			substring = str.substr(start, index - start);
			dest.push_back(stoi(substring));
			start = index + separator.size();
			index = str.find(separator, start);
			if (start == string::npos) break;
		}
	} while (index != string::npos);

	//the last part
	substring = str.substr(start);
	dest.push_back(stoi(substring));
}



void initial(vector<vector<int>>& dga, int n)
{
	dga.clear();
	vector<int> temp;
	for (int i = 0; i < n; i++)
		temp.push_back(-1);
	for (int i = 0; i < n; i++)
		dga.push_back(temp);
}

std::tuple<int, bool> longestp(vector<vector<int>>& dga, int i)//0到节点i是否有链接，距离
{
	if (i == 0)//可以连接到0，距离为0
		return make_tuple<int, bool>(0, true);
	if (i == -1)//连接不到
		return make_tuple<int, bool>(0, false);
	auto it = cachmap.find(i);
	if (it != cachmap.end())//已经算过了
		return it->second;


	tuple<int, bool> maxn{ 0,false };

	for (int k = 0; k < dga.size(); k++)
	{
		tuple<int, bool> tmtp{ 0,false };
		if (dga[k][i] != -1)//k到i是否有连接
		{
			tmtp = longestp(dga, k);//k到0是否有链接，距离多少
			if (get<1>(tmtp))//有连接
			{
				get<0>(tmtp)++;
				//get<0>(tm)++;
			}
		}
		if (get<1>(tmtp) && get<0>(tmtp) > get<0>(maxn))//有连接，且比现有最长连接长
			maxn = tmtp;
	}

	cachmap[i] = maxn;
	return maxn;
}


int main()
{
	vector<vector<int>> dga;
	int n;
	string s;
	cin >> n;
	vector<int> vin;
	while (n != 0)
	{
		initial(dga, n);
		cachmap.clear();
		std::getline(cin, s);
		for (int i = 0; i < n; i++)
		{
			std::getline(cin, s);
			if (s.size() == 0)//此行没有输入
				continue;
			Split(s, " ", vin);//解析成int数组
			for (const auto& it : vin)
				if (i != it)//自己到自己的肯定没有
					dga[i][it] = 1;

		}

		int maxl = 0;
		tuple<int, bool> tm = { 0,false };
		for (int i = 0; i < n; i++)
		{
			tm = longestp(dga, i);
			if (get<1>(tm) && get<0>(tm) > maxl)
				maxl = get<0>(tm);
		}
		std::cout << maxl << endl;
		cin >> n;
	}

	return 0;
}




// testvs2019.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include <iostream>
//#include<vector>
//#include<string>
//#include"json.hpp"
//
//using namespace std;
//using json = nlohmann::json;
//
//int main()
//{
//    vector<string> vs = {"孙文光","李蕊"};
//    for (auto it : vs)
//        cout << it << endl;
//    json j;
//    j["list"] = vs;
//    cout << j << endl;
//
//
//    std::cout << "Hello World!\n";
//}

/*
#include<iostream>
#include<tuple>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

void splitStr(string s, char c, vector<string>& vs)//字符串分割函数
{
	auto it1=s.find_first_of(c);
	auto it2 = s.find_last_of(c);
	vs.push_back(s.substr(0,it1));
	vs.push_back(s.substr(it1+1,it2-it1-1));
	vs.push_back(s.substr(it2+1, s.size() - it2));

}
int main()
{
	vector<tuple<string, string, string, int>> vtSongs;//数组中每个元素分别存放，源字符串、歌名、作者、时长
	string strTemp;//用来存储每一行的歌曲输入
	int k;
	char t;
	cin >> k;//接收k
	cin >> t;//接受分割符

	vector<string> vs;//用来存储分割后的歌曲信息

	//接受歌曲信息输入，每输入一个，解析一个，然后存进去
	while (cin >> strTemp)
	{
		vs.clear();//每次都要清空
		splitStr(strTemp, '&', vs);//分割
		vtSongs.emplace_back(tuple< string, string, string, int>(strTemp, vs[0], vs[1], stoi(vs[2])));//存储
	}

	//按照指定规则排序
	sort(vtSongs.begin(), vtSongs.end(), [](const tuple< string, string, string, int>& tp1, const tuple< string, string, string, int>& tp2) {
		if (get<3>(tp1) > get<3>(tp2))
			return true;
		else if (get<3>(tp1) == get<3>(tp2))
		{
			if (get<1>(tp1) < get<1>(tp2))
				return true;
			else if (get<1>(tp1) == get<1>(tp2))
			{
				if (get<2>(tp1) <= get<2>(tp2))
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;

		});

	//根据指定的k输出
	if (k >= 0 && k <= vtSongs.size())
	{
		for (int i = 0; i < k; i++)
			cout << get<0>(vtSongs[i]) << endl;
	}
	else
	{
		cout << "error!!!" << endl;
	}
}



*/


//
//#include<iostream>
//#include<math.h>
//#include<vector>
//#include<memory>
//using namespace std;
//
//struct StNode {
//	int num;
//	StNode* lf, * rt;
//	StNode(int n) {
//		num = n;
//		lf = nullptr;
//		rt = nullptr;
//	}
//
//};
//
//class BTree {
//public:
//	StNode *root;
//public:
//	BTree()
//	{
//		root = nullptr;
//	}
//
//	~BTree()
//	{
//		ReleaseNode(root);
//		
//	}
//
//	void ReleaseNode(StNode* node)
//	{
//		if (node == nullptr)
//			return;
//		if (node->lf != nullptr)
//		{
//			ReleaseNode(node->lf);
//		}
//
//		if (node->rt != nullptr)
//		{
//			ReleaseNode(node->rt);
//		}
//		delete node;
//
//	}
//
//	bool isBalanced(StNode* node) {
//		int left_height;
//		int right_height;
//		if (node == nullptr)
//			return true;
//		left_height = height(node->lf);
//		right_height = height(node->rt);
//		if (abs(left_height - right_height) <= 1
//			&& isBalanced(node->lf)
//			&& isBalanced(node->rt))
//			return true;
//		return false;
//	}
//	static int  height(StNode* node)
//	{
//		if (node == nullptr)
//			return 0;
//		return 1 + max(height(node->lf), height(node->rt));
//	}
//};
//
//
//
//
//
//
//int main()
//{
//	
//	int n, r_index;
//	while (cin >> n>>r_index)
//	{
//		BTree* tree = new BTree();
//		int temp;
//		vector<StNode*> vNodes;
//		for (int i = 0; i < n; i++) {
//			StNode *pNode = new StNode(i);
//			vNodes.push_back(pNode);
//		}
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < n; j++) {
//				int edge;
//				cin>> edge;
//				if (edge == 1) {
//					StNode *pchild = vNodes.at(j);
//					StNode *pparent = vNodes.at(i);
//					if (pparent->lf != nullptr) {
//						pparent->rt = pchild;
//					}
//					else {
//						pparent->lf = pchild;
//					}
//				}
//			}
//		}
//		tree->root = vNodes.at(r_index);
//		if (tree->isBalanced(tree->root))
//			cout<< tree->height(tree->root) - 1 << " True"<<endl;
//		else
//			cout<< tree->height(tree->root) - 1 <<" False"<<endl;
//		delete tree;
//	}
//
//	return 0;
//}








// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
