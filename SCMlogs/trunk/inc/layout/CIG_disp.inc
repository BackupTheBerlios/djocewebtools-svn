<?php

	/// Fill Tpl Data

	$t->setFile("CommonTemplate","tpl/common.html");	
	if ($is_signed) {
		$t->setFile("MenuTemplate","tpl/menu-user.html");
		$t->setVar("VAR_USER", $DIS_User);
	} else {
		$t->setFile("MenuTemplate","tpl/menu-login.html");
	}

	$t->setVar("VAR_TITLE", $DIS_Title);
	$t->setVar("VAR_REPOSITORY", $DIS_REPOSITORY);
	$t->setVar("VAR_REPO_BROWSING", $DIS_REPO_BROWSING);
	$t->setVar("VAR_PAGE_REPO_LIST", $DIS_VAR_PAGE_REPO_LIST);

	$t->parse("VAR_PAGE_MENU","MenuTemplate");
?>
