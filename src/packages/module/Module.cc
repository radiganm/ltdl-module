/// Module.cc
///
/// Copyright 2017 Mac Radigan
/// All Rights Reserved

  #include "packages/module/Module.h"
  #include <experimental/filesystem>
  #include <stdexcept>
  #include <ltdl.h>
  #include <chrono>
  #include <thread>

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  namespace fs = std::experimental::filesystem;
  using namespace std::chrono_literals;

namespace rad::module {

  char* Module::dlerrordup(char *errormsg)
  {
    char *error = (char *) lt_dlerror();
    if (error && !errormsg) errormsg = strdup(error);
    return errormsg;
  }

  Module::Module()
  {
    errors_ = lt_dlinit();
  }

  void Module::load(std::string path)
  {
    auto wait = 1s;
    char *errormsg;
    typedef int entrypoint (const char *argument);
    entrypoint *run    = NULL;
    lt_dlhandle module = nullptr;
    const std::string default_path = (nullptr == getenv(MODULE__PATH_ENV))
      ? ".libs"
      : getenv(MODULE__PATH_ENV);
    const auto search_path = path.empty() 
      ? default_path
      : path;
    const auto ext = ".so";
    errors_ = lt_dlsetsearchpath(search_path.c_str());
    if (errors_) throw std::runtime_error("LTLD could not set search path.");
    for (auto &p: fs::recursive_directory_iterator(fs::system_complete(search_path)))
    {
      if (ext == fs::path(p).extension()) 
      {
        module = lt_dlopenext(p.path().filename().string().c_str());
        if (module)
        {
          std::cout << "ok" << '\n';
        //std::this_thread::sleep_for(wait);
          run = (entrypoint *)lt_dlsym(module, "run");
          errormsg = dlerrordup(errormsg);
          if (nullptr != errormsg)
          {
            errors_ = lt_dlclose(module);
            module = nullptr;
          }
          else
          {
            int result = (*run)("100");
          }
        }
        fflush(stdout);
        fflush(stderr);
        std::cout << p << std::endl << std::flush;
      }
    }
  }

  std::ostream& operator<<(std::ostream &os, const Module& o)
  {
    std::ios::fmtflags flags(os.flags());
    os.flags(flags);
    return os;
  }

} // namespace

  using namespace rad::module;

/// *EOF*
