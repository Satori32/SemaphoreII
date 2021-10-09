#include <iostream>
#include <mutex>
#include <functional>
#include <future>
#include <thread>
#include <chrono>
#include <random>

template<class R>
R Semaphore(const std::function<R(void)>& F) {
	static std::mutex M;
	std::lock_guard<std::mutex> L(M);
	return F();
}/**/
template<class R>
R Semaphore(const std::function<R(void)>& F,std::mutex M) {
//	static std::mutex M;
	std::lock_guard<std::mutex> L(M);
	return F();
}
/**/
int main() {
	std::mutex M;
	std::mt19937 Rnd;
	std::uniform_int_distribution<> U(-3, 3);
	/** /
	for (std::size_t i = 0; i < 128; i++) {
	auto F = [i]()->bool {std::cout << i << std::endl; return true; };
	Semaphore<bool>(F);
	}
	/**/
	for (std::size_t i = 0; i < 12800; i++) {
		auto F = [i]()->bool {std::cout << i << std::endl; return true; };
		//	Semaphore<bool>(F);
		//	auto FU = std::async(std::launch::async, [F]() {return Semaphore(F); });//why not...
	//	auto FU = std::async(std::launch::async, [](auto F) {Semaphore<bool>(F); 	std::this_thread::sleep_for(std::chrono::nanoseconds(3)); return true; }, F);
		//	auto FU = std::async(std::launch::async, [i]() {std::cout << i << std::endl; });//why not...
		//	auto FU = std::async(std::launch::async, [](auto i) {std::cout << i << std::endl; },i);//why not...
		auto FU = std::async(std::launch::async, [](auto F,auto R) {Semaphore<bool>(F); 	std::this_thread::sleep_for(std::chrono::milliseconds(R)); return true; }, F,U(Rnd));
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
	return 0;
}