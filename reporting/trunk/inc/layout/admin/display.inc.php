<?php

	$smarty->assign ("PageMenuSrc", "menu.tpl");

	if (!$is_admin) {
		$smarty->assign("PageMainSrc","admin-login.tpl");
	} else {
		$smarty->assign("PageMainSrc","admin.tpl");
		$smarty->assign("VAR_ADMIN_PASSWORD",$admin);
		$smarty->assign("VAR_ADMIN_MESSAGE",$DIS_AdminMessage);
		$smarty->assign("VAR_ADMIN_YEAR",$DIS_Year);
		$smarty->assign("VAR_ADMIN_SEND_WEEK",$DIS_CurrentWeek);

		$smarty->assign("ListWeeks",$DIS_Weeks);
		$smarty->assign("ListYears",$DIS_Years);
	}
	$smarty->assign("VAR_APPLICATION_NAME", $DIS_Application);

?>
