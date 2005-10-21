#!/usr/bin/python

import sys;
import os;
from time import *
from pySCMLogs.SCMconfig import SCMconfig

repo = 'svndir'
class CommitsManager:
	def __init__ (self, cfg, repo):
		self.repo = repo
		self.load_config (cfg)

	def load_config (self, cfg):
		config = SCMconfig(cfg, repo)
		self.config = config
		self.SCMlogs_appdir = config.SCMlogs_appdir
		self.dirname = config.logs_dir
		self.sendlogs_cmd = "/usr/bin/python %sbin/scm_sendlogs.py" % (self.SCMlogs_appdir);

	def execute(self):
		filename = "%s/%s" %(self.dirname, "commits.txt");
		file = open (filename, 'r');
		commits = file.read();
		size = len (commits);
		file.close ();

		if size > 5: 
			year = strftime ("%Y", localtime(time()))
			month = strftime ("%m", localtime(time()))

			yearcommitdirname = "%s/%s" %(self.dirname, year)
			commitdirname = "%s/%s" %(yearcommitdirname, month)

			if not os.path.exists (yearcommitdirname) :
				os.mkdir (yearcommitdirname);
			if not os.path.exists (commitdirname) :
				os.mkdir (commitdirname);

			file_key = strftime ("%Y-%m-%d", localtime(time()))
			destfilename = "%s/%s" %(commitdirname, file_key)

			destfile = open (destfilename, 'a+');
			destfile.write (commits);
			destfile.close ()

			file = open (filename, 'w');
			file.close ();
			self.send_email (file_key)

	def send_email (self, file_key):
			# sending email
			cmd = "%s -k %s --mail" % (self.sendlogs_cmd, file_key)
			if len (self.config._filename) > 0:
				cmd = "%s --cfg=%s " % (cmd, self.config._filename)
			if len (self.repo) > 0:
				cmd = "%s --repo=%s" % (cmd, self.repo);
			os.system (cmd);

###############################################
### Main Program							###
###############################################

if __name__ == '__main__':
	cfg_fn = "%s/../conf/%s" % (os.getcwd(), 'SCMlogs.conf')
	obj = CommitsManager(cfg_fn, 'svndir')
	obj.execute();

