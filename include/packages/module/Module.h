/// Module.h
///
/// Copyright 2017 Mac Radigan
/// All Rights Reserved

  #include <iostream>
  #include <iomanip>
  #include <assert.h>

#pragma once

namespace rad::module {

  class Module
  {
    public:
      Module() = default;
      virtual ~Module() {};
    protected:
    private:
      friend std::ostream& operator<<(std::ostream &os, const Module& o);
  };

  std::ostream& operator<<(std::ostream &os, const Module& o)
  {
    std::ios::fmtflags flags(os.flags());
    os.flags(flags);
    return os;
  }

} // namespace

/// *EOF*
