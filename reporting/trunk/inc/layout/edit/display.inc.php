<?php

	$smarty->assign ("PageMenuSrc", "menu.tpl");

	$smarty->assign("VAR_APPLICATION_NAME", $DIS_Application);

	if ($go_for_editing) {
		$smarty->assign("PageMainSrc","edit-report.tpl");

		if ($is_read_only) {
			$smarty->assign("VAR_EDIT_READ_ONLY", True );
		}
		$smarty->assign("VAR_EDIT_MESSAGE", $DIS_EditMessage);
		$smarty->assign("VAR_EDIT_USERNAME", $DIS_EditUsername);
		$smarty->assign("VAR_EDIT_RELATED_DATE", $DIS_EditRelatedDate);
		$smarty->assign("VAR_EDIT_WEEK", $DIS_EditWeek);
		$smarty->assign("VAR_EDIT_YEAR", $DIS_EditYear);
		if (isset ($DIS_EditReportingText)) {
			$DIS_EditReportingText = ereg_replace("&", "&amp;",$DIS_EditReportingText);
			$smarty->assign("VAR_REPORT_TEXT", $DIS_EditReportingText);
		}
	} else {
		$smarty->assign("PageMainSrc","edit-post.tpl");
		$smarty->assign("VAR_EDIT_USERNAME_HTML_SELECT", $DIS_PostUsername_HTML_SELECT);
		$smarty->assign("VAR_EDIT_CURRENT_WEEK_TEXT", $DIS_PostCurrent_Week_text);
		$smarty->assign("VAR_EDIT_YEAR_WEEK_HTML_RADIO_SELECT", $DIS_PostYearWeek_HTML_RADIO_SELECT);
		$smarty->assign("VAR_EDIT_CATEGORIES_CHECK_LIST", $DIS_PostCategories_HTML_CHECK_LIST);
		if (isset ($DIS_PostWarning)) {
			$smarty->assign("VAR_EDIT_WARNING", $DIS_PostWarning);
		}
	}

?>
