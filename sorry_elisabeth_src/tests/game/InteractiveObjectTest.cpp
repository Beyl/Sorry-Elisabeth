#include "InteractiveObjectTest.h"

using namespace godot;

void InteractiveObjectTest::_register_methods()
{
	register_method("_ready", &InteractiveObjectTest::_ready);
}

void InteractiveObjectTest::_ready()
{
	testOfferInteractions();
}

void InteractiveObjectTest::testOfferInteractions()
{
	Godot::print("Test with multiple interactions (so it does offer)");
	ASSERT_TRUE(InteractiveObject::offerInteractions());
	Godot::print("Test passed");

	Godot::print("Test with 0 interactions (so it does not offer)");
	m_interactionTable->setInteractions(godot::Array());
	m_interactionTable->addInteractionsToScene();
	ASSERT_FALSE(InteractiveObject::offerInteractions());
	Godot::print("Test passed");
}

InteractiveObjectTest::InteractiveObjectTest()
{
}

InteractiveObjectTest::~InteractiveObjectTest()
{
}

void InteractiveObjectTest::_init()
{
}