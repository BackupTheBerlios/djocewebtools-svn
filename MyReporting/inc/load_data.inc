<?php

Function loadUsersInformation () {
	global $reporting;
	global $reporters_filename;

	// Users //
	$reporting ["users"] = array ();
	$fn = $reporters_filename;
	$fp = fopen ($fn, "r");
	while ($data = fgetcsv ($fp, filesize ($fn), ',')) {
		$user = new ReportingUser (trim($data[0]), trim($data[1]), trim($data[2]), trim($data[3]), (trim($data[4]) == 'Active'));
		$reporting ["users"][trim($data[0])] = $user; 
	}

	// Categories //
	include DATA_DIR."categories.txt";
}

?>
