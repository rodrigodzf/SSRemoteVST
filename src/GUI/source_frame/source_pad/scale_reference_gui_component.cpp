#include <src/GUI/source_frame/source_pad/scale_reference_gui_component.h>

//C++ Libs
#include <string>
#include <sstream>
#include <iomanip>

//JUCE Include
#include <JuceLibraryCode/JuceHeader.h>

SSR::Scale_reference_GUI_component::Scale_reference_GUI_component(unsigned int reference_pixels, double reference_range)
: reference_pixels(reference_pixels)
, reference_range(reference_range)
, reference_bar_size(30.0f)
, current_reference(0.0f)
{
  compute_current_reference();

  setSize(100, 12);
}

SSR::Scale_reference_GUI_component::~Scale_reference_GUI_component()
{

}

void SSR::Scale_reference_GUI_component::paint(Graphics& graphics)
{
  graphics.setColour(juce::Colours::black);
  graphics.drawVerticalLine(0, 0, getHeight() - 1);
  graphics.drawVerticalLine(reference_bar_size, 0, getHeight() - 1.0f);
  graphics.drawHorizontalLine(getHeight() - 1, 0, reference_bar_size);

  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2) << current_reference;

  std::string text = oss.str() + std::string(" m");

  graphics.drawSingleLineText(text, reference_bar_size + 5.0f, getHeight() - 1.0f);
}

void SSR::Scale_reference_GUI_component::set_reference_range(const double new_reference_range)
{
  reference_range = new_reference_range;
  compute_current_reference();
  repaint();
}

void SSR::Scale_reference_GUI_component::compute_current_reference()
{
  current_reference = reference_range / reference_pixels * reference_bar_size;
}