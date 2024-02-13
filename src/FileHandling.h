
#ifndef PLATFORMERSFML_FILEHANDLING_H
#define PLATFORMERSFML_FILEHANDLING_H

#include "fstream"
#include <iostream>

namespace FileHandling
{
  void writeFile(std::string link, std::string content);
  std::string readFile(std::string link, int line);
}

#endif // PLATFORMERSFML_FILEHANDLING_H
