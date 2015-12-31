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

#include <src/scene/scene.h>

//C++ Libs
#include <memory>
#include <vector>
#include <algorithm>

//Own Libs
#include <src/scene/source.h>
#include <src/parameter/parameter.h>
#include <src/utils/logger.h>
#include <src/scene/parameter_translation_functions.h>


//JUCE Lib
#include "../JuceLibraryCode/JuceHeader.h"

typedef std::vector<SSR::Source>::iterator source_iterator;

SSR::Scene::Scene(float scene_range)
: sources(new std::vector<SSR::Source>())
, ids_and_names(new std::vector< std::pair<unsigned int, std::string> >())
, scene_range(scene_range)
, current_selected_source()
, reference_orientation(  0.0f,
               0.0f,
               SSR::translations::orientation_discrete_to_continuous,
               SSR::translations::orientation_continuous_to_discrete,
               "Reference Orientation")

{
SSR::Logger::get_instance()->log(SSR::Logger::Level::INFO, "Scene wac created!", false);

  new_source("Default Source");
}

SSR::Scene::~Scene()
{

}

bool SSR::Scene::write_xml(){
    
    bool ret;
//    XmlElement(<#juce::XmlElement &&#>)
    
    return ret;

}


void SSR::Scene::interpret_xml_message(std::string xml_message)
{
    
    XmlDocument xml_document(xml_message);
    auto main_element = std::unique_ptr<juce::XmlElement>(xml_document.getDocumentElement());
    
    // TODO: bug in update!
    if (main_element->hasTagName("update")) {
        
        forEachXmlChildElement (*main_element, e) {
            
            if (e->hasTagName("source")) {
                
                if (e->hasAttribute("id")) {
                    
                    int id = e->getIntAttribute("id");
                    
                    if (id_already_in_use(id)) {
                        
                        manipulate_source(get_iterator(id), e);
                        
                    } else {
                        
                        if (e->hasAttribute("name")) {
                            
                            std::string name = e->getStringAttribute("name").toStdString();
                            sources->push_back(SSR::Source(id, name, scene_range));
                            ids_and_names->push_back( std::pair<unsigned int, std::string>(id, name) );
                            current_selected_source = sources->begin();
                            
                            manipulate_source(get_iterator(id), e);
                            
                        }
                        
                    }
                    
                }
                
            }
            
            if (e->hasTagName("reference")){
                
                forEachXmlChildElement(*e, f) {
                    
                    if (f->hasTagName("orientation")) {
                        
                        
                        reference_orientation.set_discrete_value(static_cast<float>(f->getDoubleAttribute("azimuth")));
//                        std::cout << f->getDoubleAttribute("azimuth") << std::endl;
                    }
                    
                }
            }
        }
        
        main_element->deleteAllChildElements();
        
    }
    
}

SSR::Parameter<float, float> SSR::Scene::get_reference_orientation() const {
    
    return reference_orientation;

}

bool SSR::Scene::select_source(const int id)
{
  bool source_is_selected = false;

  for (source_iterator it = sources->begin(); it != sources->end(); it++) {

      if (it->get_id() == id) {
          current_selected_source = it;
          source_is_selected = true;
      }

  }

  return source_is_selected;
}

std::shared_ptr< std::vector< std::pair<unsigned int, std::string> > > SSR::Scene::get_source_ids_and_names()
{
  return ids_and_names;
}

SSR::Source SSR::Scene::get_source() const
{
  SSR::Source s = *current_selected_source;
  return s;
}

unsigned int SSR::Scene::new_source(const std::string name)
{
  unsigned int id = get_next_id();
  sources->push_back(SSR::Source(id, name, scene_range));
  ids_and_names->push_back( std::pair<unsigned int, std::string>(id, name) );
  current_selected_source = get_iterator(id);
  return id;
}

bool SSR::Scene::new_source(const std::string name, const unsigned int id)
{
  bool source_successfully_created = false;

  if (!id_already_in_use(id)) {
      sources->push_back(SSR::Source(id, name, scene_range));
      ids_and_names->push_back( std::pair<unsigned int, std::string>(id, name) );
      current_selected_source = get_iterator(id);
      source_successfully_created = true;
  }

  return source_successfully_created;
}

