/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
#include "cmSourceFilesRequireCommand.h"

// cmSourceFilesRequireCommand
bool cmSourceFilesRequireCommand::Invoke(std::vector<std::string>& args)
{
  if(args.size() < 4 )
    {
    this->SetError("called with incorrect number of arguments");
    return false;
    }
  std::vector<std::string>::iterator i = args.begin();
  // Search to the key word SOURCES_BEGIN is found
  // if one of the required defines is not there, then
  // return as none of the source files will be added
  // if the required definition is not there.
  while(i != args.end() && (*i) != "SOURCES_BEGIN" )
    {
    if(!m_Makefile->GetDefinition((*i).c_str()))
      {
      return true;
      }
    i++;
    }
  if(i != args.end())
    {
    i++;
    }
  
  // Add the rest of the arguments as source files
  const char *sname = (*i).c_str();
  ++i;
  for(; i != args.end(); ++i)
    {
    cmClassFile file;
    file.m_AbstractClass = false;
    file.SetName((*i).c_str(), m_Makefile->GetCurrentDirectory());
    m_Makefile->AddClass(file, sname);
    }
  return true;
}

