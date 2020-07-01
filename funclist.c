#define	SM_SCCSID	"@(#)funclist.c	77.4 13/10/25 09:18:01"

/*************************************/
/*  Copyright  (C)  1993 - 2014	     */
/*           by                      */
/*  Prolifics, Incorporated	     */
/*  New York, New York               */
/*  All Rights Reserved              */
/*  Printed in U.S.A.                */
/*  Property of Prolifics, Inc.	     */
/*************************************/

#include "smdefs.h"
#include "smkeys.h"
#include "jsmn.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*jsmn_callback_t) PROTO((char *, char *, int));

/*************** THE FOLLOWING FUNCTIONS ARE IN THIS MODULE ***************/

	void	sm_do_uinstalls	PROTO((void));

static	int	sdummy		PROTO((char *, int));
static	int	gdummy		PROTO((char *, int));
static	int	fdummy		PROTO((int, char *, int, int));
static	int	cddummy		PROTO((int, int));
static	int	grdummy		PROTO((int, int, int));
static	int	cdummy		PROTO((char *));
static	int	pdummy		PROTO((int));
static	int	myservice	PROTO((char *, char *));
static	int	walk_jsmn	PROTO((char *, jsmntok_t *, char *, int,
						jsmn_callback_t f));
static	int	jsmn_putfield	PROTO((char *fieldname, char *value,
						int occur));


/*

NAME

	funclist.c

DESCRIPTION

	In order to attach your functions, you need to list them
	in one of the function lists.  This file contains sample
	function lists along with functions that show the calling and
	return sequences of the different types of functions you can
	have: screen, group, field, control string, scrolling,
	and external help functions.

	Screen entry and exit functions are specified by the Entry
	Function and Exit Function properties in the Focus section of
	the Screen properties.  They are called with two parameters, the
	screen name, and a flag indicating "why-called": K_ENTRY,
	K_EXIT, and K_EXPOSE.

	Group entry and exit functions are specified by the Entry
	Function and Exit Function properties in the Focus section of
	the Group properties.  Group validation functions are specified
	by the Validation Func property in the Validation section of the
	Group properties.  These functions are called with the group
	name and a flag indicating "why-called": K_ENTRY, K_EXIT, and
	further bits indicating which key caused the event.

	Field entry and exit functions are specified by the Entry
	Function and Exit Function properties in the Focus section of
	the Field properties.  Field validation functions are specified
	by the Validation Func property in the Validation section of the
	Field properties.  These Functions are called with four
	parameters.  The first is the field number, the next is the data
	from the field, the third is the occurrence number, and the last
	is a flag giving the MDT and VALIDED bits for the field together
	with bits indicating which key caused the event.

	Control functions are called by control strings.  Screen
	Control Strings are specified by the Control String property in
	the Focus section of the Screen properties.  Field Control
	Strings for Pushbutton and Listbox widgets are specified by the
	Control String property in the Validation section of the
	Widget's properties.  Control Strings can also be specified
	using the Menu Bar editor.  Control Functions are passed a
	single parameter, a pointer to the name and the following text.

	The prototype list is searched whenever the above lists do not
	contain the requested function.  There is no way to specify that
	ONLY the prototype list be searched.  A function in the
	prototype list may be entered without a prototype; in this case
	it receives a string consisting of the text FOLLOWING the name.

	See the Application Development Guide for information on
	prototyping.

	Functions on ANY list may be prototyped, however it may be more
	convenient to put all prototyped functions on the prototype list
	- this makes them available anywhere in the application (screen
	entry, field validation, etc.).

	Note that the functions herein actually do nothing (other than
	return), but they do serve as models upon which you can base
	your own functions.

	The function sm_do_uinstalls is called by jmain and jxmain to
	allow a place for users to install their functions.  It must be
	in any funclist.c that is used or the executable will not link.
*/


/*

NAME

	Function_list		-- List of user functions

DESCRIPTION

	All functions to be called via control strings, field
	entry/exit, etc, must be listed in the following arrays of
	structures.  This structure is defined in sminstfn.h.

	The first member is the name of the function - as specified in
	the screen or control string.

	The next member is the address of the function.  Following this
	the language (C, FORTRAN, etc.) is specified.  The value 0
	specifies C (and JPL), other values are site-specific, depending
	on what alternate language support has been installed.

	The next member ("intrn_use") is normally 0. However two bits
	are defined for special use.  NO_DELETE (0x01) is set to
	prohibit deletion of this function (by calling sm_install with a
	count of 0).  This feature may be used to mark certain functions
	as permanent and allow others to be installed or deleted in
	different parts of the application.  All the "built-in"
	functions (e.g., jm_keys) are marked in this way.

	The other flag, NOT_IN_EDITOR (0x02), may be set to prevent the
	function from being called when in editor mode of the Panther
	screen editor.  This might be set, for example, for functions that
	access a database or perform some other lengthy procedure.

	The next member is used in special installations for special
	purposes and should normally be 0.  The last member is used
	internally and should be set to 0.

	See the file sminstfn.h and the manual for more details.

*/

