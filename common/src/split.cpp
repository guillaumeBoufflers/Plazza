#include		"common.hh"

std::vector<std::string> split(char delim, std::string work)
{
  std::vector<std::string> flds;
  std::string buf = "";
  size_t        i = 0;

  work = work.data();
  if (!flds.empty())
    flds.clear();
  while (i < work.length())
    {
      while (work[i] != delim && i < work.length() )
        {
          buf += work[i];
          i++;
        }
      flds.push_back(buf);
      buf = "";
      i++;
    }
  return (flds);
}
