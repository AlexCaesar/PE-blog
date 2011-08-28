/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2010 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 297205 2010-03-30 21:09:07Z johannes $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_peblog.h"
#include "path.c"
#include "file.c"

/* If you declare any globals in php_peblog.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(peblog)
*/

/* True global resources - no need for thread safety here */
static int le_peblog;

/* {{{ peblog_functions[]
 *
 * Every user visible function must have an entry in peblog_functions[].
 */
const zend_function_entry peblog_functions[] = {
	PHP_FE(peblog_get_html,	NULL)		/* For testing, remove later. */
	{NULL, NULL, NULL}	/* Must be the last line in peblog_functions[] */
};
/* }}} */

/* {{{ peblog_module_entry
 */
zend_module_entry peblog_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"peblog",
	peblog_functions,
	PHP_MINIT(peblog),
	PHP_MSHUTDOWN(peblog),
	PHP_RINIT(peblog),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(peblog),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(peblog),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PEBLOG
ZEND_GET_MODULE(peblog)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("peblog.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_peblog_globals, peblog_globals)
    STD_PHP_INI_ENTRY("peblog.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_peblog_globals, peblog_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_peblog_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_peblog_init_globals(zend_peblog_globals *peblog_globals)
{
	peblog_globals->global_value = 0;
	peblog_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(peblog)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(peblog)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(peblog)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(peblog)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(peblog)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "peblog support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


PHP_FUNCTION(peblog_get_html)
{

	zval **SERVER	= NULL;
	zval **ret		= NULL;

	zend_bool jit_init = (PG(auto_globals_jit) && !PG(register_globals) && 
			                !PG(register_long_arrays));
	if (jit_init) { 
		    zend_is_auto_global(ZEND_STRL("_SERVER") TSRMLS_CC);
	}   

	(void)zend_hash_find(&EG(symbol_table), ZEND_STRS("_SERVER"), (void **)&SERVER);
	if (zend_hash_find(Z_ARRVAL_PP(SERVER), ZEND_STRS("SCRIPT_FILENAME"), (void **)&ret) == FAILURE )
	{
		RETVAL_STRING("No SCRIPT_FILENAME. ", 1);
	}   
	else
	{
		char *str = NULL;
		str		= estrdup(Z_STRVAL_P(*ret));

		char *path_list		= "list"; 
		char *path_head		= "html/head.html";
		char *path_footer	= "html/footer.html";
		
		char *base_path	= get_base_path(str);


		int	path_list_len	= strlen(path_list) + strlen(base_path) +1;
		int	path_head_len	= strlen(path_head) + strlen(base_path) +1;
		int	path_footer_len	= strlen(path_footer) + strlen(base_path) +1;

		char *file,  *html_head , *html_list, *html_footer;


		//Head ...
		file = (char *) emalloc(path_head_len);
		memset(file , 0, path_head_len);
		sprintf(file, "%s%s", base_path, path_head);

		html_head = peblog_file_contents(file);

		//list ...
		erealloc(file,path_list_len);
		memset(file , 0, path_list_len);
		sprintf(file, "%s%s", base_path, path_list);
		html_list = peblog_file_contents(file);

		//Footer ...
		erealloc(file,path_footer_len);
		memset(file , 0, path_footer_len);
		sprintf(file, "%s%s", base_path, path_footer);
		html_footer = peblog_file_contents(file);


		int html_len = strlen(html_head) + strlen(html_list) 
						 + strlen(html_footer) + 1;

		char *html = (char *) emalloc(html_len);
		memset(html , 0, html_len);
		strcat(html, html_head);
		strcat(html, html_list);
		strcat(html, html_footer);

		efree(html_head);
		efree(html_list);
		efree(html_footer);

		RETVAL_STRING(html, 1);
	}
}




/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
