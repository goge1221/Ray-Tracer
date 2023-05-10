//
// Created by Andrei Goje on 09.05.23.
//

#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "tinyxml2.h"
#include "../headers/color.h"

using namespace tinyxml2;

class XMLParser{

private:
    XMLDocument document;
    color background_color;

    void set_background_color(color&);
    void parse_background_color(XMLElement *scene_element);

public:
    XMLParser();
    void load_xml_File(const std::string&);
};


#endif
