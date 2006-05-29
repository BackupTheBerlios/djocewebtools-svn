<?php
$misc_fileloaded = True;
class ReportingUser {
	var $login;
	var $name;
	var $team;
	var $homepage;
	var $state;

	Function ReportingUser ($login, $name, $team, $homepage, $state) {
		$this->login = $login;
		$this->name = $name;
		$this->team = $team;
		$this->homepage = $homepage;
		$this->state = $state;
	}
};

?>
