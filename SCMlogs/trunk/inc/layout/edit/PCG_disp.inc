<?php

	$t->setFile ("MainTemplate", "tpl/edit.html");

	$t->setVar ("VAR_PAGE_EDIT_MESSAGE", $DIS_EditMessage);
	$t->setVar ("VAR_PAGE_EDIT_TREE", $output_user_tree);
	$t->setVar ("VAR_PAGE_EDIT_MODULES", $output_modules);
?>
