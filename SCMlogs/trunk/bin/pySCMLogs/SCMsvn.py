#!/usr/bin/python

from SCMlog import * ;

class LogEntryDetails:
	def __init__ (self, dir):
		self.directory = dir;
		self.added = [];
		self.removed = [];
		self.modified = [];

class SvnLogEntry(SCMLogEntry):
	def __init__ (self, conf, webUrl_engine):
		SCMLogEntry.__init__(self, conf, webUrl_engine)
		self.revision = 0;

	def info_to_text (self, offset):
		return "%s[ Revision   ] %d\n"  %(offset, self.revision)

	def info_to_html (self):
		result = ""
		if self.revision > 0:
			result =  "%s<tr><td class=info >Revision</td><td colspan=3>%d</td></tr>\n"  %(result, self.revision);
		return result

	def list_to_html (self, lst_id, lst, title, cssclass):
		result = ""
		if len(lst) > 0:
			result = "%s<tr><td class=\"%s\" >%s</td><td colspan=3>" % (result, cssclass, title)
			for file in lst: 
				result = "%s\n\t - <a href=\"%s\" target=\"_MyLogs_\">%s</a> " %(result, \
						self.webappUrlForShowFileInDirectory (file, self.directory), \
						file \
					)
				tmp = "<a href=\"%s\" target=\"_MyLogs_\">r%d</a>" %( \
						self.webappUrlForShowFileInDirectory (file, self.directory, self.revision), \
						self.revision \
					)
				if lst_id != self.added_id:
					tmp = "%s | <a href=\"%s\" target=\"_MyLogs_\">diff</a>" %(tmp, \
							self.webappUrlForDiffFileInDirectory (file, self.directory, self.revision, self.revision - 1) \
						)
					tmp = "%s | <a href=\"%s\" target=\"_MyLogs_\">blame</a>" %(tmp, \
							self.webappUrlForBlameFileInDirectory (file, self.directory, self.revision) \
						)
				if len (tmp) > 0:
					result = "%s (<small class=\"diff\">%s</small>)" % (result, tmp)
				tmp =''
				result = "%s<br/>\n" % (result)
			result = "%s</td></tr>\n" % (result)
		return result

class SvnLogEntries:
	def __init__ (self, conf, webUrl_engine):
		self.config = conf;
		self.webUrl_engine = webUrl_engine;
		self.date = '';
		self.author = '';
		self.directories = {};
		self.logmessage = '';
		self.revision = 0;

	def load_log (self, log):

		### Analyse log
		message = '';
		tag = '';
		loglines = (re.split ('\n', log))[1:-1];


		cursor = 0;
		self.date = (loglines[cursor])[len("Date:	"):];
		cursor = cursor + 1
		self.author = (loglines[cursor])[len("Author:	"):];
		if len (self.author) == 0:
			self.author = "unknown"
		cursor = cursor + 1
		self.revision = atoi((loglines[cursor])[len("Revision:	"):])
		cursor = cursor + 1
		dirchanged_nb = atoi ((loglines[cursor])[len("DirChanged:"):])
		cursor = cursor + 1
		if dirchanged_nb > 0:
			for i in range (1, dirchanged_nb + 1):
				dir = loglines[cursor]
				if dir[-1] == '/':
					dir = dir[:-1]
				self.directories[dir] = LogEntryDetails(dir)
				cursor = cursor + 1
		changed_nb = atoi ((loglines[cursor])[len("Changed:"):])
		cursor = cursor + 1
#		print ">>> %s\n" % (loglines[cursor])
		if changed_nb > 0:
			for i in range (1, changed_nb + 1):
				line = loglines[cursor]
				ch = line[0]
				if ch == 'A':
					self.append_added (strip(line[1:]))
				elif ch == 'U':
					self.append_modified (strip(line[1:]))
				elif ch == 'D':
					self.append_removed (strip(line[1:]))
				cursor = cursor + 1

		loglines_nb = atoi ((loglines[cursor])[len("Logs:"):])
		cursor = cursor + 1
		logs = ""
		if loglines_nb > 0:
			for i in range (1, loglines_nb + 1):
				line = loglines[cursor]
				cursor = cursor + 1
				self.logmessage = "%s%s\n" % (self.logmessage, line)
			while self.logmessage[-1] == '\n':
				self.logmessage = self.logmessage[:-1]

	def to_logEntries(self):
		result = [];
		for d in self.directories:
			o = SvnLogEntry(self.config, self.webUrl_engine)
			o.date = self.date;
			o.author = self.author;
			o.revision = self.revision;
			o.directory = d;
			ldir = self.directories[d]
			o.added = ldir.added;
			o.modified = ldir.modified;
			o.removed = ldir.removed;
			o.logmessage = self.logmessage;

			result.append (o)
		return result

	def dirname_from (self, path):
		d = os.path.dirname (path)
#		print ">>> dirname: %s -> %s" % (path, d)
		return d
	def filename_from (self, path):
		f = os.path.basename (path)
		return f

	def append_added (self, path):
		p = strip (path);
		d = self.dirname_from (p)
		if self.directories.has_key (d):
			f = self.filename_from (p)
			self.directories[d].added.append (f)
#		else:
#			print "error with %s :: %s" % (p, d)
	def append_modified (self, path):
		p = strip (path);
		d = self.dirname_from (p)
		if self.directories.has_key (d):
			f = self.filename_from (p)
			self.directories[d].modified.append (f)
#		else:
#			print "error with %s :: %s" % (p, d)
	def append_removed (self, path):
		p = strip (path);
		d = self.dirname_from (p)
		if self.directories.has_key (d):
			f = self.filename_from (p)
			self.directories[d].removed.append (f)
#		else:
#			print "error with %s :: %s" % (p, d)


