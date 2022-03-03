#include "pch.h"
#include<memory>
#include "CppUnitTest.h"
#include "PictureObserver.h"
#include "Picture.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	class CPictureObserverMock : public CPictureObserver
	{
	public:
		CPictureObserverMock() : CPictureObserver() {}
		bool mUpdated = false;
		virtual void UpdateObserver() override { mUpdated = true; }

	};

	TEST_CLASS(CPictureObserverTest)
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
		TEST_METHOD(TestCPictureObserverConstruct)
		{
			CPictureObserverMock observer;
		}
		TEST_METHOD(TestCPictureObserverOneObserver)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Create a mock observer object
			CPictureObserverMock observer;

			// And set it for the observer:
			observer.SetPicture(picture);

			picture->UpdateObservers();

			Assert::IsTrue(observer.mUpdated);
		}
		TEST_METHOD(TestCPictureObserverGetPicture)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Create a mock observer object
			CPictureObserverMock observer;

			// And set it for the observer:
			observer.SetPicture(picture);

			// Test Get picture
			Assert::IsTrue(observer.GetPicture() == picture);

		}
		TEST_METHOD(TestCPictureObserverTwoObservers)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Create a mock observer object
			CPictureObserverMock observer1;

			// Create a mock observer object
			CPictureObserverMock observer2;

			// And set it for the observer:
			observer1.SetPicture(picture);

			// And set it for the observer:
			observer2.SetPicture(picture);

			picture->UpdateObservers();

			Assert::IsTrue(observer1.mUpdated);

			Assert::IsTrue(observer2.mUpdated);
		}
		TEST_METHOD(TestCPictureObserverDestroyed)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();
			
			// Create a mock observer object
			CPictureObserverMock observer1;

			// And set it for the observer:
			observer1.SetPicture(picture);

			{
				CPictureObserverMock observer2;

				// And set it for the observer:
				observer2.SetPicture(picture);
			}
			// After deletetion check if the other oberver works 
			picture->UpdateObservers();

			Assert::IsTrue(observer1.mUpdated);

		}


	};
}