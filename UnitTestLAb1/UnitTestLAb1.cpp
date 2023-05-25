#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab1smp(pattern)\lab1smp(pattern).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab1
{
	TEST_CLASS(UnitTestLab1)
	{
	public:

		TEST_METHOD(TestWizardHandlerWithValidInput)
		{
			Handler* handler = new WizardHandler;
			string result = handler->Handle("Staff");

			
			Assert::AreEqual(string("Wizard: I will protect your back with this Staff.\n"), result);
		}

		TEST_METHOD(TestKnightHandlerWithInvalidInput)
		{
			Handler* handler = new KnightHandler;
			string result = handler->Handle("Axe");

			
			Assert::AreEqual(string(""), result);
		}

		TEST_METHOD(TestArcherHandlerWithValidInput)
		{
			Handler* handler = new ArcherHandler;
			string result = handler->Handle("Crossbow");

			
			Assert::AreEqual(string("Archer: I will snipe anybody for you with this Crossbow.\n"), result);
		}

		TEST_METHOD(TestAssassinHandlerWithValidInput)
		{
			Handler* handler = new AssassinHandler;
			string result = handler->Handle("Crossbow");

			
			Assert::AreEqual(string(""), result);
		}

		TEST_METHOD(TestFullChainOfHandlers)
		{
			Handler* wizard = new WizardHandler;
			Handler* assassin = new AssassinHandler;
			Handler* warrior = new KnightHandler;
			Handler* archer = new ArcherHandler;
			wizard->SetNext(assassin)->SetNext(warrior)->SetNext(archer);

			string result = wizard->Handle("Bow");

			
			Assert::AreEqual(string("Archer: I will snipe anybody for you with this Bow.\n"), result);
		}

		TEST_METHOD(TestEmptyChainOfHandlers)
		{
			Handler* handler = new AbstractHandler;
			string result = handler->Handle("Sword");

			
			Assert::AreEqual(string(""), result);
		}

	};
}
