#include <iostream>
#include "danejoe/common/data_type.hpp"
#include "danejoe/common/time_util.hpp"
#include "danejoe/common/process_util.hpp"
#include "demo_common.hpp"

namespace demo {

void run_common_demo()
{
    std::cout << "Common demo:\n";
    std::cout << "  DataType::Int64 => " << DaneJoe::to_string(DaneJoe::DataType::Int64) << "\n";
    std::cout << "  now              => " << DaneJoe::TimeUtil::get_now_time_str() << "\n";
    std::cout << "  pid              => " << DaneJoe::ProcessUtil::get_pid() << "\n";
}

} // namespace demo
