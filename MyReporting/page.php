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

//// Template
//	include LIB_DIR."template.inc";
//	$t = new Template;
//	include INC_DIR."layout/$application/PCG.inc";
//	include INC_DIR."layout/CIG.inc";
//	$t->pparse("Output","CommonTemplate");


// Smarty
	require_once SMARTY_DIR.'Smarty.class.php';
	$smarty = new Smarty;
	$smarty->template_dir = 'tpl'. DIRECTORY_SEPARATOR;
	$smarty->config_dir = $smarty->template_dir . '_config' . DIRECTORY_SEPARATOR;
	$smarty->compile_dir = $smarty->template_dir . '_compiled' . DIRECTORY_SEPARATOR;
	$smarty->cache_dir = $smarty->template_dir . '_cache' . DIRECTORY_SEPARATOR;
	if (False) {
		$smarty->compile_check = true;
		$smarty->debugging = true;
	}

	include INC_DIR."layout".DIRECTORY_SEPARATOR."SCIG.inc.php";
	include INC_DIR."layout".DIRECTORY_SEPARATOR.$application.DIRECTORY_SEPARATOR.'SPCG.inc.php';

	$smarty->display ('index.tpl');
	
?>
