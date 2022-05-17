#include "pch.h"
#include "CppUnitTest.h"
#include <stdbool.h>
#include "../stateMachine2/states.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestCase1) //if state connected, expected connected
		{
			bool connected = true;
			bool lightStatus = false;
			bool morseStatus = false;
			bool randomLightPattern = false;
			std::string State = stateMachine2(connected, lightStatus, morseStatus, randomLightPattern);
			
			std::string connect = "Connected";
			Assert::AreEqual(connect, State);
		}
		TEST_METHOD(TestCase2) //if state disconnected, expected disconnected
		{
			bool connected = false;
			bool lightStatus = false;
			bool morseStatus = false;
			bool randomLightPattern = false;
			std::string State = stateMachine2(connected, lightStatus, morseStatus, randomLightPattern);

			std::string disconnect = "Disconnected";
			Assert::AreEqual(disconnect, State);
		}
		TEST_METHOD(TestCase3) //if lights on and no connection, expected Disconnected
		{
			bool connected = false;
			bool lightStatus = true;
			bool morseStatus = false;
			bool randomLightPattern = false;
			std::string State = stateMachine2(connected, lightStatus, morseStatus, randomLightPattern);

			std::string disconnect = "Disconnected";
			Assert::AreEqual(disconnect, State);
		}
		TEST_METHOD(TestCase4) //if lights on and connection, expected Lights on
		{
			bool connected = true;
			bool lightStatus = true;
			bool morseStatus = false;
			bool randomLightPattern = false;
			std::string State = stateMachine2(connected, lightStatus, morseStatus, randomLightPattern);

			std::string ledsOn = "LedsOn";
			Assert::AreEqual(ledsOn, State);
		}
		TEST_METHOD(TestCase5) //if connection, lights on and morse, expected morse
		{
			bool connected = true;
			bool lightStatus = true;
			bool morseStatus = true;
			bool randomLightPattern = false;
			std::string State = stateMachine2(connected, lightStatus, morseStatus, randomLightPattern);

			std::string morse = "Morse";
			Assert::AreEqual(morse, State);
		}
		TEST_METHOD(TestCase6) //if connected and morse, expected morse
		{
			bool connected = true;
			bool lightStatus = false;
			bool morseStatus = true;
			bool randomLightPattern = false;
			std::string State = stateMachine2(connected, lightStatus, morseStatus, randomLightPattern);

			std::string morse = "Morse";
			Assert::AreEqual(morse, State);
		}
		TEST_METHOD(TestCase7) //if lights on and morse, expected disconnected
		{
			bool connected = false;
			bool lightStatus = true;
			bool morseStatus = true;
			bool randomLightPattern = false;
			std::string State = stateMachine2(connected, lightStatus, morseStatus, randomLightPattern);

			std::string disconnect = "Disconnected";
			Assert::AreEqual(disconnect, State);
		}		
		TEST_METHOD(TestCase8)
		{
			bool connected = false;
			bool lightStatus = false;
			bool morseStatus = true;
			bool randomLightPattern = false;
			std::string State = stateMachine2(connected, lightStatus, morseStatus, randomLightPattern);

			std::string disconnect = "Disconnected";
			Assert::AreEqual(disconnect, State);
		}
		TEST_METHOD(TestCase9)
		{
			bool connected = true;
			bool lightStatus = true;
			bool morseStatus = false;
			bool randomLightPattern = true;
			std::string State = stateMachine2(connected, lightStatus, morseStatus, randomLightPattern);

			std::string disconnect = "Random";
			Assert::AreEqual(disconnect, State);
		}
		TEST_METHOD(TestCase10) //sanity check, testing framework
		{
			Assert::IsTrue(true);
		}
		TEST_METHOD(TestCase11) //sanity check, testing framework
		{
			Assert::IsFalse(false);
			
		}
	};
}
