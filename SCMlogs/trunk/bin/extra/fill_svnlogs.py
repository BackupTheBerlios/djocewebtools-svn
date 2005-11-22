#!/usr/local/bin/python

import os;
import sys;
#import shutil;
import datetime;
from string import atoi;
sday = sys.argv[1]
spday = sday.split ('-')
day = datetime.datetime (atoi(spday[0]), atoi(spday[1]), atoi(spday[2]))

sday = sys.argv[2]
spday = sday.split ('-')
stopday = datetime.datetime (atoi(spday[0]), atoi(spday[1]), atoi(spday[2]))

print "Generate log between " + day.strftime("%Y-%m-%d") + " and " + stopday.strftime("%Y-%m-%d")

repo = "file:///home/svn/svnroot/ise_svn"
logdir = "/home/svn/svnroot/ise_svn/LOGS"
while day <= stopday:
	logfn = os.path.join (logdir, "%02d" % (day.year))
	if not os.path.exists (logfn):
		os.mkdir (logfn)
	logfn = os.path.join (logfn, "%02d" % (day.month))
	if not os.path.exists (logfn):
		os.mkdir (logfn)
	logfn = os.path.join (logfn, day.strftime("%Y-%m-%d"))

	cmd = "svn log " + repo + " -v "
	cmd = cmd + ' -r "{' + day.strftime("%Y-%m-%d") + 'T09:00}'
	day = day + datetime.timedelta(1)
	cmd = cmd + ':{' + day.strftime("%Y-%m-%d") + 'T09:00}" '
	cmd = cmd + ' > ' + logfn
	print cmd
	os.system (cmd)

#cmd = svn log file:///home/svn/svnroot/ise_svn/ -r "{2005-11-10T09:00}:{2005-11-11T09:00}" > ise_svn/LOGS/2005/11/
