#include "InteractionTableTest.h"

using namespace godot;

void InteractionTableTest::_register_methods()
{
	register_method("_ready", &InteractionTableTest::_ready);
}

void InteractionTableTest::_ready()
{
	Godot::print("test");
	testGetInteractionsNumber();
}

void InteractionTableTest::testGetInteractionsNumber()
{
	int interactionsNumber;

	Godot::print("Tests when adding interactions");

	Godot::print("Test with 0 interactions");
	interactionsNumber = 0;
	ASSERT_EQ(interactionsNumber, getInteractionsNumber());
	Godot::print("Test passed");

	Godot::print("Test with 1 interactions");
	interactionsNumber = 1;
	m_vBox->add_child(Node2D::_new());
	ASSERT_EQ(interactionsNumber, getInteractionsNumber());
	Godot::print("Test passed");

	Godot::print("Test with 2 interactions");
	interactionsNumber = 2;
	m_vBox->add_child(Node2D::_new());
	ASSERT_EQ(interactionsNumber, getInteractionsNumber());
	Godot::print("Test passed");

	Godot::print("Test with 3 interactions");
	interactionsNumber = 3;
	m_vBox->add_child(Node2D::_new());
	ASSERT_EQ(interactionsNumber, getInteractionsNumber());
	Godot::print("Test passed");

	Godot::print("Test with 13 interactions");
	interactionsNumber = 13;
	for (int i = 0; i < 10; i++)
		m_vBox->add_child(Node2D::_new());
	ASSERT_EQ(interactionsNumber, getInteractionsNumber());
	Godot::print("Test passed");


	Godot::print("Test when removing interactions");

	Godot::print("Test with 0 interactions");
	interactionsNumber = 0;
	Array children = m_vBox->get_children();
	for (int i = 0; i < children.size(); i++) {
		Node* child = children[i];
		child->free();
	}
	ASSERT_EQ(interactionsNumber, getInteractionsNumber());
	Godot::print("Test passed");
}

InteractionTableTest::InteractionTableTest()
{
}

InteractionTableTest::~InteractionTableTest()
{
}

void InteractionTableTest::_init()
{
}