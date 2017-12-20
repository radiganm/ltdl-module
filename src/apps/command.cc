/// command.cc
/// Copyright 2017 Mac Radigan
/// All Rights Reserved

  #include "packages/module/Module.h"
  #include <iostream>
  #include <signal.h>
  #include <atomic>
  #include <chrono>
  #include <limits.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  using namespace std::chrono_literals;

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
  
  int main(int argc, char *argv[])
  {
    int status(EXIT_SUCCESS);

    if(SIG_ERR == signal(SIGINT, interrupt)) {
      perror("unable to set signal");
      return status;
    }

    rad::module::Module mod;

    mod.load();

    return status;
  }

/// *EOF*
