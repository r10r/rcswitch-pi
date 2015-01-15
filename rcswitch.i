%module rcswitch

%{
#define SWIG_FILE_WITH_INIT
#include "RCSwitch.h"
%}

%include "RCSwitch.h"

%init %{
  if (wiringPiSetup () == -1) return;
  %}
