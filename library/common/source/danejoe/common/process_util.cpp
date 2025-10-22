#include "danejoe/common/process_util.hpp"

#if defined(_WIN32)
  #include <windows.h>
#else
  #include <unistd.h>
#endif

namespace DaneJoe {

int ProcessUtil::get_pid()
{
#if defined(_WIN32)
    return static_cast<int>(::GetCurrentProcessId());
#else
    return static_cast<int>(::getpid());
#endif
}

} // namespace DaneJoe
