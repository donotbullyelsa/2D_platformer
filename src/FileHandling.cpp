
#include "FileHandling.h"

void FileHandling::writeFile(std::string link, std::string content)
{
  std::ofstream file(link, std::ios::app);
  file << content;
  file.close();
}

std::string FileHandling::readFile(std::string link, int line)
{
  std::ifstream file;
  file.open(link);
  std::string line_string;
  for (int i=0; i<line; i++)
  {
    getline(file, line_string);
  }
  file.close();
  return line_string;
}
