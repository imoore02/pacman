#include "UnitTest.h"
#include <iostream>

UnitTest::UnitTest()
{
	
}


void UnitTest::timeTest(std::chrono::seconds elapsedTime)
{
	std::cout << "Elapsed Time: " << elapsedTime.count() << " seconds" << std::endl;
}

void UnitTest::testScore(int score){
	std::cout << "Score: " << score << std::endl;
}