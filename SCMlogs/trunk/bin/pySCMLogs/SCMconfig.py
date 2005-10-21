#!/usr/bin/python
import ConfigParser
import sys
from string import replace, split;

# class Declaration
class SCMconfig:
	def __init__ (self, cfg_file, opt_repo):
		self._filename = cfg_file;
		cfg = ConfigParser.ConfigParser()
		try:
			cfg.read (cfg_file)
			self.load_options (cfg, opt_repo)
		except:
			self.error ("\n\n[!] Error while reading configuration from: \n%s\n" %(cfg_file) );

	def error (self, m):
		sys.stderr.write (m)
		sys.exit(2);

	def option (self, cfg, sect, name):
		try:
			return cfg.get (sect, name)
		except ConfigParser.NoSectionError:
			self.error ("\n\n[!] Error in config : section [%s] is missing.\n" %(sect) );
		except ConfigParser.NoOptionError:
			self.error ("\n\n[!] Error in config : option [%s] is missing.\n" %(name) );

	def remove_double_quotes (self, text):
		return replace (text, '"', '')

	def load_options (self, cfg, repo):
		# Global
		self.SCMlogs_appdir = self.option (cfg, "global", "SCMlogs_appdir")
		self.SCMlogs_appurl = self.remove_double_quotes (self.option (cfg, "global", "SCMlogs_appurl"))
		if cfg.has_option ("global", "user_cfg_dir"):
			self.user_cfg_dir = self.option (cfg, "global", "user_cfg_dir")
		else:
			self.user_cfg_dir = "%sdata" % (self.SCMlogs_appdir)
		self.user_cfg_ext = self.option (cfg, "global", "user_cfg_extension")
		self.user_pref_ext = self.option (cfg, "global", "user_pref_extension")
		# SCM mode
		if len(repo) > 0:
			if cfg.has_section (repo):
				self.SCMrepository = repo
			else:
				self.error ("Repository id specified in argument [%s] is not valid\n" % (repo));
		else:
			if cfg.has_option("global", "SCM_repositories"):
				repositories = self.option (cfg, "global", "SCM_repositories")
				self.SCMrepository = repositories.split (',')[0]
			if cfg.has_option("global", "SCM_default_repository"):
				self.SCMrepository = self.option (cfg, "global", "SCM_default_repository")

		self.SCMmode = self.option (cfg, self.SCMrepository, "mode")
		self.repository_path = self.option (cfg, self.SCMrepository, "repository_path")
		self.repository_name = self.option (cfg, self.SCMrepository, "repository_name")
		self.logs_dir = self.option (cfg, self.SCMrepository, "logs_dir")
		# Browsing
		if cfg.has_option ("global", "browsing"):
			self.browsing = self.option (cfg, "global", "browsing")
			self.webapp_url = self.remove_double_quotes (self.option (cfg, self.browsing, "webapp_url"))
		else:
			self.browsing = ""
			self.webapp_url = "%s%s" % (self.SCMlogs_appurl, "webscmlogs.php")
		# Email
		self.smtp_server = self.option (cfg, "email", "smtp_server")
		self.at_domain_name = self.option (cfg, "email", "at_domain_name")
		self.superuser_name = self.option (cfg, "email", "superuser_name")
		self.superuser_email = self.option (cfg, "email", "superuser_email")
		self.organization_name = self.option (cfg, "email", "organization_name")
