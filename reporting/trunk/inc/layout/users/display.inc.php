<?php

	$smarty->assign("PageMenuSrc","menu.tpl");

	if ($is_admin) {
		$smarty->assign("PageMainSrc","users-admin.tpl");
		$smarty->assign("VAR_USERS_ADMIN_TEXT", $DIS_UsersText);
	} else {

		$smarty->assign("PageMainSrc","users.tpl");
		$smarty->assign("VAR_APPLICATION_NAME", $DIS_Application);
		if ($do_save) {
			$smarty->assign("VAR_USERS_MESSAGE", $DIS_UsersMessage);
		}

		$bgcolor1 = "#ffffff";
		$bgcolor2 = "#eeeeee";
		$bgcolor = $bgcolor1;

		reset ($users);
		$smarty->assign("Users", $users);
	}

?>
