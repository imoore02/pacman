#ifndef UNITTEST_H
#define UNITTEST_H
#include "main.h"

class UnitTest {
	public:
		UnitTest();
		void timeTest(std::chrono::seconds elapsedTime);
		void testScore(int score);
};

#endif