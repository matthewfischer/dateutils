#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "dt-core.h"

#define CHECK(pred, args...)			\
	if (pred) {				\
		fprintf(stderr, args);		\
		res = 1;			\
	}
#define CHECK_EQ(slot, val, args...)		\
	CHECK(slot != val, args, slot, val)

static int
add_d_only(void)
{
	static const char str[] = "2012-03-28";
	struct dt_dt_s d;
	struct dt_dt_s dur;
	int res = 0;

	/* 2012-03-28 (using no format) */
	fprintf(stderr, "testing %s +1d ...\n", str);
	d = dt_strpdt(str, NULL, NULL);

	/* we lack some lovely ctors for this */
	dt_make_d_only(&dur, DT_DAISY);
	dur.dur = 1;
	dur.neg = 0;
	dur.d.daisy = 1;
	dur.t.u = 0;

	/* the actual addition */
	d = dt_dtadd(d, dur);

	CHECK(d.d.typ != DT_YMD,
	      "  TYPE DIFFERS %u ... should be %u\n",
	      (unsigned int)d.d.typ,
	      (unsigned int)DT_YMD);
	CHECK(d.t.u,
	      "  TIME COMPONENT NOT NAUGHT %" PRIu64 "\n",
	      (uint64_t)d.t.u);
	CHECK(d.dur, "  DURATION BIT SET\n");
	CHECK(d.neg, "  NEGATED BIT SET\n");
	CHECK(d.t.dur, "  TIME DURATION BIT SET\n");
	CHECK(d.t.neg, "  TIME NEGATED BIT SET\n");

	CHECK_EQ((unsigned int)d.d.ymd.y, 2012U,
		 "  YEAR %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.d.ymd.m, 3U,
		 "  MONTH %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.d.ymd.d, 29U,
		 "  DAY %u ... should be %u\n");
	/* make sure the padding leaves no garbage */
	CHECK(d.d.ymd.u & ~0x1fffff,
	      "  PADDING NOT NAUGHT %u\n",
	      (unsigned int)(d.d.ymd.u & ~0x1fffff));
	return res;
}

static int
add_t_only(void)
{
	static const char str[] = "12:34:56";
	struct dt_dt_s d;
	struct dt_dt_s dur;
	int res = 0;

	/* 2012-03-28 (using no format) */
	fprintf(stderr, "testing %s +1h ...\n", str);
	d = dt_strpdt(str, NULL, NULL);

	/* we lack some lovely ctors for this */
	dt_make_t_only(&dur, DT_TUNK);
	dur.dur = 1;
	dur.neg = 0;
	dur.t.dur = 1;
	dur.t.neg = 0;
	dur.d.u = 0;
	dur.t.sdur = 3600;

	/* the actual addition */
	d = dt_dtadd(d, dur);

	CHECK(d.typ != DT_SANDWICH_UNK,
	      "  TYPE DIFFERS %u ... should be %u\n",
	      (unsigned int)d.typ,
	      (unsigned int)DT_SANDWICH_UNK);
	CHECK(d.t.typ != DT_HMS,
	      "  TYPE DIFFERS %u ... should be %u\n",
	      (unsigned int)d.t.typ,
	      (unsigned int)DT_HMS);
	CHECK(d.d.u,
	      "  DATE COMPONENT NOT NAUGHT %" PRIu64 "\n",
	      (uint64_t)d.d.u);
	CHECK(d.dur, "  DURATION BIT SET\n");
	CHECK(d.neg, "  NEGATED BIT SET\n");
	CHECK(d.t.dur, "  TIME DURATION BIT SET\n");
	CHECK(d.t.neg, "  TIME NEGATED BIT SET\n");

	CHECK_EQ((unsigned int)d.t.hms.h, 13U,
		 "  HOUR %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.t.hms.m, 34U,
		 "  MINUTE %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.t.hms.s, 56U,
		 "  SECOND %u ... should be %u\n");
	/* make sure the padding leaves no garbage */
	CHECK(d.t.hms.u & ~0x1f3f3f3fffffff,
	      "  PADDING NOT NAUGHT %u\n",
	      (unsigned int)(d.t.hms.u & ~0x1f3f3f3fffffff));
	return res;
}

