"""pySCMLogs.bots

"""
__revision__ = "$Id$"
__version__ = "1.0"

def html_url_for(bot,id,name):
	bot_name = "%s.%s" % (__name__, bot)
	try:
		__import__(bot_name)
		cmd = "%s.html_url_for(\"%s\",\"%s\")" % (bot, id, name)
		return eval(cmd)
	except:
		return ""

