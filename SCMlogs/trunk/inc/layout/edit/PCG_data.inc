<?php

	include "inc/show_config_tree.inc";


	if (!isset ($optree) && isset ($_POST['optree'])) { $optree = $_POST['optree']; }
	if (!isset ($optext) && isset ($_POST['optext'])) { $optext = $_POST['optext']; }
	if (!isset ($modules) && isset ($_POST['modules'])) { $modules = $_POST['modules']; }

	$user =$SCMUSER;

	if (isset ($optree) or isset ($optext)) {
		if (isset ($optree) and ($optree == 'SaveTree')) {
			if (!isset ($modules)) { echo "Error: modules data are not present\n"; exit (); }
			#displayModules ($modules);
			saveModulesFor ($modules, $user);
		} 
		if (isset ($optext) and ($optext == 'SaveText')) {
			if (!isset ($modules)) { echo "Error: modules data are not present\n"; exit (); }
			saveTextModulesFor ($modules, $user);
		}

		$DIS_EditMessage = "Changes saved for user [<STRONG> $user </STRONG>] ... ";
	} else {
		$DIS_EditMessage = "";
	}


	$user_modules = userModules ($user);
	$all_modules = allModules ();

	ob_start ();
	showAllModulesWithSelectionTree ($all_modules, $user_modules);
	$output_user_tree = ob_get_contents();
	ob_end_clean();

	ob_start ();
	include "inc/show_config.inc"; 
	$output_modules = ob_get_contents();
	ob_end_clean();

?>
