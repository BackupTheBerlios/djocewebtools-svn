<?php

	$smarty->assign ("PageMenuSrc", "menu.tpl");


	if (!$has_confirmation) {
		$smarty->assign ("PageMainSrc", "save-confirm.tpl");
		$smarty->assign("VAR_SAVE_USERNAME", $DIS_Username);
		$smarty->assign("VAR_SAVE_YEAR", $DIS_Year);
		$smarty->assign("VAR_SAVE_WEEK", $DIS_Week);
		$smarty->assign("VAR_SAVE_RELATED_DATE", $DIS_SaveRelatedDate);

		$smarty->assign("VAR_SAVE_PREVIEW", $DIS_PreviewText);
		$DIS_PreviewText = ereg_replace("&", "&amp;",$DIS_PreviewText);
		$smarty->assign("VAR_SAVE_TEXT", $DIS_PreviewText);
	} else  {
		$smarty->assign ("PageMainSrc", "save.tpl");
	}
	$smarty->assign("VAR_SAVE_MESSAGE", $DIS_SaveMessage);

	$smarty->assign("VAR_APPLICATION_NAME", $DIS_Application);

?>
