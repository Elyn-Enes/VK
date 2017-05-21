#pragma once

#include <chrono>

using namespace std::chrono;

class Time {

	public:

		Time( ) {
			this->now = high_resolution_clock::now();
		};

		unsigned int getDelta() {
			auto delta_time = std::chrono::high_resolution_clock::now() - this->now;
			this->now = std::chrono::high_resolution_clock::now();
			return delta_time.count();
		}

	protected:
	private:
		std::chrono::time_point<std::chrono::steady_clock> now;
		std::chrono::duration<long long, std::nano> lag;


};

 