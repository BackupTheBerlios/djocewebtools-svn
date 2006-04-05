<?php

class BasicAuth extends SiteAuthentification {
	var $expireTime;

	function BasicAuth($cfg) {
		parent::SiteAuthentification (&$cfg);
	}

	function initialize() {
		$expireTime = 60*60*24*100; // 100 days
		session_set_cookie_params($expireTime);
		session_start();
	}

	Function authentificate() {
		global $_SESSION;
//		echo "<pre>"; print_r ($_SESSION); echo "</pre>";
		if (isset($_SESSION['user'])) {
			$this->signed_username = $_SESSION['user'];
		}
	}

	function loginUser($u, $p) {
		global $_SESSION;
		if ($u == 'jfiat') {
			$_SESSION['user'] = $u;
			$this->signed_username = $u;
			return TRUE;
		} else {
			unset($_SESSION['user']);
			$this->signed_username = Null;
			return FALSE;
		}
	}

	function logoutUser($user) {
		// check $user == $this->user();
		$_SESSION['user'] = Null;
		$_COOKIE['user'] = Null;
		unset($_SESSION['user']);
		$this->signed_username = Null;
	}

}


?>
