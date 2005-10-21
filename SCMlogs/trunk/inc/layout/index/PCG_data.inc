<?php

	if (!isset($op) && isset ($_GET['op'])) { $op = $_GET['op']; }
	if (!isset ($subapp)) { $subapp = 'auth'; }


	$is_registring = isset ($op) && ($op == "register");

	if ($is_signed) {
		if ($is_registring) {
			createUserFile ($SCMUSER);
			$is_authentificated = True;
		}
		$DIS_Application = "login";
	} else {
		$DIS_Application = "login";
	}

?>
