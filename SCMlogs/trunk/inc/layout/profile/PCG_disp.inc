<?php

	$t->setFile ("MainTemplate", "tpl/profile.html");

	$t->setVar ("VAR_PROFILE_TREE", $output_user_tree);
	$t->setVar ("VAR_PROFILE_MODULES", $output_modules);
?>
