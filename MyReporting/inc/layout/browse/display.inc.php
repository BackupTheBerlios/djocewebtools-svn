<?php

	$smarty->assign ("PageMenuSrc", "menu.tpl");
	$smarty->assign ("PageMainSrc", "browse.tpl");

	$smarty->assign("VAR_APPLICATION_NAME", $DIS_Application);
	$smarty->assign ("ListYears", $DIS_ListYears);

	$smarty->assign ("ListUsers", $DIS_AllUsers);

?>
