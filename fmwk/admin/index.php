<?php

/* Defines */
define('SITE_INC_DIR', realpath(dirname(__FILE__).DIRECTORY_SEPARATOR.'..').DIRECTORY_SEPARATOR.'inc'.DIRECTORY_SEPARATOR);
define('SITE_DIR', realpath(dirname(__FILE__)).DIRECTORY_SEPARATOR.'inc'.DIRECTORY_SEPARATOR);
define('SITE_PARAM_APP', 'app');
define('SITE_PARAM_OP', 'appop');

/* Includes */
require_once SITE_INC_DIR.'common'.DIRECTORY_SEPARATOR.'misc.inc.php';
require_once SITE_INC_DIR.'core'.DIRECTORY_SEPARATOR.'siteconfiguration.class.php';
require_once SITE_INC_DIR.'core'.DIRECTORY_SEPARATOR.'siteauthentification.class.php';
require_once SITE_INC_DIR.'core'.DIRECTORY_SEPARATOR.'sitemanager.class.php';

/* Configuration */
$_sitecfg =& new SiteConfiguration();
$_sitecfg->set_value('site.baseurl', 'index.php');
$_sitecfg->set_value('site.title', 'Test admin');
$_sitecfg->set_value('site.default_application', 'admin');

/* WebSite */
require_once SITE_INC_DIR.'/auth/BasicAuth.php';
$_siteauth =& new BasicAuth(&$_sitecfg);
$_sitemgr =& new SiteManager(&$_sitecfg);


/* Main Application */

if (!isset($application)) {
	$application = value_from_POST_GET (SITE_PARAM_APP, $_sitecfg->value('site.default_application'));
}

$_sitemgr->initialize(&$_siteauth);
$_sitemgr->registerApplication($application);
$_sitemgr->prepareData();
//echo 'No data should be posted before this<br/>';
$_sitemgr->printOutput();

?>
