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
	testSetTableSize();
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

void InteractionTableTest::testSetTableSize()
{
	Vector2 testSize;

	/* !! There's no need to test the size if there is less than 1 interaction,
		because if that's the case, it is not displayed !! */

	Godot::print("Test with 1 interaction in the table");
	testSize = Vector2(get_size().x, 16);
	m_vBox->add_child(Node2D::_new());
	setTableSize();
	ASSERT_EQ(get_size().x, testSize.x);
	ASSERT_EQ(get_size().y, testSize.y);
	Godot::print("Test passed");

	Godot::print("Test with 2 interactions in the table");
	testSize = Vector2(get_size().x, 28);
	m_vBox->add_child(Node2D::_new());
	setTableSize();
	ASSERT_EQ(get_size().x, testSize.x);
	ASSERT_EQ(get_size().y, testSize.y);
	Godot::print("Test passed");


	Godot::print("Test with 3 interactions in the table");
	testSize = Vector2(get_size().x, 40);
	m_vBox->add_child(Node2D::_new());
	setTableSize();
	ASSERT_EQ(get_size().x, testSize.x);
	ASSERT_EQ(get_size().y, testSize.y);
	Godot::print("Test passed");

	Godot::print("Test with 10 interactions in the table");
	testSize = Vector2(get_size().x, 124);
	for (int i = 0; i < 7; i++)
		m_vBox->add_child(Node2D::_new());
	setTableSize();
	ASSERT_EQ(get_size().x, testSize.x);
	ASSERT_EQ(get_size().y, testSize.y);
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