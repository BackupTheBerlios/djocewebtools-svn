<?php

	$smarty->assign ("PageMenuSrc", "menu.tpl");
	$smarty->assign ("PageMainSrc", "browseuser.tpl");

	$smarty->assign("VAR_APPLICATION_NAME", $DIS_Application);
	$smarty->assign ("ListYearDirs", $reporting_dirs);
	$smarty->assign ("ListUserReports", $listUserReports);
	$smarty->assign ("SelectedYear", $selected_year);
	$smarty->assign ("SelectedUser", $DIS_AllUsers[$selected_user]);
	$smarty->assign("VAR_EDIT_USERNAME_HTML_SELECT", $DIS_PostUsername_HTML_SELECT);

?>
