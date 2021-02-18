#include "OpenInteraction.h"

using namespace godot;

void OpenInteraction::_register_methods()
{
	register_method("_ready", &OpenInteraction::_ready);
	register_method("on_searchPlaceCloseButton_released", &OpenInteraction::on_searchPlaceCloseButton_released);
	register_method("on_dialogBoxHiding", &OpenInteraction::on_dialogBoxHiding);
	register_method("on_examineInteraction_finished", &OpenInteraction::on_examineInteraction_finished);
	register_method("on_background_fadeOut_finished", &OpenInteraction::on_background_fadeOut_finished);

	register_property<OpenInteraction, Ref<PackedScene>>("Search place scene", &OpenInteraction::setSearchPlaceScene,
		&OpenInteraction::getSearchPlaceScene, Ref<PackedScene>());
	register_property<OpenInteraction, String>("Search place scene's name", &OpenInteraction::setSearchPlaceSceneName,
		&OpenInteraction::getSearchPlaceSceneName, "Set a name");
}

void OpenInteraction::_ready()
{
	//Get children
	m_searchPlaceBackground = get_node("CanvasLayer/FadeBackground")->cast_to<FadeBackground>
		(get_node("CanvasLayer/FadeBackground"));

	//Scene initialisation

	//Get the specific search place packed scene
	get_node("CanvasLayer")->add_child(m_searchPlaceScene->instance());
	const NodePath pathToSearchPlace = NodePath("CanvasLayer/" + m_searchPlaceSceneName);
	m_searchPlace = get_node(pathToSearchPlace)->cast_to<SearchPlace>(get_node(pathToSearchPlace));

	m_searchPlaceBackground->setFadeDuration(m_searchPlace->getAnimationDuration());

	// Signals initialisation
	m_searchPlace->getCloseButton()->connect("button_up", this, "on_searchPlaceCloseButton_released");
	m_dialogBox->getBeforeHideTimer()->connect("timeout", this, "on_dialogBoxHiding");
	m_searchPlaceBackground->connect("fadeOut_finished", this, "on_background_fadeOut_finished");
	ExamineInteraction::connect("interaction_finished", this, "on_examineInteraction_finished");
	add_user_signal("openInteraction_just_played");
	add_user_signal("openInteraction_finished");
}

void OpenInteraction::play()
{
	ExamineInteraction::play();
	emit_signal("openInteraction_just_played");

	if (!m_searchPlaceBackground->isDisplayed()) {
		m_searchPlace->setIsOpen(true);
		m_searchPlace->display();
		m_searchPlace->getCloseButton()->set_disabled(true);
		m_searchPlaceBackground->fadeIn();
		m_searchPlaceBackground->set_mouse_filter(Control::MOUSE_FILTER_STOP);
	}
}

void OpenInteraction::on_searchPlaceCloseButton_released()
{
	m_searchPlaceBackground->fadeOut();
	m_searchPlaceBackground->set_mouse_filter(Control::MOUSE_FILTER_IGNORE);
	m_searchPlace->setIsOpen(false);
	emit_signal("interaction_finished");
}

void OpenInteraction::on_dialogBoxHiding()
{
	m_searchPlace->getCloseButton()->set_disabled(false);
}

void OpenInteraction::on_examineInteraction_finished()
{
	if (m_searchPlaceBackground->get_mouse_filter() == Control::MOUSE_FILTER_STOP)
		emit_signal("interaction_just_played");
}

void OpenInteraction::on_background_fadeOut_finished()
{
	emit_signal("openInteraction_finished");
}

void OpenInteraction::setSearchPlaceScene(const godot::Ref<godot::PackedScene> newSearchPlaceScene)
{
	m_searchPlaceScene = newSearchPlaceScene;
}

godot::Ref<godot::PackedScene> OpenInteraction::getSearchPlaceScene() const
{
	return m_searchPlaceScene;
}

void OpenInteraction::setSearchPlaceSceneName(const godot::String newName)
{
	m_searchPlaceSceneName = newName;
}

godot::String OpenInteraction::getSearchPlaceSceneName() const
{
	return m_searchPlaceSceneName;
}

OpenInteraction::OpenInteraction()
{
	m_searchPlace = nullptr;
	m_searchPlaceBackground = nullptr;
}

OpenInteraction::~OpenInteraction()
{
}

void OpenInteraction::_init()
{
}
