## Makefile.am
## Copyright 2017 Mac Radigan
## All Rights Reserved

AM_LDFLAGS  = -pthread                                                         \
              -L/usr/lib -ldl -lm                                              \
              -L/usr/lib/x86_64-linux-gnu -lgflags                             \
              -lltdl                                                            

AM_CPPFLAGS = -I$(top_srcdir)/include                                          \
              -std=c++1z                                                       \
              -O3
AM_FCFLAGS  = -Jmod

module_ldadd               = libmodule.la                                      \
                             -ldl -lm                                          \
                             -lrt                                              \
                             -lltdl

bin_PROGRAMS               = loader

loader_SOURCES             = src/tests/loader.cc
loader_LDADD               = $(module_ldadd)

lib_LTLIBRARIES            = libmodule.la                                      \
                             hello.la

libmodule_la_SOURCES       = src/packages/module/Module.cc
libmodule_la_LIBADD        = -L/usr/lib/x86_64-linux-gnu -lrt
libmodule_la_LDFLAGS       = -export-symbols-regex '^module_[^_]' -fPIC        \
                             -shared -pthread                                  \
                             -L/usr/lib/x86_64-linux-gnu -lrt                   


hello_la_SOURCES           = src/packages/test/hello.cc
hello_la_LIBADD            = -L/usr/lib/x86_64-linux-gnu -lrt                   
hello_la_LDFLAGS           = -export-symbols-regex '^module_[^_]' -fPIC        \
                             -shared -pthread                                  \
                             -L/usr/lib/x86_64-linux-gnu -lrt                  \
                             -module                                            

pkginclude_HEADERS         = include/packages/module/Module.h

## *EOF*
