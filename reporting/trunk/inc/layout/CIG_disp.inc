<?php

	/// Fill Tpl Data

	$t->setFile("CommonTemplate","tpl/common.html");	
	$t->setVar("VAR_HEADER_TITLE",$DIS_Title);
	$t->setVar("VAR_APPLICATION_TITLE",$DIS_Title);
	if (isset ($DIS_reporter_name)) {
		$t->setVar("VAR_REPORTER_NAME",$DIS_reporter_name);
	} else {
		$t->setVar("VAR_REPORTER_NAME","");
	}

	if (isset ($DIS_reporter_team)) {
		$t->setVar("VAR_REPORTER_TEAM",$DIS_reporter_team);
	} else {
		$t->setVar("VAR_REPORTER_TEAM","");
	}

	if (isset($DIS_Application)) {
		$t->setVar("VAR_APPLICATION_NAME",$DIS_Application);
	}

?>
