<?php
ini_set ("session.use_trans_sid", 1);

$this_url = $_SERVER['REQUEST_URI'];

ini_set('magic_quotes_runtime', 0);
ini_set('magic_quotes_gpc', 0);

session_start();

//echo "<pre>"; print_r ($_SERVER); echo "</pre>";
//echo "<pre>"; print_r ($_SESSION); echo "</pre>";

$username = $_SESSION['user'];

//error_reporting (55);

// Config
include "conf/config.inc";
include "inc/require.inc";
include "inc/datamanager.inc";

global $SCMLOGS;

	$_POST = $HTTP_POST_VARS ;
	$_GET = $HTTP_GET_VARS ;
	$_COOKIE = $HTTP_COOKIE_VARS ;

if (isset($_GET['repo'])) {
	$asked_repo = $_GET['repo'];
} elseif (isset ($_SESSION['repo'])) {
	$asked_repo = $_SESSION['repo'];
}
if (isset ($asked_repo)) {
	if ($asked_repo == $SCMLOGS['repository_id']) {
		$_SESSION['repo'] = Null;
		unset ($_SESSION['repo']);
	} else {
		SCMLogs_set_repository_id ($asked_repo);
		$_SESSION['repo'] = $SCMLOGS['repository_id'];
	}
}

// Cookies
	$w_user = Null;
	if (!isset($w_user) and isset($_POST['w_user'])) { $w_user = $_POST['w_user']; }
	if (!isset($w_user) and isset( $_GET['w_user'])) { $w_user =  $_GET['w_user']; }

	if (isset ($w_user)) { $username= $w_user; }

$_SESSION['user'] = $username;

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
