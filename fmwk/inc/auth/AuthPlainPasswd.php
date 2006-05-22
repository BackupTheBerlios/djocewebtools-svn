<?php

class SiteAuthPlainPasswd extends SiteAuthentification {
	var $passwd_filename;

	function SiteAuthPlainPasswd($cfg, $passwd_filename) {
		parent::SiteAuthentification (&$cfg);
		$this->passwd_filename = $passwd_filename;
	}

	function initialize() {
		parent::initialize();
	}

	Function Authentificate() {
		global $_SESSION;
		//echo "<pre>"; print_r ($_SESSION); echo "</pre>";
		if (isset($_SESSION['username'])) {
			$this->signed_username = $_SESSION['username'];
		}
	}

	function loginUser($u, $p) {
		global $_SESSION;

		if (!file_exists($this->passwd_filename)) {
			$this->signed_username = Null;
			unset($_SESSION['username']);
			return FALSE;
		} else {
			$res = FALSE;
			$txt = ContentOfFile($this->passwd_filename);
			$lines = split("\n", $txt);
			foreach ($lines as $line) {
				list($un,$pn) = explode ('=', $line, 2);
				if (trim($un) == $u) {
					$res = (trim($pn) == $p);
					break;
				}
			}
			if ($res) {
				$_SESSION['username'] = $u;
				$this->signed_username = $u;
				return TRUE;
			} else {
				$this->signed_username = Null;
				unset($_SESSION['username']);
				return FALSE;
			}
		}
	}

	function logoutUser($user=NULL) {
		// check $user == $this->user();
		$_SESSION['username'] = Null;
		$_COOKIE['username'] = Null;
		unset($_SESSION['username']);
		$this->signed_username = Null;
	}

}


?>
