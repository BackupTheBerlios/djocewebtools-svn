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
from subprocess import Popen, PIPE
from string import split

repos = sys.argv[1]
trans = sys.argv[2]

SVNLOOK = "/usr/bin/svnlook"
CONFIG = "%s/conf/config" % repos

config = ConfigParser()
config.read(CONFIG)
autoprops = dict(config.items("auto-props"))
changes = os.popen("%s changed -t %s %s" % (SVNLOOK,trans,repos)).readlines()

def checkPath(path,autoprops):
  #sys.stderr.write ("Checking autoprops on [%s] ...\n" % (path))
  okay = 1
  is_dir = (path[-1] == '/')
  for pattern in autoprops.keys():
    if fnmatch(path,pattern):
      items = map( lambda rule: rule.split("="),autoprops[pattern].split(";"))
      for item in items:
        propname = item[0]
        if is_dir and propname == 'svn:keywords':
          sys.stderr.write ("Skip checking %s on directory [%s] ...\n" % (propname, path))
        else:
          expected = item[1]
          cmd = "%s propget -t %s %s %s %s" % (SVNLOOK,trans,repos,propname,path)
          propget = Popen(split (cmd), stdout=PIPE).stdout
          #propget = os.popen(cmd)
          propval = propget.read()
          status = propget.close()
          if propval.find(expected) < 0:
            okay = 0
            #if not status:
            sys.stderr.write("hook: Property value '%s=%s' not found on path '%s'\n" % (propname,expected,path))
  return okay

failures = 0
for change in changes:
  if change[0] == 'A':
    path = change[4:].strip()
    if not checkPath(path,autoprops):
      sys.stderr.write("props not set correctly for %s\n" % path)
      failures = 1

if failures:
  hr = "\n" + "-" * 80 + "\n"
  MESSAGE = 'ERROR: Set the auto-props in your subversion config file.'
  MESSAGE = "%s\n%s" % (MESSAGE, 'Location(linux): $HOME/.subversion/config ')
  MESSAGE = "%s\n%s" % (MESSAGE, 'Location(windows): $APPDATE\subversion\config \n  or in HKCU\\Software\\Tigris.org\\Subversion\\Config\\miscellany')
  MESSAGE = "%s\n%s" % (MESSAGE, ':\t[auto-props]\n:\t* = svn:keywords=Author Date ID Revision')
  MESSAGE = "%s\n%s" % (MESSAGE, 'Or for instance execute :\n  svn propset svn:keywords "Author Date ID Revision" ')
  sys.stderr.write(hr + MESSAGE + hr)
sys.exit(failures) 

