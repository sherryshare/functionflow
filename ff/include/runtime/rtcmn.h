#ifndef FF_RUNTIME_RTCMN_H_
#define FF_RUNTIME_RTCMN_H_
#include <thread>
#include <atomic>
#include <mutex>
#include "runtime/env.h"
#include "runtime/taskbase.h"

namespace ff {
namespace rt {

void	schedule(task_base_ptr p);

//Give other tasks opportunities to run!
void yield();

//!This will save the context, and save it to the current RTThreadInfo.
template <class Func>
void 	yield_and_ret_until(Func f)
{
    auto info = RTThreadInfo::instance();
    auto ctx = make_shared_jmp_buf();
    if(setjmp(ctx.get()) == 0)
    {
        info->get_to_exe_ctxs().push_back(std::make_tuple(ctx, f));
        longjmp(info->get_entry_point().get(), 1);
    }
}//end yield_and_ret_until

}//end namespace rt
}//end namespace ff
#endif
