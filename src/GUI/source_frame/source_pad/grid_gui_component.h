#ifndef GRID_GUI_COMPONENT_H
#define GRID_GUI_COMPONENT_H

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

//C++ Libs
#include <memory>

//JUCE Lib
#include <JuceHeader.h>

namespace SSR
{

  /**
   * This class is a grid GUI component representing a grind with a X and Y
   * axis where the point (0/0) is in the center. The Class provides the
   * following methods:
   *
   * - paint method for drawing the component
   * - get_rect method returning the rectangle defining the grids dimensions
   */
  class Grid_gui_component : public juce::Component
  {

  public:

    /**
     * Constructor awaits the transfer parameters width and height which
     * determine the dimensions of the grid.
     *
     * @param           width           The width of the component.
     * @param           height          The height of the component.
     */
    Grid_gui_component(unsigned int width, unsigned int height);

    /**
     * Destructor.
     */
    ~Grid_gui_component();

    /**
     * Draws the grid.
     *
     * JUCE Dok:
     *
     * <i>[...]
     *
     * The paint() method gets called when a region of a component needs
     * redrawing, either because the component's repaint() method has been called,
     * or because something has happened on the screen that means a section of a
     * window needs to be redrawn.
     *
     * [...]
     *
     * You should never need to call this method directly - [...]</i>
     *
     * @param           graphics        the graphics context that must be used to
     *                                  do the drawing operations.
     */
    virtual void paint(Graphics& graphics) override;

    /**
     * Returns the rectangle defining the grids dimensions.
     *
     * @return the rectangle defining the grids dimensions.
     */
    const juce::Rectangle<int> get_rect() const;

  private:

    /**
     * This method draws the background of the grid GUI component.
     *
     * @param           graphics        The graphics context that must be used to
     *                                  do the drawing operations.
     */
    void draw_background(Graphics& graphics);

    /**
     * This method draws the borders of the grid GUI component.
     *
     * @param           graphics        The graphics context that must be used to
     *                                  do the drawing operations.
     */
    void draw_border(Graphics& graphics);

    /**
     * This method draws the axes of the grid GUI component.
     *
     * @param           graphics        The graphics context that must be used to
     *                                  do the drawing operations.
     */
    void draw_axes(Graphics& graphics);

  private:

    /**
     * The width of the grid GUI component.
     */
    const unsigned int width;

    /**
     * The height of the grid GUI component.
     */
    const unsigned int height;

    /**
     * Rectangle representing the grids dimensions.
     */
    std::unique_ptr<const juce::Rectangle<int> > rect;

  };

}

#endif
