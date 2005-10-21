<?php

if (! defined("_DATAMANAGER_")) { define ("_DATAMANAGER_", 1);

	require "conf/config.inc";
	require "lib/file.inc";

	Function listOfUsers () {
		global $SCMLOGS;
		$filter = "[a-z_\.]*.cfg$";
		$ls_result = listDirFilter ($SCMLOGS['datadir'], $filter);
		$result = array();
		while (list($key, $val) = each ($ls_result)) {
			$result[] = substr ($val, 1 + strlen ($SCMLOGS['datadir']), - strlen (',cfg') );
		}
		return $result;
	}

	Function saveUserPref ($pref, $user) {
		SaveTextIntoFile ($pref, userPrefFilename ($user));
	}

	Function loadUserPref ($user) {
		global $SCMLOGS;
		$fn = userPrefFilename ($user);
		if (file_exists ($fn)) {
		} else {
			$fn = userPrefDefaultFilename ();
		}
		$tmp_pref = split ("\n", ContentOfFile ($fn));
		while (list ($k, $pref) = each ($tmp_pref)) {
			$pos = strpos ($pref, "=");
			if ($pos > 0) {
				$var = trim (substr($pref, 0, $pos));
				$val = trim (substr($pref, $pos + 1));
				$SCMLOGS[$var]=$val;
			}
		}
	}

	Function displayCurrentUserPref () {
		global $SCMLOGS;
		echo "<BR>AAA".$SCMLOGS['send_format']."BBB<BR>";
		while (list($k, $v) = each ($SCMLOGS)) {
			echo "<LI>$k = $v</LI>\n";
		}
	}
	Function userPrefFilename ($user) {
		global $SCMLOGS;
		return $SCMLOGS['datadir']."/".$user.".pref";
	}
	Function userCfgDefaultFilename () {
		global $SCMLOGS;
		return $SCMLOGS['datadir']."/cfg.tpl";
	}
	Function userPrefDefaultFilename () {
		global $SCMLOGS;
		return $SCMLOGS['datadir']."/pref.tpl";
	}
	Function userConfigFilename ($user) {
		global $SCMLOGS;
		return $SCMLOGS['datadir']."/".$user.".cfg";
	}

	Function userCfgDefaultText() {
		$fn = userCfgDefaultFilename();
		if (file_exists ($fn)) {
			return ContentOfFile ($fn);
		} else {
			return "";
		}
	}

	Function createUserFile ($user) {
		saveTextModulesFor (userCfgDefaultText(), $user);
	}

	Function deleteUserFile ($user) {
		RemoveFile (userConfigFilename ($user));
		if (file_exists (userPrefFilename ($user))) {
			RemoveFile (userPrefFilename ($user));
		}
	}

	Function cleanedTextModule ($text_modules) {
		$modules = split ("\n", $text_modules);
		$modules = convertSimpleModListToModRespList ($modules);
		return cleanTextListOfModules ($modules);
	}

	Function saveTextModulesFor ($text_modules, $user) {
		$modules = split ("\n", $text_modules);
		//$modules = convertSimpleModListToModRespList ($modules);
		saveModulesFor ($modules, $user);
	}

	Function saveModulesFor ($modules, $user) {
		$modules = convertSimpleModListToModRespList ($modules);
		$text = cleanTextListOfModules ($modules);
		//echo "<PRE>$text</PRE>";
		SaveTextIntoFile ($text, userConfigFilename ($user));
	}

	Function displayModules ($modules) {
		while (list ($mod,$val) = each ($modules)) {
			echo "- $mod<BR>\n";
		}
	}

	Function toValidModuleName ($modname) {
		$result = trim ($modname);
		if (substr ($result, strlen ($result) - 1) == '/') {
			$result = substr ($result, 0, strlen ($result) -1);
		}
		return $result;
	}

	Function userModules ($user) {
		if (!isset ($user)) { echo "ERROR: user is not set !"; exit(); }
		$tmp_cfg = ContentOfFile (userConfigFilename ($user));
		//echo "<PRE>$tmp_cfg</PRE>";
		$lst = split ("\n", $tmp_cfg);
		return convertSimpleModListToModRespList ($lst);
	}
	Function userModulesText ($user) {
		return  ContentOfFile (userConfigFilename ($user));
	}

	Function allModules () {
		global $SCMLOGS;
		$all_cfg = ContentOfFile ($SCMLOGS['datadir']."/all.tpl");
		$lst = split ("\n", $all_cfg);
		return convertSimpleModListToModRespList ($lst);
	}

	Function convertSimpleModListToModRespList ($lst) {
		$tmp_mods = array ();
		while (list ($k, $mod) = each ($lst)) {
			if (strpos ($mod, ":")) {
				list($modname, $users) = split(":", $mod, 2); 
			} else {
				$modname = "$mod";
				$users = " ";
			}
			$modname = toValidModuleName ($modname);
			if ($modname != '') {
				$list_of_resps = split (",", $users);
				while (list ($k, $usr) = each ($list_of_resps)) {
					$usr = trim ($usr);
					if ($usr == '') {
						unset ($list_of_resps[$k]);
					} else {
						$list_of_resps[$k] = $usr;
					}
				}
				$tmp_mods [$modname] = $list_of_resps;
			}
		}
		return $tmp_mods; 
	}

	Function cleanTextListOfModules ($modules) {
		$tree = array ();
		while (list ($path, $resps) = each ($modules)) {
			$tree = addToSelectionTree ($path, $tree);
		}
		$text = textOfCleanTreeOfModules ('', $tree);
		return $text;
	}

	Function textOfCleanTreeOfModules ($fullpath, $tree) {
		$text = '';
		while (list ($key, $val) = each ($tree)) {
			if ($val == '*') { 
				$text .= "$fullpath$key\n";
			}
			if (is_array ($val)) {
				$text .= textOfCleanTreeOfModules ("$fullpath$key/", $val);
			}
		}
		return $text;
	}

	Function addToSelectionTree ($path, $tree) {
		$pos = strpos ($path, '/', 0) ;
		if ($pos > 0) {
			$dir = substr ($path , 0, $pos);
			if (isset ($tree[$dir])) {
				$next = $tree[$dir];
			}
			else {
				$next = array();
			}
			if ($next == '*') {
				// Already selected from the parent
			} else {
				$rest = substr ($path , $pos + 1);
				$tree[$dir] = addToSelectionTree ($rest, $next);
			}
		} else {
			$tree[$path]='*'; //array();
		}
		return $tree;
	}

}
//else { echo "_DATAMANAGER_ Already loaded .."; }

?>