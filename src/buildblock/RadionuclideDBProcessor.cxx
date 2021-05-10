/*!

  \file
  \ingroup projdata
  \brief Implementation of class stir::RadionuclideDBProcessor
  
  \author Daniel Deidda
  \author Kris Thielemans
      
*/
/*
    Copyright (C) 2021, NPL
    Copyright (C) 2021, UCL
    This file is part of STIR.

    This file is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This file is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    See STIR/LICENSE.txt for details
*/

#include "stir/RadionuclideDBProcessor.h"
#include "stir/info.h"
#include "stir/round.h"
#include "stir/error.h"
#include "stir/find_STIR_config.h"

START_NAMESPACE_STIR

RadionuclideDBProcessor::
RadionuclideDBProcessor()
{
}

RadionuclideDBProcessor::
RadionuclideDBProcessor(ImagingModality rmodality, std::string rname)
:nuclide_name(rname),
 modality(rmodality)
{
    set_DB_filename(find_STIR_config_file("radionuclide_info.json"));
    this->isotope_lookup_table_str=find_STIR_config_file("isotope_names.json");
    modality_str=modality.get_name();
    
    //Read Radionuclide file and set JSON member for DB
    
    std::string s =this->filename;
    std::ifstream json_file_stream(s);
    
    if(!json_file_stream)
        error("Could not open Json file!");
  
  //  nlohmann::json radionuclide_json;
    json_file_stream >> this->radionuclide_json;
  //  radionuclide_json.parse(json_file_stream);
  //  
    
    if (radionuclide_json.find("nuclide") == radionuclide_json.end())
    {
      error("RadionuclideDB: No or incorrect JSON radionuclide set (could not find \"nuclide\" in file \""
            + filename + "\")");
    }
}

void
RadionuclideDBProcessor::
set_DB_filename(const std::string& arg)
{
  this->filename = arg;
}

void 
RadionuclideDBProcessor::get_isotope_name_from_lookup_table()
{
    if (this->isotope_lookup_table_str.empty())
        error("Lookup table: no filename set");
    if (this->filename.empty())
      error("RadionuclideDB: no filename set for the Radionuclide info");
    
    
    std::string s =this->isotope_lookup_table_str;
    std::ifstream json_file_stream(s);
    
    if(!json_file_stream)
        error("Could not open Json file!");
    
    nlohmann::json table_json;
    json_file_stream >> table_json;
    
//    Check that lookup table and database have the same numbe of elements
    if (radionuclide_json["nuclide"].size() != table_json.size())
        error("The lookup table and the radionuclide database do not have the same number of elements. " 
              "If you added a radionuclide you also need to add the same in the lookup table");
//    std::cout<<radionuclide_json["nuclide"].size()<< "   "<<table_json.size();
    
    for (int l=0; l<table_json.size(); l++)
        for (int c=0; c<table_json.at(0).size(); c++)
        {
            if(table_json.at(l).at(c)==this->nuclide_name)
            this->nuclide_name=table_json.at(l).at(0);
        }
//    std::cout<<" name " <<nuclide_name<<std::endl;

}

void
RadionuclideDBProcessor::
get_record_from_json()
{
    get_isotope_name_from_lookup_table();
    
  if (this->filename.empty())
    error("RadionuclideDB: no filename set for the Radionuclide info");
  if (this->modality_str.empty())
    error("RadionuclideDB: no modality set for the Radionuclide info");
  if (this->nuclide_name.empty())
    error("RadionuclideDB: no nuclide set for the Radionuclide info");

  
  

  std::string name = this->nuclide_name;

  //Get desired keV as float value
  float  keV = this->energy;
  //Get desired kVp  as float value
  float  h_life = this->half_life;
  info("RadionuclideDB: finding record radionuclide: " + nuclide_name+
       " in file "+ filename);
  
  //Extract appropriate chunk of JSON file for given nuclide.
  nlohmann::json target = radionuclide_json["nuclide"][name]["modality"][modality_str]["properties"];
//[name]["modality"][modality_str]["properties"]
  int location = -1;
  int pos = 0;
  for (auto entry : target){
      location = pos;
    pos++;
  }

  if (location == -1){
    error("RadionuclideDB: Desired radionuclide not found!");
  }

  //Extract properties for specific nuclide and modality.
  nlohmann::json properties = target[location];
  {
    std::stringstream str;
    str << properties.dump(6);
    info("RadionuclideDB: JSON record found:" + str.str(),2);
  }
  this->energy = properties["kev"];
  this->branching_ratio = properties["BRatio"];
  this->half_life = properties["half_life"];
  
  //  this->breakPoint = properties["break"];
  
//Set Radionuclide member
  Radionuclide rnuclide(nuclide_name,
                        energy,
                        branching_ratio,
                        half_life,
                        modality);
  
  this->radionuclide=rnuclide;

}

Radionuclide 
RadionuclideDBProcessor::
get_radionuclide(){
    get_record_from_json();
    return this->radionuclide;
}

END_NAMESPACE_STIR


