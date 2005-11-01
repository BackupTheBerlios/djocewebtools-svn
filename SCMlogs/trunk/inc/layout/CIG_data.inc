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
	$DIS_REPOSITORY = SCMLogs_Repository();
	$DIS_REPO_BROWSING = SCMLogs_WebBrowsing();

	if (isset ($SCMLOGS['repository_list_id'])) {
		$ids = $SCMLOGS['repository_list_id'];
		$html = ' <form action="'.$this_url.'" method="GET"><input type="submit" value="&gt;&gt;" />';
		$html .= '<select name="repo">';
		foreach ($ids as $k_id => $v_id) {
			$html .= '<option value="'.$v_id.'" ';
			if ($v_id == $SCMLOGS['repository_id']) {
				$html .= ' SELECTED ';
			}
			$html .= '>'.$v_id.'</option>';
		}
		$html .= '</select></form>';
		$DIS_VAR_PAGE_REPO_LIST = $html;
	} else {
		$DIS_VAR_PAGE_REPO_LIST = '';
	}

?>
