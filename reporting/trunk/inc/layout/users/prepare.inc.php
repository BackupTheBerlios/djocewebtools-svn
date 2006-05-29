<?php

	include LIB_DIR."file.inc";
	$DIS_Application = "Users";

	// Operation
	$op = value_from_POST_GET ('op');
	$do_save = isset($op) && $op == 'save';

	// Administration
	$admin = value_from_POST_GET ('admin');
	$is_admin = isset ($admin) && isValidAdminPassword($admin);

	if ($is_admin && !$do_save) {
		$DIS_UsersText = ContentOfFile (reportersFilename());
	} else {
		if ($do_save) {
			BackupFile (reportersFilename());
			SaveTextIntoFile ($_POST['userDataText'], reportersFilename());
			loadUsersInformation ();

			$DIS_UsersMessage = "Modification saved ..";
		}
		// Display
		$users = $GLOBALS['reporting']["users"];
	}

?>
