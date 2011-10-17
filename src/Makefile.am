### Makefile.am

AM_CPPFLAGS = -D_GNU_SOURCE -D_POSIX_C_SOURCE=201001L -D__USE_XOPEN2K8
AM_LDFLAGS =

M4 = m4

bin_PROGRAMS =
noinst_PROGRAMS =
BUILT_SOURCES =
CLEANFILES =
GGO_HELPERS =
EXTRA_DIST = $(BUILT_SOURCES) $(GGO_HELPERS)

GGO_HELPERS += __gengetopt-mularg.h __gengetopt-mularg.sed
GGO_HELPERS += common.ggo.in

DT_INCLUDES = -I$(top_srcdir)/lib
noinst_HEADERS = date-io.h time-io.h

bin_PROGRAMS += dseq
dseq_SOURCES = dseq.c dseq-clo.ggo
dseq_CPPFLAGS = $(AM_CPPFLAGS) $(DT_INCLUDES)
dseq_LDFLAGS = $(AM_LDFLAGS)
BUILT_SOURCES += dseq-clo.c dseq-clo.h

bin_PROGRAMS += strptime
strptime_SOURCES = strptime.c strptime-clo.ggo
strptime_CPPFLAGS = $(AM_CPPFLAGS) $(DT_INCLUDES)
strptime_LDFLAGS = $(AM_LDFLAGS)
BUILT_SOURCES += strptime-clo.c strptime-clo.h

bin_PROGRAMS += dcal
dcal_SOURCES = dcal.c dcal-clo.ggo
dcal_CPPFLAGS = $(AM_CPPFLAGS) $(DT_INCLUDES)
dcal_LDFLAGS = $(AM_LDFLAGS)
BUILT_SOURCES += dcal-clo.c dcal-clo.h

bin_PROGRAMS += dtest
dtest_SOURCES = dtest.c dtest-clo.ggo
dtest_CPPFLAGS = $(AM_CPPFLAGS) $(DT_INCLUDES)
dtest_LDFLAGS = $(AM_LDFLAGS)
BUILT_SOURCES += dtest-clo.c dtest-clo.h

bin_PROGRAMS += dadd
dadd_SOURCES = dadd.c dadd-clo.ggo
dadd_CPPFLAGS = $(AM_CPPFLAGS) $(DT_INCLUDES)
dadd_LDFLAGS = $(AM_LDFLAGS)
BUILT_SOURCES += dadd-clo.c dadd-clo.h

bin_PROGRAMS += ddiff
ddiff_SOURCES = ddiff.c ddiff-clo.ggo
ddiff_CPPFLAGS = $(AM_CPPFLAGS) $(DT_INCLUDES)
ddiff_LDFLAGS = $(AM_LDFLAGS)
BUILT_SOURCES += ddiff-clo.c ddiff-clo.h

bin_PROGRAMS += dgrep
dgrep_SOURCES = dgrep.c dgrep-clo.ggo
dgrep_CPPFLAGS = $(AM_CPPFLAGS) $(DT_INCLUDES)
dgrep_LDFLAGS = $(AM_LDFLAGS)
BUILT_SOURCES += dgrep-clo.c dgrep-clo.h

bin_PROGRAMS += tseq
tseq_SOURCES = tseq.c tseq-clo.ggo
tseq_CPPFLAGS = $(AM_CPPFLAGS) $(DT_INCLUDES)
tseq_LDFLAGS = $(AM_LDFLAGS)
BUILT_SOURCES += tseq-clo.c tseq-clo.h

bin_PROGRAMS += tdiff
tdiff_SOURCES = tdiff.c tdiff-clo.ggo
tdiff_CPPFLAGS = $(AM_CPPFLAGS) $(DT_INCLUDES)
tdiff_LDFLAGS = $(AM_LDFLAGS)
BUILT_SOURCES += tdiff-clo.c tdiff-clo.h

bin_PROGRAMS += tadd
tadd_SOURCES = tadd.c tadd-clo.ggo
tadd_CPPFLAGS = $(AM_CPPFLAGS) $(DT_INCLUDES)
tadd_LDFLAGS = $(AM_LDFLAGS)
BUILT_SOURCES += tadd-clo.c tadd-clo.h

bin_PROGRAMS += tgrep
tgrep_SOURCES = tgrep.c tgrep-clo.ggo
tgrep_CPPFLAGS = $(AM_CPPFLAGS) $(DT_INCLUDES)
tgrep_LDFLAGS = $(AM_LDFLAGS)
BUILT_SOURCES += tgrep-clo.c tgrep-clo.h

bin_PROGRAMS += ttest
ttest_SOURCES = ttest.c ttest-clo.ggo
ttest_CPPFLAGS = $(AM_CPPFLAGS) $(DT_INCLUDES)
ttest_LDFLAGS = $(AM_LDFLAGS)
BUILT_SOURCES += ttest-clo.c ttest-clo.h

bin_PROGRAMS += tcal
tcal_SOURCES = tcal.c tcal-clo.ggo
tcal_CPPFLAGS = $(AM_CPPFLAGS) $(DT_INCLUDES)
tcal_LDFLAGS = $(AM_LDFLAGS)
BUILT_SOURCES += tcal-clo.c tcal-clo.h


## ggo rule
%.c %.h: %.ggo $(GGO_HELPERS)
	$(M4) -I $(srcdir) common.ggo.in $< | gengetopt -l -F $*
## patch the multiple arg thingie dingie
	sed -f $(srcdir)/__gengetopt-mularg.sed -- $*.c > $*.c.sed && \
		mv $*.c.sed $*.c

# 
# Help the developers get nice post-processed source files

## Create preprocessor output (debugging purposes only)
.c.i:
	$(COMPILE) -E -o $@ $<

## Create assembler output (debugging purposes only)
.c.s:
	$(COMPILE) -S -c $(AM_CFLAGS) $<