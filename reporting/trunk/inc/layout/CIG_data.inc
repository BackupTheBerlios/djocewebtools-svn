<?php

	/// Fill Data

	$DIS_Title = "Weekly Activity Reports";

	$DIS_MyReportingUrl = MyReportingUrl();
	$t->setVar ("VAR_REPORTING_URL", $DIS_MyReportingUrl);

	if (isset($GLOBALS['username'])) { $username = $GLOBALS['username']; }
	if (isset ($username) && strlen ($username) > 0) {
		$reporter = ($GLOBALS['reporting']['users'][$username]);
		$DIS_reporter_name = $reporter->name;
		$DIS_reporter_team = $reporter->team;
	} else {
	}

	if (isset($_POST['username'])) { $username = $_POST['username']; }

	if (!isset($year) && isset($_POST['year'])) { $year = $_POST['year']; }
	if (!isset($year) && isset($_GET['year'])) { $year = $_GET['year']; }

	if (!isset($week) && isset($_POST['week'])) { $week = $_POST['week']; }
	if (!isset($week) && isset($_GET['week'])) { $week = $_GET['week']; }


?>
