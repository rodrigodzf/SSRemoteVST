//
//  head_gui_component.cpp
//  SSRRemote_FromScratch
//
//  Created by Rodrigo Diaz on 12/28/15.
//
//

#include "head_gui_component.h"

//Own Libs
#include <src/config/ssr_colour.h>

SSR::Head_gui_component::Head_gui_component()
: radius(20.0f)
{
    setSize(40.0f, 40.0f);
}

SSR::Head_gui_component::Head_gui_component(const unsigned int width_and_height)
: radius(width_and_height / 2.0f)
{
    setSize(width_and_height, width_and_height);
}

SSR::Head_gui_component::~Head_gui_component()
{
    
}

float SSR::Head_gui_component::get_radius() const
{
    return radius;
}

void SSR::Head_gui_component::paint(Graphics& graphics)
{
    draw_background(graphics);
}

void SSR::Head_gui_component::draw_background(juce::Graphics& graphics)
{
    graphics.setColour(SSR::colour::get_colour(SSR::colour::Colours::black));
//    graphics.fillEllipse(0.0f, 0.0f, getWidth(), getHeight());
    
//    graphics.setColour(SSR::colour::get_colour(SSR::colour::Colours::purple));
    
//    Line<<#typename ValueType#>>(<#ValueType startX#>, <#ValueType startY#>, <#ValueType endX#>, <#ValueType endY#>)
//    Line<float> *line = new Line<float>();
//    graphics.drawLine(<#float startX#>, <#float startY#>, <#float endX#>, <#float endY#>, <#float lineThickness#>)
//    graphics.drawLine(-1.0f, -1.0f, getWidth(), getHeight(), 10.0f);
//    graphics.drawArrow(<#const Line<float> &line#>, <#float lineThickness#>, <#float arrowheadWidth#>, <#float arrowheadLength#>)
    
    graphics.drawArrow(*new Line<float>(getWidth()/2,getHeight(),getWidth()/2,0.0f), 0.0f, 20.0f, 40.0f);
//    graphics.drawEllipse(2.0f, 2.0f, getWidth() - 4.0f, getHeight() - 4.0f, 3.0f);
}
