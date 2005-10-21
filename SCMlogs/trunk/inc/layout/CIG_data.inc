<?php

	include "inc/users.inc";

	if (!isset($SCMUSER) && isset ($_GET['user'])) { $SCMUSER = $_GET['user']; }
	if (!isset($SCMUSER) && isset ($_POST['user'])) { $SCMUSER = $_POST['user']; }

	/// Fill Data

	if (isset ($SCMUSER)) {
		$is_signed = True;
		$DIS_User = $SCMUSER;
		$DIS_Title = " :: Welcome $SCMUSER";

		$is_authentificated = user_exists ($SCMUSER);
	} else {
		$is_signed = False;
		$is_authentificated = False;
		$DIS_Title = " :: Authentification";
	}
	$DIS_REPOSITORY = SCMLogs_Repository();
	$DIS_REPO_BROWSING = SCMLogs_WebBrowsing();

?>
