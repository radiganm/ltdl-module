/// Module.h
///
/// Copyright 2017 Mac Radigan
/// All Rights Reserved

  #include <iostream>
  #include <iomanip>
  #include <assert.h>

#pragma once

  #define MODULE__PATH_ENV ("MODULE_PATH")

namespace rad::module {

  class Module
  {
    public:
      Module();
      virtual ~Module() {};
      void load(std::string path="");
    protected:
    private:
      int errors_;
      friend std::ostream& operator<<(std::ostream &os, const Module& o);
      char *dlerrordup (char *errormsg);
  };

} // namespace

/// *EOF*