bool SSR::Scene::new_source(const std::string name, const unsigned int id, const std::string jackport)
{
  bool source_successfully_created = false;

  if (!id_already_in_use(id)) {
      sources->push_back(SSR::Source(id, name, scene_range, jackport));
      ids_and_names->push_back( std::pair<unsigned int, std::string>(id, name) );
      current_selected_source = get_iterator(id);
      source_successfully_created = true;
  }

  return source_successfully_created;
}

void SSR::Scene::set_id_of_selected_source(const int id)
{
  set_id_of_source(current_selected_source->get_id(), id);
}

int SSR::Scene::get_id_of_selected_source() const
{
  return current_selected_source->get_id();
}

void SSR::Scene::set_x_position_discrete_of_selected_source(const float position)
{
  current_selected_source->set_x_position_discrete(position);
}

void SSR::Scene::set_x_position_continuous_of_selected_source(const float position)
{
  current_selected_source->set_x_position_continuous(position);
}

SSR::Parameter<float, float> SSR::Scene::get_x_position_of_selected_source() const
{
  return current_selected_source->get_x_position();
}

void SSR::Scene::set_y_position_discrete_of_selected_source(const float position)
{
  current_selected_source->set_y_position_discrete(position);
}

void SSR::Scene::set_y_position_continuous_of_selected_source(const float position)
{
  current_selected_source->set_y_position_continuous(position);
}

SSR::Parameter<float, float> SSR::Scene::get_y_position_of_selected_source() const
{
  return current_selected_source->get_y_position();
}

void SSR::Scene::set_gain_discrete_of_selected_source(const float gain, const bool linear)
{
  current_selected_source->set_discrete_gain(gain, linear);
}

void SSR::Scene::set_gain_continuous_of_selected_source(const float gain)
{
  current_selected_source->set_continuous_gain(gain);
}

SSR::Parameter<float, float> SSR::Scene::get_gain_of_selected_source() const
{
  return current_selected_source->get_gain();
}

void SSR::Scene::set_orientation_discrete_of_selected_source(const float orientation)
{
  current_selected_source->set_discrete_orientation(orientation);
}

void SSR::Scene::set_orientation_continuous_of_selected_source(const float orientation)
{
  current_selected_source->set_continuous_orientation(orientation);
}

SSR::Parameter<float, float> SSR::Scene::get_orientation_of_selected_source() const
{
  return current_selected_source->get_orientation();
}

void SSR::Scene::set_mute_discrete_of_selected_source(const bool mute)
{
  current_selected_source->set_discrete_mute(mute);
}

void SSR::Scene::set_mute_continuous_of_selected_source(const float mute)
{
  current_selected_source->set_continuous_mute(mute);
}

SSR::Parameter<bool, float> SSR::Scene::get_mute_of_selected_source() const
{
  return current_selected_source->get_mute();
}

void SSR::Scene::set_model_point_discrete_of_selected_source(const bool point)
{
  current_selected_source->set_discrete_model_point(point);
}

void SSR::Scene::set_model_point_continuous_of_selected_source(const float point)
{
  current_selected_source->set_continuous_model_point(point);
}

SSR::Parameter<bool, float> SSR::Scene::get_model_point_of_selected_source() const
{
  return current_selected_source->get_model_point();
}

void SSR::Scene::set_fixed_discrete_of_selected_source(const bool fixed)
{
  current_selected_source->set_discrete_fixed(fixed);
}

void SSR::Scene::set_fixed_continuous_of_selected_source(const float fixed)
{
  current_selected_source->set_continuous_fixed(fixed);
}

SSR::Parameter<bool, float> SSR::Scene::get_fixed_of_selected_source() const
{
  return current_selected_source->get_fixed();
}

void SSR::Scene::set_name_of_selected_source(const std::string name)
{
  set_name_of_source(current_selected_source->get_id(), name);
}

std::string SSR::Scene::get_name_of_selected_source() const
{
  return current_selected_source->get_name();
}

