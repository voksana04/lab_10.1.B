#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\admin\source\repos\Project_10.1.В\Project_10.1.В\lab_10.1.b.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestCalculateHighAveragePercentage)
        {
            // Тестові дані
            Student students[4] = {
                { "Вишинська", 1, KN, 5, 5, 5 },  
                { "Пащук", 2, INF, 4, 4, 4 },
                { "Булик", 3, ME, 5, 5, 5 },
                { "Астапович", 4, TN, 3, 3, 3 }
            };

            double result = CalculateHighAveragePercentage(students, 4);
            Assert::AreEqual(50.0, result, 0.01, L"Test failed: Очікувалося 50.0%");
        }

        
    };
}
