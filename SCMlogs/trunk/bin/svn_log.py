#!/usr/local/bin/python

# jfiat: 	This is a port/evolution of the contrib/log.pl 
# 			from the cvs 1.11 distribution
#
# 
# /usr/bin/python /home/jfiat/public_html/Berlios/djocewebtools/SCMLogs/bin/svn_log.py -rev $REV -repo $REPOS -l /home/jfiat/svndir/LOGS/commits.txt
#
# Usage:  log.py [-u user] [-i cvsinfo] [-s] -f logfile 
#
#	-u user		- $USER passed from loginfo
#	--svn-repo=
#	-s			- to prevent "cvs status -v" messages
#	-f logfile	- for the logfile to append to
#
#
# here is what the output looks like:
#
#
#	 ****************************************
#    Date: Wednesday November 23, 1994 @ 14:15
#    Author: woods
#	 Info:	 test3,1.12,1.13 test6,NONE,1.3 test4,1.6,NONE
#
#    Update of /local/src-CVS/testmodule
#    In directory kuma:/home/kuma/woods/work.d/testmodule
#    
#    Modified Files:
#    	test3 
#    Added Files:
#    	test6 
#    Removed Files:
#    	test4 
#    Log Message:
#    wow, what a test

import os;
import sys;
import string;
import subprocess;
from time import strftime, localtime, time;

def usage ():
	return """
Usage:  svn_log.py [-u user] [-i cvsinfo] [-s] -l logfile 

	-u user		- $USER passed from loginfo
	-i cvsinfo	- to pass the %{sVv} information : file,old,new .
	-s			- to prevent "cvs status -v" messages
	-f logfile	- for the logfile to append to
"""

def output_of (cmd):
	output = subprocess.Popen(string.split (cmd), stdout=subprocess.PIPE).communicate()[0]
	return output[:-1]

if __name__ == '__main__':
	logfile = '';
	revision = '';
	repository = '';
	argc = len (sys.argv) ;
	i = 1;
	while i < argc:
		arg = sys.argv[i];
		i = i + 1;
		if arg == '-rev' :
			revision = sys.argv[i]
			i = i + 1;
		elif arg == '-repo' :
			repository = sys.argv[i]
			i = i + 1;
		elif arg == '-l' :
			logfile = sys.argv[i]
			i = i + 1;
		#else :
			#nop
			#print "? Ignored : [%s] ?" %(arg);

	if logfile == '':
		print "You must specify at least the logfile"
		print usage ();
		sys.exit ();

	#date = strftime ("%A %B %d, %Y @ %H:%M:%S", localtime(time()))
	### Let's get the message content (from CVS)
	text = ''
	text_dirchanged = output_of ("svnlook dirs-changed %s -r %s" %(repository, revision))
	text_changed = output_of ("svnlook changed %s -r %s" %(repository, revision))
	text_logs = output_of ("svnlook log %s -r %s" %(repository, revision))

	login = output_of ("svnlook author %s -r %s" % (repository, revision))
	if len (login) == 0:
		login = os.environ['USER'] + "?"
	date = output_of ("svnlook date %s -r %s" % (repository, revision))

	text = "%s\n" 				% (text)

	### Build the log text
	text = "****************************************\n";
	text = "%sDate:\t%s\n" 		% (text, date)
	text = "%sAuthor:\t%s\n" 	% (text, login)
	text = "%sRevision:\t%s\n" 	% (text, revision)
	text = "%sDirChanged:%d\n%s\n" 	% (text, 1 + string.count (text_dirchanged,"\n"), text_dirchanged)
	text = "%sChanged:%d\n%s\n" 	% (text, 1 + string.count (text_changed,"\n"), text_changed)
	text = "%sLogs:%d\n%s\n" 	% (text, string.count (text_logs, "\n"), text_logs)
	text = "%s\n" 				% (text)

	### Save the log text in the log file
	z_logfile = open (logfile, 'a');
	z_logfile.write (text)
	z_logfile.close ();

	sys.exit();
