/*** date-core-private.h -- our universe of dates, private bits
 *
 * Copyright (C) 2011-2014 Sebastian Freundt
 *
 * Author:  Sebastian Freundt <freundt@ga-group.nl>
 *
 * This file is part of dateutils.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the author nor the names of any contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **/
/* private portion of date-core.h */
#if !defined INCLUDED_date_core_private_h_
#define INCLUDED_date_core_private_h_

#include "date-core.h"


/* formatting defaults */
extern const char ymd_dflt[];
extern const char ymcw_dflt[];
extern const char ywd_dflt[];
extern const char yd_dflt[];
extern const char daisy_dflt[];
extern const char bizsi_dflt[];
extern const char bizda_dflt[];

extern const char ymddur_dflt[];
extern const char ymcwdur_dflt[];
extern const char ywddur_dflt[];
extern const char yddur_dflt[];
extern const char daisydur_dflt[];
extern const char bizsidur_dflt[];
extern const char bizdadur_dflt[];

extern dt_dtyp_t __trans_dfmt_special(const char*);
extern dt_dtyp_t __trans_dfmt(const char **fmt);
extern dt_dtyp_t __trans_ddurfmt(const char**fmt);

#endif	/* INCLUDED_date_core_private_h_ */