void SSR::Scene::set_properties_file_of_selected_source(const std::string prop_file)
{
  current_selected_source->set_properties_file(prop_file);
}

std::string SSR::Scene::get_properties_file_of_selected_source() const
{
  return current_selected_source->get_properties_file();
}

void SSR::Scene::set_jackport_of_selected_source(const std::string value)
{
  current_selected_source->set_jackport(value);
}

std::string SSR::Scene::get_jackport_of_selected_source() const
{
  return current_selected_source->get_jackport();
}

// PRIVATE

bool SSR::Scene::id_already_in_use(unsigned int id_to_check)
{
  return std::any_of(begin(*ids_and_names), end(*ids_and_names), [&id_to_check](std::pair<unsigned int, std::string> p){ return id_to_check == p.first; });
}

unsigned int SSR::Scene::get_next_id()
{
  unsigned int next_id = 1;
  std::for_each(begin(*ids_and_names), end(*ids_and_names), [&next_id](std::pair<unsigned int, std::string> p){

    if (next_id == p.first) {
        next_id++;
    }

  });
  return next_id;
}

const source_iterator SSR::Scene::get_iterator(unsigned int id)
{

  if (id_already_in_use(id)) {
    return std::find_if(begin(*sources), end(*sources), [id](const SSR::Source s) { return id == s.get_id(); }  );
  } else {
    throw std::runtime_error("Source does not exist!");
  }

}

void SSR::Scene::set_name_of_source(const unsigned int id, const std::string name)
{
  auto source = get_iterator(id);
  source->set_name(name);
  std::for_each(begin(*ids_and_names), end(*ids_and_names), [&id, &name](std::pair<unsigned int, std::string> p) {

    if (p.first == id) {
        p.second = name;
    }

  });

}

void SSR::Scene::set_id_of_source(const unsigned int old_id, const unsigned int new_id)
{
  auto source = get_iterator(old_id);
  source->set_id(new_id);
  std::for_each(begin(*ids_and_names), end(*ids_and_names), [&old_id, &new_id](std::pair<unsigned int, std::string> p) {

    if (p.first == old_id) {
        p.first = new_id;
    }

  });
}

void SSR::Scene::manipulate_source(source_iterator source_to_manipulate, juce::XmlElement* element)
{

  if (element->hasAttribute("volume")) {
      source_to_manipulate->set_discrete_gain(static_cast<float>(element->getDoubleAttribute("volume")), false);
  }

  if (element->hasAttribute("name")) {
      std::string name = element->getStringAttribute("name").toStdString();
      set_name_of_source(source_to_manipulate->get_id(), name);
  }

  if (element->hasAttribute("mute")) {
      source_to_manipulate->set_discrete_mute(element->getBoolAttribute("mute"));
  }

  if (element->hasAttribute("model")) {
      source_to_manipulate->set_discrete_model_point(element->getStringAttribute("model").toStdString() == "point");
  }

  if (element->hasAttribute("properties_file")) {
      source_to_manipulate->set_properties_file(element->getStringAttribute("properties_file").toStdString());
  }

  forEachXmlChildElement(*element, f) {

    if (f->hasTagName("position")) {

        if (f->hasAttribute("x")) {
            source_to_manipulate->set_x_position_discrete(static_cast<float>(f->getDoubleAttribute("x")));
        }

        if (f->hasAttribute("y")) {
            source_to_manipulate->set_y_position_discrete(static_cast<float>(f->getDoubleAttribute("y")));
        }

        if (f->hasAttribute("fixed")) {
            source_to_manipulate->set_discrete_fixed(f->getBoolAttribute("fixed"));
        } else {
            source_to_manipulate->set_discrete_fixed(false);
        }

    } else {

        if (f->hasTagName("orientation")) {

            if (f->hasAttribute("azimuth")) {
                source_to_manipulate->set_discrete_orientation(static_cast<float>(f->getDoubleAttribute("azimuth")));
            }

        } else {

            if (f->hasTagName("port")) {
                //WARNING: I put the getAllSubText() method in here because with getText()
                //I dont get the string of the port
                source_to_manipulate->set_jackport(f->getAllSubText().toStdString());
            }

        }

    }

  }

}