/************************************************************************/
/*			SCREEN ENTRY/EXIT FUNCTIONS			*/
/************************************************************************/

static struct fnc_data sfuncs[] =
{
	SM_OLDFNC("sdummy",		sdummy)
};
static int scount = sizeof (sfuncs) / sizeof (struct fnc_data);

/************************************************************************/
/*		GROUP ENTRY/EXIT/VALIDATION FUNCTIONS			*/
/************************************************************************/

static struct fnc_data gfuncs[] =
{
	SM_OLDFNC("gdummy",		gdummy)
};
static int gcount = sizeof (gfuncs) / sizeof (struct fnc_data);

/************************************************************************/
/*		FIELD ENTRY/EXIT/VALIDATION FUNCTIONS			*/
/************************************************************************/

static struct fnc_data ffuncs[] =
{
	SM_OLDFNC("fdummy",		fdummy)
};
static int fcount = sizeof (ffuncs) / sizeof (struct fnc_data);

/************************************************************************/
/*		TAB CARD ENTRY/EXIT/HIDE/EXPOSE FUNCTIONS		*/
/************************************************************************/

static struct fnc_data cdfuncs[] =
{
	SM_OLDFNC("cddummy",		cddummy)
};
static int cdcount = sizeof (cdfuncs) / sizeof (struct fnc_data);

/************************************************************************/
/*		GRID ENTRY/EXIT/VALIDATION FUNCTIONS			*/
/************************************************************************/

static struct fnc_data grfuncs[] =
{
	SM_OLDFNC("grdummy",		grdummy)
};
static int grcount = sizeof (grfuncs) / sizeof (struct fnc_data);

/************************************************************************/
/*			CONTROL FUNCTIONS				*/
/************************************************************************/

static struct fnc_data cfuncs[] =
{
	SM_OLDFNC("cdummy",		cdummy)
};
static int ccount = sizeof (cfuncs) / sizeof (struct fnc_data);

/************************************************************************/
/*			PROTOTYPED FUNCTIONS				*/
/************************************************************************/

static struct fnc_data pfuncs[] =
{
   SM_INTFNC ("myservice(s,s)",        myservice),
   SM_INTFNC ("pdummy(i)",             pdummy)
};
static int pcount = sizeof (pfuncs) / sizeof (struct fnc_data);


/************************************************************************/
/* Do not remove this function or the executable will not link.		*/
/************************************************************************/
/*

NAME		sm_do_uinstalls

SYNOPSIS
		sm_do_uinstalls();

DESCRIPTION

	Function to install user functions, signal handler, and other
	user options.

*/

void
sm_do_uinstalls NOPARMS(())
{
	static int	installed = 0;

	if (installed)
		return;

	installed = 1;

	/* install functions that exist in this module */

	sm_install (SCREEN_FUNC,  sfuncs, &scount);
	sm_install (GROUP_FUNC,   gfuncs, &gcount);
	sm_install (FIELD_FUNC,   ffuncs, &fcount);
	sm_install (CARD_FUNC,    cdfuncs,&cdcount);
	sm_install (GRID_FUNC,    grfuncs,&grcount);
	sm_install (CONTROL_FUNC, cfuncs, &ccount);
	sm_install (PROTO_FUNC,   pfuncs, &pcount);

	/* additional installs may be placed here -			*/
	/* sm_install (---, ---, &---);					*/

	/* signal handler can be installed here -			*/
	/* signal (---);						*/
}


/*

NAME

	sdummy		-- a dummy screen (entry/exit) routine

SYNOPSIS

	ret_code = sdummy (screen_name, why_called);
	int	 ret_code;
	char	*screen_name;
	int	 why_called;

DESCRIPTION

	This is an empty screen function.  The returned value is ignored, and
	is present only to satisfy the definition of the fnc_data structure.

	See smvalids.h for bits in the "why_called" parameter.


RETURNS

	0	ignored

*/

