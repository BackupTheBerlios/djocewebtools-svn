<?php

	$smarty->assign("PageMenuSrc","menu.tpl");

	switch ($DIS_ShowOverview) {
		case "why":
			$smarty->assign("PageMainSrc","overview-why.tpl");
			break;
		case "front":
		default:
			$smarty->assign("PageMainSrc","overview.tpl");
		}

	$smarty->assign("VAR_APPLICATION_NAME", $DIS_Application);

?>
