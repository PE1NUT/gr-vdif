/* -*- c++ -*- */

#define VDIF_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "vdif_swig_doc.i"

%{
#include "vdif/VDIF_packetize.h"
%}

%include "vdif/VDIF_packetize.h"
GR_SWIG_BLOCK_MAGIC2(vdif, VDIF_packetize);
