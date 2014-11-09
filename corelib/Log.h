#ifndef LOG_H
#define LOG_H

#include <string>
#include <cstdarg>
#include <iostream>

namespace
{
  enum LOGLVL { LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };
  void LogMsg( LOGLVL lvl, const std::string &format, ... )
  {
    if( lvl >= LOGLVL::LOG_ERROR )
      std::cout << "[$$$] ";

    va_list args;
    char str[256];

    // special C stuff to interpret a dynamic set of arguments specified by "..."
    va_start(args, format);
      vsprintf_s(str, format.c_str(), args);
    va_end(args);

    std::cout << str << std::endl;
  }
}
#endif // LOG_H
