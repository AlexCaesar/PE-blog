dnl $Id$
dnl config.m4 for extension peblog

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(peblog, for peblog support,
dnl Make sure that the comment is aligned:
dnl [  --with-peblog             Include peblog support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(peblog, whether to enable peblog support, 
dnl Make sure that the comment is aligned:
[  --enable-peblog           Enable peblog support])

if test "$PHP_PEBLOG" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-peblog -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/peblog.h"  # you most likely want to change this
  dnl if test -r $PHP_PEBLOG/$SEARCH_FOR; then # path given as parameter
  dnl   PEBLOG_DIR=$PHP_PEBLOG
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for peblog files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PEBLOG_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PEBLOG_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the peblog distribution])
  dnl fi

  dnl # --with-peblog -> add include path
  dnl PHP_ADD_INCLUDE($PEBLOG_DIR/include)

  dnl # --with-peblog -> check for lib and symbol presence
  dnl LIBNAME=peblog # you may want to change this
  dnl LIBSYMBOL=peblog # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PEBLOG_DIR/lib, PEBLOG_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PEBLOGLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong peblog lib version or lib not found])
  dnl ],[
  dnl   -L$PEBLOG_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PEBLOG_SHARED_LIBADD)

  PHP_NEW_EXTENSION(peblog, peblog.c, $ext_shared)
fi
