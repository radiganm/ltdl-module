## Makefile.am
## Copyright 2017 Mac Radigan
## All Rights Reserved

AM_LDFLAGS  = -pthread                                                         \
              -L/usr/lib -ldl -lm                                              \
              -L/usr/lib/x86_64-linux-gnu -lgflags                             \
              -lstdc++fs                                                       \
              -lltdl                                                            

AM_CPPFLAGS = -I$(top_srcdir)/include                                          \
              -std=c++1z                                                       \
              -O3
AM_FCFLAGS  = -Jmod

module_ldadd               = libmodule.la                                      \
                             -ldl -lm                                          \
                             -lrt                                              \
                             -lstdc++fs                                        \
                             -lltdl                                             

bin_PROGRAMS               = command                                           \
                             loader

command_SOURCES            = src/apps/command.cc
command_LDADD              = $(module_ldadd)

loader_SOURCES             = src/tests/loader.cc
loader_LDADD               = $(module_ldadd)

lib_LTLIBRARIES            = libmodule.la                                      \
                             libhello.la

libmodule_la_SOURCES       = src/packages/module/Module.cc
libmodule_la_LIBADD        = -L/usr/lib/x86_64-linux-gnu -lrt
libmodule_la_LDFLAGS       = -export-symbols-regex '^module_[^_]' -fPIC        \
                             -shared -pthread                                  \
                             -L/usr/lib/x86_64-linux-gnu -lrt                   


libhello_la_SOURCES           = src/packages/test/hello.cc
libhello_la_LIBADD            = -L/usr/lib/x86_64-linux-gnu -lrt                   
libhello_la_LDFLAGS           = -export-symbols-regex '^module_[^_]' -fPIC        \
                             -shared -pthread                                  \
                             -L/usr/lib/x86_64-linux-gnu -lrt                   

pkginclude_HEADERS         = include/packages/module/Module.h

## *EOF*
