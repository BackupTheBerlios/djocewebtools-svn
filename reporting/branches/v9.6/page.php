<?php

ini_set('magic_quotes_runtime', 0);
ini_set('magic_quotes_gpc', 0);

//error_reporting (55);

// Config
	include "conf/config.inc";
	include INC_DIR."prepend.inc.php";

	$_POST = $HTTP_POST_VARS ;
	$_GET = $HTTP_GET_VARS ;
	$_COOKIE = $HTTP_COOKIE_VARS ;
	$_FILES = $HTTP_POST_FILES;

	$username = value_from_POST_GET ("username");

// Cookies
	$cookiename = "myreportingcookie";
	require (LIB_DIR."cookie.inc");
	check_cookies ($cookiename, 'username');

	if (isset ($GLOBALS['username'])) { $username = $GLOBALS['username']; }
	if (!isset ($application)) { $application = "overview"; }

// Smarty
	require_once SMARTY_DIR.'Smarty.class.php';
	$smarty = new Smarty;
	$smarty->template_dir = TPL_DIR;
	$smarty->config_dir = $smarty->template_dir . '_config' . DIRECTORY_SEPARATOR;
	$smarty->compile_dir = TMP_DIR . '_compiled' . DIRECTORY_SEPARATOR;
	$smarty->cache_dir = TMP_DIR . '_cache' . DIRECTORY_SEPARATOR;
	if (False) {
		$smarty->compile_check = true;
		$smarty->debugging = true;
	}

	include INC_DIR."layout".DIRECTORY_SEPARATOR."SCIG.inc.php";
	include INC_DIR."layout".DIRECTORY_SEPARATOR.$application.DIRECTORY_SEPARATOR.'SPCG.inc.php';

	$smarty->display ('index.tpl');
	
?>
