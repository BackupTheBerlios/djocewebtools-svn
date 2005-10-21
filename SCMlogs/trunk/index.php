<?php

ini_set('magic_quotes_runtime', 0);
ini_set('magic_quotes_gpc', 0);



//error_reporting (55);

// Config
include "conf/config.inc";
include "inc/require.inc";
include "inc/datamanager.inc";

	$_POST = $HTTP_POST_VARS ;
	$_GET = $HTTP_GET_VARS ;
	$_COOKIE = $HTTP_COOKIE_VARS ;

if (isset($_GET['repo'])) {
	SCMLogs_set_repository_id ($_GET['repo']);
}

// Cookies
	if (!isset($user) and isset($_POST['user'])) { $username = $_POST['user']; }
	if (!isset($user) and isset($_GET['user'])) { $username = $_GET['user']; }
	/*
	$cookiename = "SCMlogs";
	require ($lib_dir."/cookie.inc");
	check_cookies ($cookiename, 'user');

	if (isset ($GLOBALS['user'])) {
		$username = $GLOBALS['user']; 
	}
	*/

// Template
	include LIB_DIR."template.inc";
	$t = new Template;

	/// Index Interface
	if (!isset ($application)) {
		$application = "index";
	}


	include INC_DIR."layout/CIG.inc";
	include INC_DIR."layout/$application/PCG.inc";

	/// Common Interface

	/// Display Tpl
	$t->pparse("Output","CommonTemplate");

?>
