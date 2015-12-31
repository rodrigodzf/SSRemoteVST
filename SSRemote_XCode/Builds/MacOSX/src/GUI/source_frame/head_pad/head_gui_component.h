//
//  head_gui_component.hpp
//  SSRRemote_FromScratch
//
//  Created by Rodrigo Diaz on 12/28/15.
//
//

#ifndef head_gui_component_hpp
#define head_gui_component_hpp

#include <stdio.h>

//JUCE Lib
#include "../JuceLibraryCode/JuceHeader.h"

//C++ Libs
#include <memory>

namespace SSR
{
    
    /**
     * This class represents the Source GUI Component.
     *
     * The Source GUI Component is graphically represented as a triangle similar
     * to the source GUI component in the SSR.
     */
    class Head_gui_component
    : public juce::Component
    {
        
    public:
        
        /**
         * Constructor initialising the radius with 20.0. Sets the size of the
         * component to 40x40 pixels.
         */
        Head_gui_component();
        
        /**
         * Constructor initialising the radio with width_and_height / 2. Sets the
         * size of the component to width_and_height x width_and_height pixels.
         *
         * @param   width_and_height        The width and height of the GUI
         *                                  component.
         */
        Head_gui_component(const unsigned int width_and_height);
        
        /**
         * Destructor.
         */
        ~Head_gui_component();
        
        /**
         * Draws the component.
         *
         * For more information on this method please read the JUCE documentaion:
         *
         * http://learn.juce.com/doc/classComponent.php#a7cf1862f4af5909ea72827898114a182
         *
         * @see http://learn.juce.com/doc/classComponent.php#a7cf1862f4af5909ea72827898114a182
         *
         * @param   graphics        The graphics context that must be used to do
         *                          the drawing operations.
         */
        void paint(juce::Graphics& graphics) override;
        
        /**
         * Returns the radius of the source.
         */
        float get_radius() const;
        
    private:
        
        /**
         * Draws the background of the component.
         */
        void draw_background(juce::Graphics& graphics);
        
    private:
        
        /**
         * Radius of the circle (representing the source).
         */
        float radius;
        
    };
    
    
}


#endif /* head_gui_component_hpp */