static int
dt_add_d(void)
{
	static const char str[] = "2012-03-28T12:34:56";
	struct dt_dt_s d;
	struct dt_dt_s dur;
	int res = 0;

	fprintf(stderr, "testing %s +1d ...\n", str);
	d = dt_strpdt(str, NULL, NULL);

	/* we lack some lovely ctors for this */
	dt_make_d_only(&dur, DT_DAISY);
	dur.dur = 1;
	dur.neg = 0;
	dur.d.daisy = 1;
	dur.t.u = 0;
	dur.t.dur = 0;
	dur.t.neg = 0;

	/* the actual addition */
	d = dt_dtadd(d, dur);

	CHECK(d.d.typ != DT_YMD,
	      "  TYPE DIFFERS %u ... should be %u\n",
	      (unsigned int)d.d.typ,
	      (unsigned int)DT_YMD);
	CHECK(d.dur, "  DURATION BIT SET\n");
	CHECK(d.neg, "  NEGATED BIT SET\n");
	CHECK(d.t.dur, "  TIME DURATION BIT SET\n");
	CHECK(d.t.neg, "  TIME NEGATED BIT SET\n");

	CHECK_EQ((unsigned int)d.d.ymd.y, 2012U,
		 "  YEAR %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.d.ymd.m, 3U,
		 "  MONTH %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.d.ymd.d, 29U,
		 "  DAY %u ... should be %u\n");

	CHECK_EQ((unsigned int)d.t.hms.h, 12U,
		 "  HOUR %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.t.hms.m, 34U,
		 "  MINUTE %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.t.hms.s, 56U,
		 "  SECOND %u ... should be %u\n");

	/* make sure the padding leaves no garbage */
	CHECK(d.d.ymd.u & ~0x1fffff,
	      "  PADDING NOT NAUGHT %u\n",
	      (unsigned int)(d.d.ymd.u & ~0x1fffff));
	CHECK(d.t.hms.u & ~0x1f3f3f3fffffff,
	      "  TIME PADDING NOT NAUGHT %u\n",
	      (unsigned int)(d.t.hms.u & ~0x1f3f3f3fffffff));
	return res;
}

static int
dt_add_t(void)
{
	static const char str[] = "2012-03-28T23:12:01";
	struct dt_dt_s d;
	struct dt_dt_s dur;
	int res = 0;

	fprintf(stderr, "testing %s +1h ...\n", str);
	d = dt_strpdt(str, NULL, NULL);

	/* we lack some lovely ctors for this */
	dt_make_t_only(&dur, DT_TUNK);
	dur.dur = 1;
	dur.neg = 0;
	dur.d.u = 0;
	dur.t.dur = 1;
	dur.t.neg = 0;
	dur.t.sdur = 3600;

	/* the actual addition */
	d = dt_dtadd(d, dur);

	CHECK(d.d.typ != DT_YMD,
	      "  DATE TYPE DIFFERS %u ... should be %u\n",
	      (unsigned int)d.d.typ,
	      (unsigned int)DT_YMD);
	CHECK(d.t.typ != DT_HMS,
	      "  TIME TYPE DIFFERS %u ... should be %u\n",
	      (unsigned int)d.t.typ,
	      (unsigned int)DT_HMS);
	CHECK(d.dur, "  DURATION BIT SET\n");
	CHECK(d.neg, "  NEGATED BIT SET\n");
	CHECK(d.t.dur, "  TIME DURATION BIT SET\n");
	CHECK(d.t.neg, "  TIME NEGATED BIT SET\n");

	CHECK_EQ((unsigned int)d.d.ymd.y, 2012U,
		 "  YEAR %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.d.ymd.m, 3U,
		 "  MONTH %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.d.ymd.d, 29U,
		 "  DAY %u ... should be %u\n");

	CHECK_EQ((unsigned int)d.t.hms.h, 00U,
		 "  HOUR %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.t.hms.m, 12U,
		 "  MINUTE %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.t.hms.s, 01U,
		 "  SECOND %u ... should be %u\n");

	/* make sure the padding leaves no garbage */
	CHECK(d.d.ymd.u & ~0x1fffff,
	      "  PADDING NOT NAUGHT %u\n",
	      (unsigned int)(d.d.ymd.u & ~0x1fffff));
	CHECK(d.t.hms.u & ~0x1f3f3f3fffffff,
	      "  TIME PADDING NOT NAUGHT %u\n",
	      (unsigned int)(d.t.hms.u & ~0x1f3f3f3fffffff));
	return res;
}

