<?php

require_once SITE_INC_DIR."/core/siteapplication.class.php";

class Scmlogs_SiteManager extends SiteManager {
	var $config;
	var $appname;
	var $application;
	var $baseurl;
	var $title;
	var $auth;

	var $tpl_engine;
	function Scmlogs_SiteManager (&$cfg) {
		parent::SiteManager(&$cfg);
	}

	function prepareOutput() {
		include LIB_DIR."template.inc";
		$t =& new Template;
		$this->tpl_engine =& $t;
		include INC_DIR."layout/CIG.inc";
		include INC_DIR."layout/$application/PCG.inc";
		$this->application->getOutput();
	}
	function printOutput() {
		$this->application->printOutput();
		$this->tpl_engine->pparse("Output","CommonTemplate");
	}


}

?>
