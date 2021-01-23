#include "Interaction.h"
#include "../ui/dialog_box/DialogBox.h"

/**
 * The interaction type : "Examine"
 *		Display a dialog box and play the sound (voice) associated with it
 */
class ExamineInteraction : public Interaction {

	GODOT_CLASS(ExamineInteraction, godot::TextureButton);	//To make godot able to use this class

public:

	ExamineInteraction();
	~ExamineInteraction();

	/**
	 * Register the methods that godot is directly going to use
	 */
	static void _register_methods();
	void _init();	//Needed by godot

	/**
	 * Initialise the class and the scene
	 */
	void _ready();
	
	/**
	 * Display the dialog box and the play the sound
	 */
	virtual void play();

	/**
	 * Play the interaction
	 */
	void on_button_released();



	/* PROPERTIES */

	godot::String m_examineText;	//Text that will be displayed in the dialog box
	void setExamineText(godot::String newText);
	godot::String getExamineText();

protected:
	DialogBox* m_dialogBox;
};