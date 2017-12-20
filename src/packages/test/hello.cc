/// hello.cc

  #include <stdio.h>
  #include <math.h>

  #define run libhello_LTX_run

extern "C"
{

  int run(const char *argument)
  {
    char *end = NULL;
    long number;
    
    if (!argument || *argument == '\0')
    {
      fprintf(stderr, "error: invalid argument, \"%s\".\n", argument ? argument : "(null)");
      return -1;
    }
    
    number = strtol (argument, &end, 0);
    if (end && *end != '\0')
    {
      fprintf(stderr, "warning: trailing garbage \"%s\".\n", end);
    }

    printf("Square root of %s is %f\n", argument, sqrt (number));

    return 0;
  }

} // extern C

/// *EOF*
