<?php

Function loadUsersInformation () {
	global $reporting;
	global $reporters_filename;

	// Users //
	$reporting ["users"] = array ();
	$fn = $reporters_filename;
	$fp = fopen ($fn, "r");
	while ($data = fgetcsv ($fp, filesize ($fn), ',')) {
		$user = new ReportingUser ($data[0], $data[1], $data[2], $data[3], ($data[4] == 'Active'));
		$reporting ["users"][$data[0]] = $user; 
	}

	// Categories //
	include DATA_DIR."categories.txt";
}

?>
