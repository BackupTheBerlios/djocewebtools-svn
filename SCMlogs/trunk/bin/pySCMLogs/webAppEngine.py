#!/usr/bin/python

class webappUrlEngine:
	def __init__ (self, baseurl, reponame):
		self.baseurl = baseurl;
		self.reponame = reponame;

	def urlShowFile (self, file, dir, r1): return ""
	def urlBlameFile (self, file, dir, r1): return ""
	def urlDiffFile (self, file, dir, r1, r2): return ""
	def urlShowDir (self, dir, r1): return ""
	def urlDiffDir (self, dir, r1, r2): return ""

class webscmlogs (webappUrlEngine):
	def set_default_webapp (self, wapp):
		self.webapp = wapp
	def urlTmp (self, op):
		url = "%s?op=%s&repname=%s" % (self.baseurl, op, self.reponame)
		if len (self.webapp) > 0:
			url = "%s&webapp=%s" % (url, self.webapp);
		return url;
	def urlShowFile (self, file, dir, r1):
		url = self.urlTmp ('fileshow')
		if r1 >= 0: url = "%s&rev=%s" % (url, r1)
		url = "%s&path=/%s/%s" % (url, dir,file)
		return url
	def urlBlameFile (self, file, dir, r1):
		url = self.urlTmp ('fileblame')
		if r1 >= 0: url = "%s&rev=%s" % (url, r1)
		url = "%s&path=/%s/%s" % (url, dir,file)
		return url
	def urlDiffFile (self, file, dir, r1, r2):
		url = self.urlTmp ('filediff')
		if r1 >= 0: url = "%s&r1=%s&r2=%s" % (url, r1, r2)
		url = "%s&path=/%s/%s" % (url, dir,file)
		return url
	def urlShowDir (self, dir, r1):
		url = self.urlTmp ('dirshow')
		if r1 >= 0: url = "%s&rev=%s" % (url, r1)
		url = "%s&path=/%s" % (url, dir)
		return url
	def urlDiffDir (self, dir, r1, r2):
		url = self.urlTmp ('dirdiff')
		url = "%s&path=/%s&r1=%s&r2=%s" % (url, dir, r1, r2)
#		url = "%s&compare[]=/%s@%s&compare[]=/%s@%s" % (url, dir, r1, dir, r2)
		return url

class websvn (webappUrlEngine):
	def urlShowFile (self, file, dir, r1):
		url = "%s/filedetails.php?repname=%s" % (self.baseurl, self.reponame)
		if r1 >= 0: url = "%s&rev=%s" % (url, r1)
		url = "%s&sc=1" % (url)
		url = "%s&path=/%s/%s" % (url, dir,file)
		return url
	def urlBlameFile (self, file, dir, r1):
		url = "%s/blame.php?repname=%s" % (self.baseurl, self.reponame)
		if r1 >= 0: url = "%s&rev=%s" % (url, r1)
		url = "%s&sc=1" % (url)
		url = "%s&path=/%s/%s" % (url, dir,file)
		return url
	def urlDiffFile (self, file, dir, r1, r2):
		url = "%s/diff.php?repname=%s" % (self.baseurl, self.reponame)
		if r1 >= 0: url = "%s&rev=%s" % (url, r1)
		url = "%s&sc=1" % (url)
		url = "%s&path=/%s/%s" % (url, dir,file)
		return url
	def urlShowDir (self, dir, r1):
		url = "%s/listing.php?repname=%s" % (self.baseurl, self.reponame)
		if r1 >= 0: url = "%s&rev=%s" % (url, r1)
		url = "%s&sc=1" % (url)
		url = "%s&path=/%s" % (url, dir)
		return url
	def urlDiffDir (self, dir, r1, r2):
		url = "%s/comp.php?repname=%s" % (self.baseurl, self.reponame)
		url = "%s&compare[]=/%s@%s&compare[]=/%s@%s" % (url, dir, r1, dir, r2)
		return url

class viewcvs(webappUrlEngine):
	def tmpUrl (self, file, dir):
		return "%s/%s/%s?root=%s" % (self.baseurl, dir, file, self.reponame)
	def urlShowFile (self, file, dir, r1):
		url = self.tmpUrl (file, dir)
		if r1 >= 0: url = "%s&rev=%s" % (url, r1)
		url = "%s&content-type=text/vnd.viewcvs-markup" % (url)
		return url
	def urlBlameFile (self, file, dir, r1):
		url = self.urlShowFile (file, dir, r1)
		url = "%s&view=annotate" % (url)
		return url
	def urlDiffFile (self, file, dir, r1, r2):
		if len(file) > 0:
			if r1 == 'NONE':
				url = self.urlShowFile (file, dir, r2)
			elif r2 == 'NONE':
				url = self.urlShowFile (file, dir, r1)
			elif r1 != 0 and r2 != 0:
				url = self.tmpUrl(file, dir)
				url = "%s&r1=%s&r2=%s" % (url, r1, r2)
		else:
			url = self.urlShowDir (dir, r1)
		return url
	def urlShowDir (self, dir, r1):
		url = self.tmpUrl ('', dir)
		if r1 >= 0: url = "%s&rev=%s" % (url, r1)
		return url
	def urlDiffDir (self, dir, r1, r2):
		return self.urlShowDir(dir, r1)