static int
sdummy PARMS((screen_name, why_called))
PARM(	 char	*screen_name)
LASTPARM(int	 why_called)
{
	return (0);
}

/*

NAME

	gdummy		-- a dummy group (validation/entry/exit) routine

SYNOPSIS

	ret_code = gdummy (group_name, why_called);
	int	 ret_code;
	char	*group_name;
	int	 why_called;

DESCRIPTION

	This is an empty group function.  The returned value is used
	only for validation functions.  It should be 0 for
	successful validation and -1 for unsuccessful.

	See smvalids.h for bits in the "why_called" parameter.


RETURNS

	 0	successful validation
	-1	error in validation

*/


static int
gdummy PARMS((group_name, why_called))
PARM(	 char	*group_name)
LASTPARM(int	 why_called)
{
	return (0);
}

/*

NAME

	fdummy		-- a dummy field (validation/entry/exit) routine

SYNOPSIS

	ret_code = fdummy (field_num, field_data, item_id, val_mdt);
	int	 ret_code;
	int	 field_num;
	char	*field_data;
	int	 item_id;
	int	 val_mdt;

DESCRIPTION

	This is the shell of a field validation routine, which is called
	to verify (i.e., validate) that the content of a field is
	correct.  This particular routine always returns a value that
	indicates that the field's content is correct, so the net effect
	of this routine is an elaborate no-op.


RETURNS

	0	Field's content is valid.
	1	Field's content is invalid, but don't move cursor to
		this field if it isn't there.
	OTHER	Field's content is invalid, and move the cursor to the
		beginning of this field.

*/


static int
fdummy PARMS((field_num, field_data, item_id, val_mdt))
PARM(	 int	 field_num)
PARM(	 char	*field_data)
PARM(	 int	 item_id)
LASTPARM(int	 val_mdt)
{
	return (0);
}

/*

NAME

	cddummy		-- a dummy card (entry/exit/expose/hide) routine.

SYNOPSIS

	ret_code = cddummy (objid, val_mdt);
	int	ret_code;
	int	objid;
	int	val_mdt;

DESCRIPTION

	This is the shell of a card routine, which might be called for
	card entry, card exit, card expose or card hide.

	objid is the object ID of the card.  Values in val_mdt can be
	used to determine the reason for which the function was called
	by testing for particular bits:

		card entry	K_ENTRY
		card exit	K_EXIT
		card expose	K_EXPOSE
		card hide	none of the above bits.

RETURNS

	ignored.

*/


static int
cddummy PARMS((objid, val_mdt))
PARM(	 int	 objid)
LASTPARM(int	 val_mdt)
{
	return (0);
}

/*

NAME

	grdummy		-- a dummy grid and grid row (validation/entry/exit)
			   routine.

SYNOPSIS

	ret_code = grdummy (field_num, item_id, val_mdt);
	int	ret_code;
	int	field_num;
	int	item_id;
	int	val_mdt;

DESCRIPTION

	This is the shell of a grid validation routine, which is called
	to verify (i.e., validate) that the content of a grid is correct.
	This particular routine always returns a value that indicates
	that the grid's content is correct, so the net effect of this
	routine is an elaborate no-op.

	Grid validation is called after field validation for its member(s).

	This function can also be used as a grid and grid row entry and
	exit function.  field_num will be the current field for all calls
	except for screen validation, where the number of the first field
	will be used.  item_id will be the current occurrence in the grid
	for grid row entry and exit and will be zero for grid entry, exit
	and validation.

RETURNS

	0	Grid's content is valid.
	OTHER	Grid's content is invalid.

*/


static int
grdummy PARMS((field_num, item_id, val_mdt))
PARM(	 int	 field_num)
PARM(	 int	 item_id)
LASTPARM(int	 val_mdt)
{
	return (0);
}

/*

NAME

	cdummy		-- a dummy control function

SYNOPSIS

	key = cdummy (cfield_data);
	int	 key;
	char	*cfield_data;

DESCRIPTION

	This type of function is called when a function is invoked via
	the caret (^) control field.  The data passed to the function is
	the contents of the control field (with the caret stripped off).

RETURNS

	Either a function key (e.g., PF1), which will cause the program to
	act as if the user had just pressed that key, or any other value,
	which returns the program to sm_input().  This function, for
	simplicity, always returns a 0.

*/


static int
cdummy PARMS((cfield_data))
LASTPARM(char *cfield_data)
{
	return (0);
}


