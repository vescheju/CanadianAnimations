#include "pch.h"
#include "CppUnitTest.h"
#include "AnimChannelAngle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CAnimChannelAngleTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestNothing)
		{
			// This is an empty test just to ensure the system is working
		}
		TEST_METHOD(TestCAnimChannelAngleGettersAndSetters)
		{
			CAnimChannelAngle chan;
			chan.SetName(L"Channel1");
			
			Assert::AreEqual(chan.GetName(), wstring(L"Channel1"));

		}
	};
}