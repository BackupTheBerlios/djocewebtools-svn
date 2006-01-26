<?php

	include "inc/users.inc";

	if (!isset($SCMUSER) && isset ($_GET['user'])) { $SCMUSER = $_GET['user']; }
	if (!isset($SCMUSER) && isset ($_POST['user'])) { $SCMUSER = $_POST['user']; }
	if (!isset($SCMUSER) && isset ($_SESSION['user'])) { $SCMUSER = $_SESSION['user']; }

	/// Fill Data

	if (isset ($SCMUSER)) {
		$_SESSION['user'] = $SCMUSER;
		$is_signed = True;
		$DIS_User = $SCMUSER;
		$DIS_Title = " :: Welcome $SCMUSER";

		$is_authentificated = user_exists ($SCMUSER);
	} else {
		$_SESSION['user'] = Null;
		unset ($_SESSION['user']);
		$is_signed = False;
		$is_authentificated = False;
		$DIS_Title = " :: Authentification";
	}
	$repo =& SCMLogs_repository();
	$DIS_REPOSITORY = $repo->path;
	$DIS_REPO_BROWSING = SCMLogs_WebBrowsing();

	if (isset ($SCMLOGS['repositories'])) {
		$repos = $SCMLOGS['repositories'];
		$html = ' <form action="'.$this_url.'" method="GET"><input type="submit" value="&gt;&gt;" />';
		$html .= '<select name="repo">';
		foreach ($repos as $k_repoid => $v_repo) {
			$html .= '<option value="'.$v_repo->id.'" ';
			if ($v_repo->id == SCMLogs_repository_id()) {
				$html .= ' SELECTED ';
			}
			$html .= '>'.$v_repo->id.'</option>';
		}
		$html .= '</select></form>';
		$DIS_VAR_PAGE_REPO_LIST = $html;
	} else {
		$DIS_VAR_PAGE_REPO_LIST = '';
	}

?>