static int
dt_add_dt(void)
{
	static const char str[] = "2012-03-28T23:55:55";
	struct dt_dt_s d;
	struct dt_dt_s dur;
	int res = 0;

	fprintf(stderr, "testing %s +1d1h ...\n", str);
	d = dt_strpdt(str, NULL, NULL);

	/* we lack some lovely ctors for this */
	dt_make_sandwich(&dur, DT_DAISY, DT_TUNK);
	dur.dur = 1;
	dur.neg = 0;
	dur.d.daisy = 1;
	dur.t.dur = 1;
	dur.t.neg = 0;
	dur.t.sdur = 3600;

	/* the actual addition */
	d = dt_dtadd(d, dur);

	CHECK(d.d.typ != DT_YMD,
	      "  DATE TYPE DIFFERS %u ... should be %u\n",
	      (unsigned int)d.d.typ,
	      (unsigned int)DT_YMD);
	CHECK(d.t.typ != DT_HMS,
	      "  TIME TYPE DIFFERS %u ... should be %u\n",
	      (unsigned int)d.t.typ,
	      (unsigned int)DT_HMS);
	CHECK(d.dur, "  DURATION BIT SET\n");
	CHECK(d.neg, "  NEGATED BIT SET\n");
	CHECK(d.t.dur, "  TIME DURATION BIT SET\n");
	CHECK(d.t.neg, "  TIME NEGATED BIT SET\n");

	CHECK_EQ((unsigned int)d.d.ymd.y, 2012U,
		 "  YEAR %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.d.ymd.m, 3U,
		 "  MONTH %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.d.ymd.d, 30U,
		 "  DAY %u ... should be %u\n");

	CHECK_EQ((unsigned int)d.t.hms.h, 00U,
		 "  HOUR %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.t.hms.m, 55U,
		 "  MINUTE %u ... should be %u\n");
	CHECK_EQ((unsigned int)d.t.hms.s, 55U,
		 "  SECOND %u ... should be %u\n");

	/* make sure the padding leaves no garbage */
	CHECK(d.d.ymd.u & ~0x1fffff,
	      "  PADDING NOT NAUGHT %u\n",
	      (unsigned int)(d.d.ymd.u & ~0x1fffff));
	CHECK(d.t.hms.u & ~0x1f3f3f3fffffff,
	      "  TIME PADDING NOT NAUGHT %u\n",
	      (unsigned int)(d.t.hms.u & ~0x1f3f3f3fffffff));
	return res;
}

int
main(void)
{
	int res = 0;

	/* we just assume the parser works */
	if (add_d_only() != 0) {
		res = 1;
	}

	if (add_t_only() != 0) {
		res = 1;
	}

	if (dt_add_d() != 0) {
		res = 1;
	}

	if (dt_add_t() != 0) {
		res = 1;
	}

	if (dt_add_dt() != 0) {
		res = 1;
	}

	return res;
}

/* dtcore-add.c ends here */
