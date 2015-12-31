/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * Copyright © 2015
 * Quality and Usability Lab
 * Berlin Institute of Technology
 * http://www.qu.tu-berlin.de
 *
 * For more detailed information, please read the license.txt in the root directory.
 */

//JUCE Lib
#include "../JuceLibraryCode/JuceHeader.h"

//C++ Libs
#include <memory>

//Own Libs
#include <src/GUI/head_frame/network_gui_component.h>
//#include <src/controller.h>
#include <src/GUI/gui_components_configurator.h>
#include <src/controller.h>
SSR::Network_gui_component::Network_gui_component(Controller* controller)
: AudioProcessorEditor(controller)
, connected_button(new juce::TextButton("connected_button"))
, is_connected(false)
{
  addAndMakeVisible(*connected_button);

  SSR::configure_text_button(*connected_button, "Connected");
  connected_button->addListener(this);
  connected_button->setBounds(0, 0, 138, 25);

  setSize(138, 26);
}

SSR::Network_gui_component::~Network_gui_component()
{
  removeAllChildren();
}

void SSR::Network_gui_component::set_connected(const bool connected)
{
  is_connected = connected;
  connected_button->setToggleState(is_connected, juce::dontSendNotification);
}

bool SSR::Network_gui_component::get_connected() const
{
  return is_connected;
}

void SSR::Network_gui_component::buttonClicked(Button* button)
{

  if (button == connected_button.get()) {
      Controller* processor = getProcessor();

      if (!is_connected) {
          processor->connect();
      }

      is_connected = processor->is_connected_to_ssr();

      connected_button->setToggleState(is_connected, juce::dontSendNotification);
  }

}
