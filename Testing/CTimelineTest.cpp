#include "pch.h"
#include "CppUnitTest.h"
#include "Timeline.h"
#include "AnimChannelAngle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CTimelineTest)
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
		TEST_METHOD(TestCTimelineNumFrames)
		{
			CTimeline timeline;

			// numFrames getter and setter

			Assert::AreEqual(timeline.GetNumFrames(), 300);
			// setter
			timeline.SetNumFrames(44);
			Assert::AreEqual(timeline.GetNumFrames(), 44);

		}

		TEST_METHOD(TestCTimelineFrameRate)
		{
			CTimeline timeline;

			// numFrames getter and setter

			Assert::AreEqual(timeline.GetFrameRate(), 30);
			// setter
			timeline.SetFrameRate(60);
			Assert::AreEqual(timeline.GetFrameRate(), 60);

		}
		TEST_METHOD(TestCTimelineCurrentTime)
		{
			CTimeline timeline;

			// numFrames getter and setter

			Assert::AreEqual(timeline.GetCurrentTime(), 0, 0.00001);
			// setter
			timeline.SetCurrentTime(30.32444);
			Assert::AreEqual(timeline.GetCurrentTime(), 30.32444, 0.000001);

		}
		TEST_METHOD(TestCTimelineGetDuration)
		{
			CTimeline timeline;

			// Default value
			Assert::AreEqual(10, timeline.GetDuration(), 0.0001);

			// Changed duration
			timeline.SetFrameRate(375);
			Assert::AreEqual(300.0 / 375.0, timeline.GetDuration(), 0.0001);

			timeline.SetNumFrames(789);
			Assert::AreEqual(789.0 / 375.0, timeline.GetDuration(), 0.0001);
		}

		TEST_METHOD(TestCTimelineGetCurrentFrame)
		{
			CTimeline timeline;

			// Default value
			Assert::AreEqual(0, timeline.GetCurrentFrame());

			// Changed time
			timeline.SetCurrentTime(9.27);
			Assert::AreEqual(278, timeline.GetCurrentFrame());
		}

		TEST_METHOD(TestCTimelineAdd)
		{
			CTimeline timeline;
			CAnimChannelAngle channel;

			timeline.AddChannel(&channel);
			Assert::IsTrue(&timeline == channel.GetTimeline());
		}
		
	};
}