/*

NAME

	pdummy		-- a dummy prototyped function

SYNOPSIS

	ret = pdummy (parameter);
	int	 ret;
	int	 parameter;

DESCRIPTION

	This is a dummy prototyped function.  The return and parameter
	types depend on the prototype given in the pfuncs.

	See sminstfn.h and the manual for details.

RETURNS
	varies
*/

static int
pdummy PARMS((int val))
LASTPARM(int val)
{
	return (0);
}

static int
myservice PARMS((char *in, char *out))
PARM(char *in)
LASTPARM(char *out)
{
	int len = sm_n_ww_length(in);
	char *buf = NULL;
	jsmn_parser parser;
	jsmntok_t *toks;
	int toks_size = 128;
	int r;
	char outbuf[1024];

	if (len > 0)
		buf = (char *)sm_fmalloc((size_t)(len + 1));

	if (!buf)
		return -1;

	len = sm_n_ww_read(in, buf, len + 1, 0);
	if (len <= 0)
	{
		sm_ffree(buf);
		return -2;
	}
	jsmn_init(&parser);
	for (toks = NULL, toks_size = 128, r = JSMN_ERROR_NOMEM;
	     r == JSMN_ERROR_NOMEM && toks_size < SM_INT_MAX; toks_size *= 2)
	{
		sm_ffree(toks);
		toks = (jsmntok_t *)sm_fmalloc(128 * sizeof(jsmntok_t));
		r = jsmn_parse(&parser, buf, len, toks, toks_size);
	}
	if (r < 0)
	{
		sm_ffree(toks);
		return -3;
	}
	/* Assume the top-level element is an object */
	if (r < 1 || toks[0].type != JSMN_OBJECT)
	{
		return -4;
	}
	walk_jsmn(buf, toks, NULL, 0, (jsmn_callback_t)jsmn_putfield);
	sm_ffree(toks);
	sm_ffree(buf);

	sprintf(outbuf, "{\"Greeting\":\"Hello, %s\"}", sm_n_fptr("name"));
	sm_n_ww_write(out, outbuf, 0);

	return (0);
}

static int
walk_jsmn PARMS((char *s, jsmntok_t *t, char *keyname, int occur,
						jsmn_callback_t f))
PARM(char *s)
PARM(jsmntok_t *t)
PARM(char *keyname)
PARM(int occur)
LASTPARM(jsmn_callback_t f)
{
	int i;
	int len;
	char *value;

	if (t->type == JSMN_STRING ||
	    t->type == JSMN_PRIMITIVE)
	{
		len = (int)(t->end - t->start);
		value = (char *)sm_fmalloc(len + 1);
		if (value)
		{
			strncpy(value, s + t->start, len);
			value[len] = '\0';
			(* f)(keyname, value, occur);
			sm_ffree(value);
		}
		return 1;
	}
	else if (t->type == JSMN_OBJECT)
	{
		char keybuf[256];
		int r = 0;

		for (i = 1; i <= t->size; i++)
		{
			if (t[i+r].type == JSMN_STRING)
			{
				len = (int)(t[i+r].end - t[i+r].start);
				strncpy(keybuf, s + t[i+r].start, len);
				keybuf[len] = '\0';
				r += walk_jsmn(s, &t[i+r+1], keybuf, 1, f);
			}
		}
		return r+i;
	}
	else if (t->type == JSMN_ARRAY)
	{
		int r = 0;

		for (i = 1; i <= t->size; i++)
		{
			len = (int)(t[i+r].end - t[i+r].start);
			if (t[i+r].type == JSMN_STRING ||
			    t[i+r].type == JSMN_PRIMITIVE)
			{
				value = (char *)sm_fmalloc(len + 1);
				if (value)
				{
					strncpy(value, s + t[i+r].start, len);
					value[len] = '\0';
					(* f)(keyname, value, i);
					sm_ffree(value);
				}
			}
			else if (t->type == JSMN_OBJECT)
			{
				r += walk_jsmn(s, t, NULL, 1, f);
			}
		}
		return r + i;
	}
	return 1;
}

static int
jsmn_putfield PARMS((char *fieldname, char *value, int occur))
PARM(char *fieldname)
PARM(char *value)
LASTPARM(int occur)
{
	int rv = -1;

	if (sm_n_ww_length(fieldname) >= 0)
		rv = sm_n_ww_write(fieldname, value, 0);
	else if (sm_i_fldno(fieldname, occur) > 0);
		rv = sm_i_putfield(fieldname, occur, value);

	return rv;
}

#ifdef __cplusplus
}
#endif
