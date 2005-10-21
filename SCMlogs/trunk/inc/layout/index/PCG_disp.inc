<?php

	switch ($subapp) {
		case "doc":
			$t->setFile ("MainTemplate", "tpl/doc.html");
			break;
		case "auth":
		default:
			if ($is_signed) {
				if ($is_authentificated) {
					if ($is_registring) {
						$t->setFile ("MainTemplate", "tpl/welcome.html");
					} else {
						$t->setFile ("MainTemplate", "tpl/welcome.html");
					}
				} else {
					$t->setFile ("MainTemplate", "tpl/confirm-login-box.html");
				}
			} else {
				$t->setFile ("MainTemplate", "tpl/login-box.html");
			}
			break;
	}

?>
