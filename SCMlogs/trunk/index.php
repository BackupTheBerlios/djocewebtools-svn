<?php
error_reporting (55);
ini_set ("session.use_trans_sid", 1);
//ini_set('magic_quotes_runtime', 0);
//ini_set('magic_quotes_gpc', 0);

/* Defines */
define('ROOT_DIR', realpath(dirname(__FILE__)).DIRECTORY_SEPARATOR);
define('SITE_INC_DIR', ROOT_DIR.'fmwk'.DIRECTORY_SEPARATOR.'inc'.DIRECTORY_SEPARATOR);
define('SITE_DIR', ROOT_DIR.'inc'. DIRECTORY_SEPARATOR .'site'.DIRECTORY_SEPARATOR );
define('SITE_PARAM_APP', 'app');
define('SITE_PARAM_OP', 'op');

/* Includes */
require_once SITE_INC_DIR.'common'.DIRECTORY_SEPARATOR.'misc.inc.php';
require_once SITE_INC_DIR.'core'.DIRECTORY_SEPARATOR.'siteconfiguration.class.php';
require_once SITE_INC_DIR.'core'.DIRECTORY_SEPARATOR.'siteauthentification.class.php';
require_once SITE_INC_DIR.'core'.DIRECTORY_SEPARATOR.'sitemanager.class.php';

/* Configuration */
include "conf/config.inc";

$_sitecfg =& new SiteConfiguration();
$_sitecfg->set_value('site.baseurl', 'index.php');
$_sitecfg->set_value('site.title', 'SCMlogs');
$_sitecfg->set_value('site.default_application', 'index');
$_sitecfg->set_value('site.htpasswd', $SCMLOGS['htpasswd.filename']);

/* WebSite */
require_once SITE_INC_DIR.'auth/PearAuthHtpasswd.php';
$_siteauth =& new SitePearAuthHtpasswd(&$_sitecfg, $_sitecfg->value('site.htpasswd'));
$_sitemgr =& new SiteManager(&$_sitecfg);

/* Main Application */

include "inc/require.inc";
include "inc/datamanager.inc";
require_once SITE_DIR.'apps'.DIRECTORY_SEPARATOR."scmapp.php";

if (!isset($application)) {
	$application = value_from_POST_GET (SITE_PARAM_APP, $_sitecfg->value('site.default_application'));
}

$_sitemgr->initialize(&$_siteauth);
$_sitemgr->registerApplication($application);
$_sitemgr->prepareData();
//echo 'No data should be posted before this<br/>';
$_sitemgr->printOutput();

?>
