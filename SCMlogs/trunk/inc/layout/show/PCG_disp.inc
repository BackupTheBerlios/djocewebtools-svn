<?php

	$t->setFile ("MainTemplate", "tpl/show.html");

	$t->setVar ("VAR_PAGE_SHOW_MESSAGE", $DIS_Message);
	$t->setVar ("VAR_PAGE_SHOW_PARAM", $DIS_Parameters);
	$t->setVar ("VAR_SELECTED_YEARS_GET", $DIS_GET_SelectedYear);
	$t->setVar ("VAR_PAGE_SHOW_FILES", $DIS_Files);
	$t->setVar ("VAR_PAGE_SHOW_COMMAND", $DIS_Command);
	if ($DIS_Format == 'text') {
		$t->setVar ("VAR_PAGE_SHOW_RESULT", "<PRE>$DIS_Result</PRE>");
	} else {
		$t->setVar ("VAR_PAGE_SHOW_RESULT", $DIS_Result);
	}

	$t->setVar ("VAR_FORMAT", $DIS_Format);

	if (isset ($only_user)) {
		$t->setVar ("VAR_ONLY_USER", $only_user);
	} else {
		$t->setVar ("VAR_ONLY_USER", '');
	}
	if (isset ($only_tag)) {
		$t->setVar ("VAR_ONLY_TAG", $only_tag);
	} else {
		$t->setVar ("VAR_ONLY_TAG", '');
	}

	$t->setBlock ("MainTemplate", "HiddenCommitFilesBlock", "HCF_B");
	reset ($commitsfiles);
	while (list ($k, $v_key) = each ($commitsfiles)) {
		$t->setVar ("VAR_ITEM_FILE_KEY", $v_key);
		$t->parse ("HCF_B", "HiddenCommitFilesBlock", True);
	}

?>
