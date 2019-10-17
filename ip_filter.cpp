#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <tuple>
#include <algorithm>


using ip_addr = std::vector<int>;
using ip_pool = std::multiset<ip_addr, std::greater<>>;
// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	auto stop = str.find_first_of(d);
		
	while (stop != std::string::npos)
	{
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

void print_ip_addr(const ip_addr& ip) {
	std::cout << ip[0] << "." <<
		ip[1] << "." <<
		ip[2] << "." <<
		ip[3] << std::endl;
}

/*
bool comp_ip_addr(const ip_addr& a, int n) {
	return (a[0] == n);
}

bool comp_ip_addr(const ip_addr& a, int n, int m) {
	return (a[0] == n && a[1] == m);
}

template <typename...Args>
void filter(const ip_pool& pool, Args...args) {
	for (auto it : pool) {
		if (comp_ip_addr(it, args...)) {
			print_ip_addr(it);
		}
	}
}
*/

template <typename...Args>
void filter(const ip_pool& pool, Args...args) {
	ip_addr temp = {args...};
	for (auto it : pool) {
		if (std::equal(it.begin(), it.begin() + (sizeof...(args)), temp.begin())) {
			print_ip_addr(it);
		}
	}
}

void filter_any(const ip_pool& pool, int a) {
	for (auto it : pool) {
		if (std::any_of(it.begin(), it.end(), [a=a](auto vec) {return vec == a; })) {
			print_ip_addr(it);
		}
	}
}


int main(int argc, char const *argv[])
{
	//ââîä äàííûõ èç ôàéëà âî âðåìÿ îòëàäêè
	std::ifstream test_in;
	test_in.open("C:/Users/Evgeniy/source/repos/HomeWork1_2/ip_filter_3.tsv");
	
		try
		{
			ip_pool ip_pool; //ñòðêóòóðà äàííûõ, ñîäåðæàùàÿ ip-àäðåñà â ïîðÿäêå óáûâàíèÿ.

			for (std::string line; std::getline(test_in, line);)  //èçìåíèòü test_in íà std::cin
			{
				auto v1 = std::move(split(line, '\t'));
				auto v2 = std::move(split(v1.at(0), '.'));
			 
			//	int o = std::stoi(v2[0]);
			//	int two = std::stoi(v2[1]);
			//	int three = std::stoi(v2[2]);
			//	int four = std::stoi(v2[3]);
			//ip_addr temp{ (std::stoi(v2[0]), std::stoi(v2[1]), std::stoi(v2[2]), std::stoi(v2[3])) };
				ip_pool.emplace(ip_addr{ std::stoi(v2[0]), std::stoi(v2[1]), std::stoi(v2[2]), std::stoi(v2[3])});
			}

			// TODO reverse lexicographically sort
/*
			for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
			{
				print_ip_addr(*ip);
			}
			*/

			for (auto ip : ip_pool)
			{
				print_ip_addr(ip);
			}

		
			// TODO filter by first byte and output
			// ip = filter(1)
			filter(ip_pool, 1);

			
			// TODO filter by first and second bytes and output
			// ip = filter(46, 70)
			filter(ip_pool, 46, 70);
			

			// TODO filter by any byte and output
			// ip = filter_any(46)
			filter_any(ip_pool, 46);

			
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	
    return 0;
}

