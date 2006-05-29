<?php

	$DIS_Title = "Weekly Activity Reports";

	$DIS_MyReportingUrl = MyReportingUrl();
	if (isset($GLOBALS['username'])) { $username = $GLOBALS['username']; }
	if (isset ($username) && strlen ($username) > 0) {
		$reporter = ($GLOBALS['reporting']['users'][$username]);
		$DIS_reporter_name = $reporter->name;
		$DIS_reporter_team = $reporter->team;
	}

	if (!isset ($username)) {
		$username = value_from_POST ('username');
	}
	$year = value_from_POST_GET ('year');
	$week = value_from_POST_GET ('week');

// Display
	$smarty->assign ("VAR_REPORTING_URL", $DIS_MyReportingUrl);
	$smarty->assign("VAR_HEADER_TITLE",$DIS_Title);
	$smarty->assign("VAR_APPLICATION_TITLE",$DIS_Title);
	if (isset ($DIS_reporter_name)) {
		$smarty->assign("VAR_REPORTER_NAME",$DIS_reporter_name);
	} else {
		$smarty->assign("VAR_REPORTER_NAME","");
	}

	if (isset ($DIS_reporter_team)) {
		$smarty->assign("VAR_REPORTER_TEAM",$DIS_reporter_team);
	} else {
		$smarty->assign("VAR_REPORTER_TEAM","");
	}

	if (isset($DIS_Application)) {
		$smarty->assign("VAR_APPLICATION_NAME",$DIS_Application);
	}

?>
