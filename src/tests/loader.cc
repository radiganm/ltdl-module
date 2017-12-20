/// loader.cc
/// Copyright 2017 Mac Radigan
/// All Rights Reserved

  #include "packages/module/Module.h"
  #include <gflags/gflags.h>
  #include <iostream>
  #include <signal.h>
  #include <atomic>
  #include <chrono>
  #include <limits.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <ltdl.h>

  #define MODULE__PATH_ENV ("MODULE_PATH")

  using namespace std::chrono_literals;

extern "C"
{
  typedef int entrypoint (const char *argument);
  static char *dlerrordup (char *errormsg);
}

  static std::atomic<bool> is_running(true);

  static void interrupt(int signo)
  {
    switch(signo)
    {
      case SIGINT:
        is_running = false;
        break;
      default:
        std::cerr << "unhandled signal" << std::endl << std::flush;
    }
  }
  
  DEFINE_bool(  debug,    false, "debug");
  DEFINE_bool(  verbose,  false, "verbose");
  DEFINE_string(name,    "test", "name");
  DEFINE_string(args,        "", "args");

  int main(int argc, char *argv[])
  {
    int status(EXIT_SUCCESS);

    if(SIG_ERR == signal(SIGINT, interrupt)) {
      perror("unable to set signal");
      return status;
    }

    std::string usage("loader - usage:\n");
    usage += argv[0];
    usage += " ";
    gflags::SetUsageMessage(usage);
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    char *errormsg     = NULL;
    lt_dlhandle module = NULL;
    entrypoint *run    = NULL;
    int errors         = 0;

    const bool        debug(  FLAGS_debug);
    const bool        verbose(FLAGS_verbose);
    const std::string name(   FLAGS_name);
    const std::string args(   FLAGS_args);

    if (args.empty())
    {
      std::cout << gflags::ProgramUsage() << std::endl << std::flush;
      return(EXIT_FAILURE);
    }

    errors = lt_dlinit();

    if (!errors)
    {
      const char *path = getenv(MODULE__PATH_ENV);
      if (path != NULL) errors = lt_dlsetsearchpath(path);
    }
  
    if (!errors) module = lt_dlopenext(name.c_str());

    if (module)
    {
      run = (entrypoint *)lt_dlsym(module, "run");
      errormsg = dlerrordup(errormsg);
      if (errormsg != NULL)
      {
        errors = lt_dlclose(module);
        module = NULL;
      }
    }
    else
    {
      errors = 1;
    }

    if (!errors)
    {
      int result = (*run)(args.c_str());
      if (result < 0)
      {
        errormsg = strdup("module entry point execution failed");
      }
      else
      {
        printf("\t=> %d\n", result);
      }
    }

    if (!errors) errors = lt_dlclose(module);

    if (errors)
    {
      errormsg = dlerrordup(errormsg);
      if (!errormsg)
      {
        fprintf(stderr, "%s: dlerror() failed.\n", argv[0]);
        return EXIT_FAILURE;
      }
    }

    if (!errors) if (lt_dlexit () != 0) errormsg = dlerrordup (errormsg);

    if (errormsg)
    {
      fprintf(stderr, "ERROR in %s: %s.\n", argv[0], errormsg);
      free(errormsg);
      exit(EXIT_FAILURE);
    }

    return status;
  }

  static char *dlerrordup (char *errormsg)
  {
    char *error = (char *) lt_dlerror();
    if (error && !errormsg) errormsg = strdup(error);
    return errormsg;
  }

/// *EOF*
