## Process this file with automake to produce Makefile.in

## Using wildcards in these lists doesn't work. Also GNU make's ($wildcard,) doesn't
## work. It gives warning message about portability, but in the end doesn't work,
## I tried :-).
REGFILES = data.h mematrix.h reg1.h usage.h main.cpp mematri1.h

## Filevector files:
FVSRC = fvlib/AbstractMatrix.cpp fvlib/CastUtils.cpp			\
 fvlib/convert_util.cpp fvlib/FileVector.cpp fvlib/FilteredMatrix.cpp	\
 fvlib/frutil.cpp fvlib/Logger.cpp fvlib/RealHandlerWrapper.cpp		\
 fvlib/ReusableFileHandle.cpp fvlib/Transposer.cpp
FVHEADERS = fvlib/AbstractMatrix.h fvlib/CastUtils.h fvlib/const.h	\
 fvlib/convert_util.h fvlib/FileVector.h fvlib/frutil.h			\
 fvlib/frversion.h fvlib/Logger.h fvlib/Transposer.h			\
 fvlib/ReusableFileHandle.h fvlib/RealHandlerWrapper.h			\
 fvlib/FilteredMatrix.h

## R headers, used by pacoxph
RHEADERS = include/R.h include/Rmath.h include/R_ext/Arith.h		\
 include/R_ext/Boolean.h include/Rconfig.h include/R_ext/Complex.h	\
 include/R_ext/Constants.h include/R_ext/Error.h			\
 include/R_ext/libextern.h include/R_ext/Memory.h			\
 include/R_ext/Print.h include/R_ext/Random.h include/R_ext/Utils.h	\
 include/R_ext/RS.h

## Extra files for pacoxph
COXBASE = coxfit2 chinv2 cholesky2 chsolve2 dmatrix
COXSRC = $(COXBASE:=.c)


bin_PROGRAMS = palinear palogist pacoxph

palinear_SOURCES = $(REGFILES) $(FVSRC) $(FVHEADERS)
palinear_CXXFLAGS = -DLINEAR

palogist_SOURCES = $(REGFILES) $(FVSRC) $(FVHEADERS)
palogist_CXXFLAGS = -DLOGISTIC

pacoxph_SOURCES = $(COXSRC) $(REGFILES) $(FVSRC) $(FVHEADERS)	\
 $(RHEADERS) survS.h survproto.h
pacoxph_CXXFLAGS = -DCOXPH -I $(top_srcdir)/src/include
pacoxph_CFLAGS = -DCOXPH -I $(top_srcdir)/src/include

## Install these scripts in the bin directory as well:
dist_bin_SCRIPTS = probabel.pl extIDS.pl

## Install the config file
dist_sysconf_DATA = probabel_config.cfg