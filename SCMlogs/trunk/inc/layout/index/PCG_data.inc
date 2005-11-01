<?php

	if (!isset($op) && isset ($_GET['op'])) { $op = $_GET['op']; }
	if (!isset ($subapp)) { $subapp = 'auth'; }


	$is_registring = isset ($op) && ($op == "register");
	$is_exiting = isset ($op) && ($op == "exit");

	if ($is_signed) {
		if ($is_registring) {
			createUserFile ($SCMUSER);
			$_SESSION = $SCMUSER;
			$is_authentificated = True;
		} elseif ($is_exiting) {
			$_SESSION['user'] = Null;
			unset ($_SESSION['user']);
		}
		$DIS_Application = "login";
	} else {
		$DIS_Application = "login";
	}

?>
