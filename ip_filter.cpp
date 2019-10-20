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
using ip_pool_reverse = std::multiset<ip_addr, std::greater<>>;
using ip_pool = std::multiset<ip_addr>;
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
	std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << std::endl;
}

template <typename...Args>
void filter(const ip_pool& pool, Args...args) {
	ip_addr temp = { args... };
	auto it_start = std::upper_bound(pool.begin(), pool.end(), temp);
		if (it_start == pool.end()) { return; }
	auto it_finish = std::upper_bound(it_start, pool.end(), temp,
		[](auto b, auto a) {return !(std::equal(a.begin(), a.begin() + sizeof...(args), b.begin())); });
	ip_pool_reverse temp_pool(it_start, it_finish);
	for (auto it : temp_pool) {
		print_ip_addr(it);
	}
}

void filter_any(const ip_pool& pool, int a) {
	for (auto ip = pool.rbegin(); ip != pool.rend(); ++ip) {
		if (std::any_of(ip->begin(), ip->end(), [a=a](auto vec) {return vec == a; })) {	print_ip_addr(*ip);	}
	}
}

int main([[maybe_unused]]int argc, char const *argv[])
{
		
		try
		{
			ip_pool ip_pool; 
      
			for (std::string line; std::getline(std::cin, line);)  
			{
				auto v1 = std::move(split(line, '\t'));
				auto v2 = std::move(split(v1.at(0), '.'));
			 	ip_pool.emplace(ip_addr{ std::stoi(v2[0]), std::stoi(v2[1]), std::stoi(v2[2]), std::stoi(v2[3])});
			}

			// TODO reverse lexicographically sort

			for (auto ip = ip_pool.rbegin(); ip != ip_pool.rend(); ++ip)
			{
				print_ip_addr(*ip);
			}
						
			// TODO filter by first byte and output
			// ip = filter(1)
			filter(ip_pool, 1);

			
			// TODO filter by first and second bytes and output
			// ip = filter(46, 70)
			filter(ip_pool, 46, 70);
			

			// TODO filter by any byte and output
			//ip = filter_any(46);
		   filter_any(ip_pool, 46);

		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
    return 0;
}


