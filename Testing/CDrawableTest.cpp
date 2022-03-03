#include "pch.h"
#include "CppUnitTest.h"
#include "Drawable.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;

namespace Testing
{
	class CDrawableMock : public CDrawable
	{
	public:
		CDrawableMock(const std::wstring& name) : CDrawable(name) {}

		virtual void Draw(Gdiplus::Graphics* graphics) override {}
		virtual bool HitTest(Gdiplus::Point pos) override { return false; }

	};



	TEST_CLASS(CDrawableTest)
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

		TEST_METHOD(TestCDrawableConstructor)
		{
			CDrawableMock drawn(L"test");
			Assert::AreEqual(std::wstring(L"test"), drawn.GetName());
		}
		TEST_METHOD(TestCDrawablePositionGetterSetter)
		{
			CDrawableMock drawn(L"test");
			// test default position
			Assert::AreEqual(0, drawn.GetPosition().X);
			Assert::AreEqual(0, drawn.GetPosition().Y);
			
			// test getter and setter
			drawn.SetPosition(Point(54,52));
			Assert::AreEqual(54, drawn.GetPosition().X);
			Assert::AreEqual(52, drawn.GetPosition().Y);

		}
		TEST_METHOD(TestCDrawableRotationGetterSetter)
		{
			CDrawableMock drawn(L"test");
			// test default position
			Assert::AreEqual(0, drawn.GetRotation(), 0.00001);
			
			// test getter and setter
			drawn.SetRotation(.333);
			Assert::AreEqual(.333, drawn.GetRotation());
			double b = acos(cos(drawn.GetRotation()));
			Assert::AreEqual(drawn.GetRotation(), b, 0.000000001);

		}
		TEST_METHOD(TestCDrawableAssociation)
		{
			CDrawableMock body(L"Body");
			auto arm = std::make_shared<CDrawableMock>(L"Arm");
			auto leg = std::make_shared<CDrawableMock>(L"Leg");

			Assert::IsNull(arm->GetParent());
			Assert::IsNull(leg->GetParent());

			body.AddChild(arm);
			body.AddChild(leg);

			Assert::IsTrue(arm->GetParent() == &body);
			Assert::IsTrue(leg->GetParent() == &body);
		}


	};
}