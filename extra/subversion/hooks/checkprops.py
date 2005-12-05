#!/usr/bin/python

### Config file
# put in your repository/conf
# the file 'config'
# with for instance:
# 
# [auto-props]
# *.e = svn:keywords=Author Date ID Revision
# *.c = svn:keywords=Author Date ID Revision
# *.cpp = svn:keywords=Author Date ID Revision
# *.h = svn:keywords=Author Date ID Revision
# Make* = svn:keywords=Author Date ID Revision
# *.bat = svn:keywords=Author Date ID Revision
# *.sh = svn:keywords=Author Date ID Revision
# *.bm = svn:keywords=Author Date ID Revision
#
### install hook
# in pre-commit  hook 
# REPOS="$1"
# TXN="$2"
# /usr/bin/python /path-to/checkprops.py $REPOS $TXN >> /tmp/svnlog || exit 1 
#
# exit 0
###

from ConfigParser import ConfigParser
from fnmatch import fnmatch
import sys,os
#from subprocess import Popen, PIPE
import popen2;
from string import split, lower

repos = sys.argv[1]
trans = sys.argv[2]

SVNLOOK = "/usr/bin/svnlook"
CONFIG = "%s/conf/config" % repos

nb_of_failures_before_error = 5
log_enabled = 0
logfilename ="/home/svn/logs/checkprops.log"
#logfile = None;
#global log_enabled, logfile;
if log_enabled:
	try:
		logfile = open (logfilename, 'a')
	except:
		sys.stderr.write ("Checkprops#: unexpected error: %s \n" %(sys.exc_info()[0]))
		sys.stderr.write ("Checkprops#: unexpected error: %s \n" %(sys.exc_info()[1]))
		sys.stderr.write ("Checkprops#: unexpected error: %s \n" %(sys.exc_info()[2]))
		sys.stderr.write ("Checkprops: failed : [%s] is not writable\n" % (logfilename))
		log_enabled = 0
		sys.exit(1);

def log_message(msg):
	global log_enabled, logfile;
	if log_enabled:
		logfile.write (msg)
		logfile.flush ()

def checkPath(path,autoprops):
  log_message ("checkPath: [%s]\n" % (path));
  #sys.stderr.write ("Checking autoprops on [%s] ...\n" % (path))
  okay = 1
  is_dir = (path[-1] == '/')
  for pattern in autoprops.keys():
    #log_message("#Pattern [%s] \n" % (pattern))
    if fnmatch(path,pattern):
      #log_message("#Match [%s ~ %s] \n" % (pattern, path))
      items = autoprops[pattern]
      for item in items:
        propname = item[0]
        log_message("#Propname [%s] \n" % (propname))
        if is_dir and propname == 'svn:keywords':
          log_message ("Skip checking %s on directory [%s] ...\n" % (propname, path))
        else:
          expected = item[1] # already lower case
          cmd = "%s propget -t %s %s %s %s" % (SVNLOOK,trans,repos,propname,path)
          #propget = Popen(split (cmd), stdout=PIPE).stdout
          #log_message("Launch command=%s \n" % (cmd))
          (propget, prop_in) = popen2.popen4(cmd)
          #log_message("Read output \n")
          propval = lower(propget.read())
          status = propget.close()
          prop_in.close()
          #log_message("Finish command \n")
          if propval.find(expected) < 0:
            okay = 0
            #if not status:
            #sys.stderr.write("Property value '%s=%s' not found (or not expected) on path '%s'\n" % (propname,expected,path))
            sys.stderr.write("Props '%s=%s' missing (or not expected)\n" % (propname,expected))
  log_message ("checkPath: [%s] done\n" % (path));
  return okay

try:
	log_message ("checkprop: start\n");
	hr = "-" * 74 + "\n"

	config = ConfigParser()
	config.read(CONFIG)
	autoprops = dict(config.items("auto-props"))
	for pattern in autoprops.keys():
		s_props = autoprops[pattern]
		props_items=[]
		props = s_props.split(";")
		for p in props:
			s_pn = p.split("=")
			if s_pn[0] == "svn:keywords":
				s_pn[1] = lower (s_pn[1]);
			props_items.append (s_pn)
		autoprops[pattern] = props_items

	failures = 0
	cmd = "%s changed -t %s %s" % (SVNLOOK,trans,repos)
	(cmd_out, cmd_in) = popen2.popen2(cmd)
	changes = cmd_out.readlines()
	cmd_out.close()
	cmd_in.close()
	for change in changes:
	  if change[0] == 'A':
	    path = change[4:].strip()
	    if not checkPath(path,autoprops):
	      sys.stderr.write("Props issue on: %s\n" % path)
	      sys.stderr.write(hr)
	      failures = failures + 1
	  if nb_of_failures_before_error > 0 and failures >= nb_of_failures_before_error:
	    break;
	log_message ("checkprop: done\n");
	if failures > 0:
	  MESSAGE = "! ERROR: %d failure(s) " %( failures )
	  if nb_of_failures_before_error > 0 and failures >= nb_of_failures_before_error:
	    MESSAGE = "%s (or more)" % (MESSAGE)
	  MESSAGE = "%s occurred during auto-props checking.\n" %(MESSAGE)
	  USAGE = """! Please set the auto-props value in your subversion config file : 
! Location(linux): $HOME/.subversion/config '
! Location(windows): $APPDATA\subversion\config
! or in HKCU\\Software\\Tigris.org\\Subversion\\Config\\miscellany
! You can also execute: svn propset svn:keywords "Author Date Id Revision"
! (use flag -R for recursive if needed)
! 
! For more details, visit http://www.ise/wiki/index.php/SubversionAtISE
"""

	  sys.stderr.write("\n%s%s!\n%s%s" % (hr, MESSAGE, USAGE, hr))
	if log_enabled: logfile.close()
	sys.exit(failures) 
except SystemExit:
	sys.exit(failures) 
except:
	if log_enabled: logfile.close()
	einfo = sys.exc_info()
	sys.excepthook(einfo[0], einfo[1], einfo[2]);
	sys.stderr.write ("\nCheckProp: Error occurred ... ask your system administrator \n")
	sys.exit(-1) 

