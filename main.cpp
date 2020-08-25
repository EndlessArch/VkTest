#include <iostream>

#ifndef NDEBUG
#include <execinfo.h>
void __SIGSEVHANDLER(int SIG) {
   void * arr[40];
   size_t arr_size = backtrace(arr, (sizeof(arr) / sizeof(arr[0])));
   std::cerr << "Signal: " << SIG << "." << std::endl;
   backtrace_symbols_fd(arr, arr_size, 0);
   exit(SIG);
}
#endif

#include "test/code/arch/VkTest.hpp"

int main(int argc, char * argv[]) {

   // default settings.
   std::ios_base::sync_with_stdio(false);

#ifndef NDEBUG
   signal(SIGSEGV, __SIGSEVHANDLER);
#endif

   ::execute_test(argc, argv);

   return 0;
}