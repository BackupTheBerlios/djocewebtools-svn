#!/usr/bin/python

import os
import re
from string import split, replace, rstrip, strip, atoi ;
#from misc import * ;


def text_to_formated_html_escape (txt):
	# escape the  '<' and '>' to htmlentities
	result = "%s"  % (txt)
	result = replace (result, "<","&lt;")
	result = replace (result, ">","&gt;")
	result = replace (result, "\n", "<BR>\n")
	#result = replace (result, "\ ", "&nbsp;")
	result = replace (result, "    ", "&nbsp;&nbsp;&nbsp;&nbsp;")
	result = replace (result, "\t", "&nbsp;&nbsp;&nbsp;&nbsp;")
	return result


# classes Declaration
class SCMLogEntry:
	def __init__ (self, conf, webUrl_engine):
		self.webUrl_engine = webUrl_engine
		self.config = conf

		self.date = ''
		self.author = ''
		self.revision = ''
		self.directory = ''
		self.logmessage = ''

		self.added = [];
		self.removed = [];
		self.modified = [];

		self.added_id = 'A';
		self.modified_id = 'U';
		self.removed_id = 'D';

	def webappUrlForBlameFileInDirectory (self, file, dir, r1=-1):
		return self.webUrl_engine.urlBlameFile (file, dir, r1)

	def webappUrlForDiffFileInDirectory (self, file, dir, r1=0, r2=0):
		return self.webUrl_engine.urlDiffFile (file, dir, r1, r2)

	def webappUrlForShowFileInDirectory (self, file, dir, r1=-1):
		return self.webUrl_engine.urlShowFile (file, dir, r1)

	def webappUrlForListDirectory (self, dir, r1=-1):
		return self.webUrl_engine.urlShowDir (dir, r1)

	def webappUrlForDiffDirectory (self, dir, r1, r2):
		return self.webUrl_engine.urlDiffDir (dir, r1, r2)

	def to_text (self):
		tab = " "*13
		offset = "  "
		result = ""
		result = "%s%s" % (result, offset +"_"*70+"\n");
		result = "%s%s[ Author     ] %s\n"  %(result, offset, self.author);
		result = "%s%s[ Date       ] %s\n"  %(result, offset, self.date);
		result = "%s%s[ Directory  ] %s\n"  %(result, offset, self.directory);
		result = "%s%s"  %(result, self.info_to_text (offset));
		if self.modified:
			result = "%s%s" % (result, self.list_to_text (self.modified, "Modified", offset, tab))
		if self.added:
			result = "%s%s" % (result, self.list_to_text (self.added, "Added   ", offset, tab))
		if self.removed:
			result = "%s%s" % (result, self.list_to_text (self.removed, "Removed ", offset, tab))
		result = "%s%s[ LogMessage ] %s\n"  %(result, offset, replace (self.logmessage, "\n","\n"+offset+ tab + ": "));
		return result

	def list_to_text (self, lst, title, offset, tab):
		result = "%s[ %s   ]\n" % (offset, title)
		for file in lst:
			result = "%s%s%s - %s\n" %(result, offset, tab, file)
		return result

	def info_to_text (self, offset):
#		return "%s[ Info   ] %d\n"  %(offset, self.info);
		return ""

	def info_to_html (self):
		return ""

	def to_html (self):
		result = ""
		result = "%s<tr><td class=date >Date</td>\
				<td>%s</td>\
				<td class=author >Author</td>\
				<td>%s</td></tr>\n" \
				%(result, self.date, self.author);

		result = "%s<tr><td class=directory >Directory</td><td colspan=3>" % (result)
		result = "%s<a href=\"%s\" target=\"_MyLogs_\" >%s</a>" % (result, \
				self.webappUrlForListDirectory (self.directory, self.revision), self.directory);
		if self.config.SCMmode == 'svn':
			result = "%s (<a href=\"%s\" target=\"_MyLogs_\" >diff</a>)" % (result, \
				self.webappUrlForDiffDirectory (self.directory, self.revision, self.revision - 1));
		result = "%s</td></tr>\n"  %(result)
		result =  "%s%s"  %(result, self.info_to_html());

		### Files and Co
		if self.modified:
			result = "%s%s" % (result, self.list_to_html (self.modified_id, self.modified, "Modified", "modified"))
		if self.added:
			result = "%s%s" % (result, self.list_to_html (self.added_id, self.added, "Added", "added"))
		if self.removed:
			result = "%s%s" % (result, self.list_to_html (self.removed_id, self.removed, "Removed", "removed"))
		result = "%s\n"  %(result)
		result = "%s<tr><td class=log >LogMessage</td><td colspan=3 class=logmessage>%s</td></tr>"  %(result, \
				text_to_formated_html_escape (self.logmessage));
		return result

	def list_to_html (self, lst_id, lst, title, cssclass):
		result = ""
		return result
